#include "NetworkModel.hpp"

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

#include <SFML/System/Vector2.hpp>

#include "mvc/Model/Network/Graphe/GrapheGreedy/GrapheGreedy.hpp"
#include "mvc/Model/Network/Graphe/GrapheBacktrack/GrapheBacktrack.hpp"

#include "utils/PerfMeasure/PerfMeasure.hpp"
#include "utils/utils.hpp"
#include "common.hpp"


NetworkModel::NetworkModel():
    m_antennas{},
    m_frequencies{},
    m_showAntennas(true),
    m_showRanges(false),
    m_showColors(false)
{
}

NetworkModel::~NetworkModel() {

}

void NetworkModel::loadFromConfig(const NetworkConfig& config) {
#ifdef MEASURE_PERF
    PerfMeasure perf;

    perf.start();
#endif

	std::ifstream file(config.entryFile);

    bool isCSV = endsWith(config.entryFile, ".csv");

	if(file.is_open()) { // only read if file exists and is not empty

        m_antennas.clear();

        if(isCSV)   loadFromCsv(file);
        else        loadFromTxt(file);

		file.close();

#ifdef DEBUG
        std::cout << std::endl;
#endif

	}
	else {
        throw std::runtime_error("[ERROR] NetworkModel::loadFromConfig : Failed to open the sample file.");
    }

#ifdef MEASURE_PERF
    perf.flag();
#endif

    // ------ GRAPH / COLORIZATION ------
    updateColorization();

#ifdef MEASURE_PERF
    perf.end();

    std::cout << "\n" << BOX_TL << repeat(BOX_HL, 6) << " Network loading performances log " << repeat(BOX_HL, 6) << BOX_TR
        << "\n" << BOX_VL << " loadFile : " << perf.getTime(0)
        << "\n" << BOX_VL << " graphe   : " << perf.getTime(1)
        << "\n" << BOX_BL << repeat(BOX_HL, 46) << BOX_BR
        << std::endl;
#endif
}


void NetworkModel::loadFromTxt(std::ifstream& file) {
    std::string line;

    // read line by line
    while(std::getline(file, line)) {
        // a line is modelised here as "name X Y R" (1 string 3 int)
        // where X,Y are in lambert
        std::string name;
        // default name, gives a max length
        char cname[] = "unamed XXX-XXX-XXX-XXX";
        int x = 0, y = 0, r = 0;

        sscanf(line.c_str(), "%s %d %d %d", cname, &x, &y, &r);

        name = std::string(cname);

        createAntenna(name, x, y, r);
    }
}

void NetworkModel::loadFromCsv(std::ifstream& file) {
    std::string line;

    // remove the first line because it's header
    std::getline(file, line);

    if(!file) {
        return;
    }


    // read cell by cell
    while(std::getline(file, line)) {
        std::istringstream iss { line };
        
        std::string name;
        int values[3];

        int i = -2;
        std::string s;

        while(std::getline(iss, s, ';')) {
            if(++i == -1) {
                name = s;
            }
            else {
                values[i] = std::stoi(s);
            }
        }

        createAntenna(name, values[0], values[1], values[2]);
    }
}

void NetworkModel::createAntenna(const std::string& name, const int x, const int y, const unsigned int r) {
    auto ant = std::make_unique<Antenna>(name, sf::Vector2i(x, y), r, 0, 0);

    m_antennas.push_back(std::move(ant));
}


void NetworkModel::updateColorization() {
#ifdef MEASURE_PERF
    PerfMeasure perf;

    perf.start();
#endif

    // no need to operate if there's no antenna
    if(m_antennas.size() == 0) {
        return;
    }

    //do logic to figure out which antennas are in each others zone
    // for every two interfering antennas, take their indexes
    // and pass them to addEdge method of Graphe class
    unsigned int antennasCr = m_antennas.size();

	GrapheGreedy graphe(antennasCr);

    // 1st. Add vertices
    for(unsigned int i=0; i < antennasCr; i++) {
        graphe.addVertex(i, (*this)[i]);
    }

    // 2nd. Add edges
    for(unsigned int i=0; i < antennasCr; i++) {
        for(unsigned int j=i+1; j < antennasCr; j++) {
            // Antennas
            auto a = (*this)[i];
            auto b = (*this)[j];

            const unsigned int rangesCollide = circleToCircleCollision(
                a->getPosition().meters().x,
                a->getPosition().meters().y,
                a->getRange(),
                b->getPosition().meters().x,
                b->getPosition().meters().y,
                b->getRange()
            );

            if(rangesCollide != 0) {
                graphe.addEdge(i, j);
            }
        }
    }

#ifdef MEASURE_PERF
    perf.flag();
#endif

	graphe.colorize();

#ifdef MEASURE_PERF
    perf.flag();
#endif

    // now associate a frequence for each color
    // GSM frequences are in 900 - 1800 MHz bounds
    std::unordered_map<sf::Uint32, unsigned int> colFreq;

    const auto& colors = graphe.getColors();
    const unsigned int colorCount = colors.size();

    const unsigned int freqStart = 900;
    const unsigned int freqEnd = 1800;

    const unsigned int freqStep = (freqEnd - freqStart) / colorCount;

    unsigned int freqVal = freqStart;

    m_frequencies.clear();

    for(const auto& color : colors) {
        colFreq.emplace(
            color.toInteger(),
            freqVal
        );

        m_frequencies.push_back(freqVal);

        freqVal += freqStep;
    }

    // set frequence for each antennas
    for(const auto& ant : m_antennas) {
        ant->setFreq(colFreq.at(ant->getColor().toInteger()));
    }

#ifdef MEASURE_PERF
    perf.end();
#endif

#ifdef DEBUG
    /* ==== HEADER ==== */
    std::string header = BOX_VL" idx";
    
    const auto ls = std::max((int)std::to_string(colorCount).size(), 3);
    const unsigned int l = ls - 2;
    
    header += repeat(' ', l);

    header += BOX_VL"  r  ";
    header += BOX_VL"  g  ";
    header += BOX_VL"  b  ";
    header += BOX_VL"   freq  ";
    header += BOX_VL;

    unsigned int headerSize = header.size() - 2;

    header += "\n";
    header += BOX_CR;
    header += repeat(BOX_HL, 33);
    header += BOX_CL;

    headerSize = header.size() / 2;

    const std::string title = "GRAPHE COLORIZATION";
    const unsigned int titleSize = title.size();
    (void)headerSize;
    (void)titleSize;
    const unsigned int tbl = 6;

    std::cout
        << BOX_TL
        << repeat(BOX_HL, tbl)
        << " " << title << " "
        << repeat(BOX_HL, tbl)
        << BOX_TR
        << "\n" << header
        << std::endl;


    /* ==== ANTENNAS ==== */

    for(unsigned int i=0; i < colorCount; i++) {
        const auto s = std::to_string(i);
        const auto color = m_antennas.at(i)->getColor();
        const unsigned int l = ls - s.size() + 1;

        const std::string sColor[] = {
            std::to_string(color.r),
            std::to_string(color.g),
            std::to_string(color.b)
        };

        std::cout << BOX_VL;

        /* ==== INDEX ==== */
        std::cout << repeat(' ', l) << s << " " << BOX_VL;

        /* ==== COLOR ==== */
        for(unsigned int j=0; j < 3; j++) {
            const unsigned int cl = 6 - sColor[j].size() - ((j == 0)? 2 : 0);

            std::cout << repeat(' ', cl) << sColor[j];
        }

        /* ==== FREQUENCE ==== */
        const std::string freq = std::to_string(m_antennas.at(i)->getFreq());
        const unsigned int freqL = std::to_string(freqEnd).size() - freq.size();

        std::cout
            << " "
            << BOX_VL
            << "   "
            << repeat(' ', freqL)
            << freq << "  "
            << BOX_VL
            << std::endl;
    }


    std::cout
        << BOX_BL
        << repeat(BOX_HL, 33)
        << BOX_BR
        << std::endl;
#endif

#ifdef MEASURE_PERF
    std::cout << "\n" << BOX_TL << repeat(BOX_HL, 7) << " Graphe loading performances log " << repeat(BOX_HL, 6) << BOX_TR
        << "\n" << BOX_VL << " construction     : " << perf.getTime(0)
        << "\n" << BOX_VL << " coloration       : " << perf.getTime(1)
        << "\n" << BOX_VL << " freq. assignment : " << perf.getTime(2)
        << "\n" << BOX_BL << repeat(BOX_HL, 46) << BOX_BR
        << std::endl;
#endif
}

const std::vector<std::unique_ptr<Antenna>>& NetworkModel::getAntennas() const {
	return m_antennas;
}

std::vector<std::unique_ptr<Antenna>>& NetworkModel::getAntennas() {
	return m_antennas;
}

Antenna* NetworkModel::getAntennaByIndex(const unsigned int i) {
    return m_antennas[i].get();
}

Antenna* NetworkModel::operator[](const unsigned int i) {
    return m_antennas[i].get();
}

void NetworkModel::clearNetwork() {
    m_antennas.clear();
    m_frequencies.clear();
}

void NetworkModel::showAntennas(const bool state) {
    m_showAntennas = state;
}

void NetworkModel::showRanges(const bool state) {
    m_showRanges = state;
}

void NetworkModel::showColors(const bool state) {
    m_showColors = state;
}

bool NetworkModel::shouldShowAntennas() const {
    return m_showAntennas;
}

bool NetworkModel::shouldShowRanges() const {
    return m_showRanges;
}

bool NetworkModel::shouldShowColors() const {
    return m_showColors;
}

const std::vector<unsigned int>& NetworkModel::getFrequencies() const {
    return m_frequencies;
}