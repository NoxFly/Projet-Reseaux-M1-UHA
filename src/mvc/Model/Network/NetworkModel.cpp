#include "NetworkModel.hpp"

#include <iostream>
#include <string.h>
#include <fstream>

#include <SFML/System/Vector2.hpp>

#include "mvc/Model/Network/Graphe/Graphe.hpp"
#include "utils/utils.hpp"


NetworkModel::NetworkModel():
    m_antennas{},
    m_showAntennas(true),
    m_showRanges(false),
    m_showColors(false)
{

}

NetworkModel::~NetworkModel() {

}

void NetworkModel::loadFromConfig(const NetworkConfig& config) {
	std::ifstream file(config.entryFile);
    std::string line;


	if(file.is_open()) { // only read if file exists and is not empty

        m_antennas.clear();

		while(std::getline(file, line)) {
            // a line is modelised here as "0.0 0.0 0.0" (3 floats)
            // and in order "X Y RANGE" and where X,Y are in lambert
            std::string name;
            char cname[] = "unamed XXX-XXX-XXX-XXX";
            float x, y, r;

            sscanf(line.c_str(), "%s %f %f %f", cname, &x, &y, &r);

            // at least one of the 3 floats does not respect the float form
            if(x < .1 || y < .1 || r < .1) {
                // continue;
            }

            name = std::string(cname);

            auto ant = std::make_unique<Antenna>(name, sf::Vector2f(x, y), r, 0, 0);

            m_antennas.push_back(std::move(ant));
		}

		file.close();

#ifdef DEBUG
        std::cout << std::endl;
#endif

	}
	else {
        throw std::runtime_error("[ERROR] NetworkModel::loadFromConfig : Failed to open the sample file.");
    }




    // ------ GRAPH / COLORIZATION ------
    updateColorization();
}

void NetworkModel::updateColorization() {
    //do logic to figure out which antennas are in each others zone
    // for every two interfering antennas, take their indexes
    // and pass them to addEdge method of Graphe class
    unsigned int antennasCr = m_antennas.size();

    std::cout << "am antennas count : " << antennasCr << std::endl;

	Graphe graphe(antennasCr);

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
                a->getPosition().lambert().x,
                a->getPosition().lambert().y,
                a->getRange(),
                b->getPosition().lambert().x,
                b->getPosition().lambert().y,
                b->getRange()
            );

            if(rangesCollide != 0) {
                graphe.addEdge(i, j);
            }
        }
    }

	graphe.colorize();


    // now associate a frequence for each color
    // GSM frequences are in 900 - 1800 MHz bounds
    std::unordered_map<sf::Uint32, unsigned int> colFreq;

    const auto& colors = graphe.getColors();
    const unsigned int colorCount = colors.size();

    const unsigned int freqStart = 900;
    const unsigned int freqEnd = 1800;

    const unsigned int freqStep = (freqEnd - freqStart) / colorCount;

    unsigned int freqVal = freqStart;

    for(const auto& color : colors) {
        colFreq.emplace(
            color.toInteger(),
            freqVal
        );

        freqVal += freqStep;
    }

    // set frequence for each antennas
    for(const auto& ant : m_antennas) {
        ant->setFreq(colFreq.at(ant->getColor().toInteger()));
    }


#ifdef DEBUG
    /* ==== HEADER ==== */
    std::string header = "| idx";
    
    const unsigned int l = colorCount - 4;
    
    header += repeat(' ', l);

    header += "|  r  |  g  |  b  |   freq  |";

    unsigned int headerSize = header.size() - 2;

    header += "\n|";
    header += repeat('-', headerSize);
    header += "|";

    headerSize = header.size() / 2;

    const std::string title = "GRAPHE COLORIZATION";
    const unsigned int titleSize = title.size();
    const unsigned int tbl = (headerSize - titleSize - 2) / 2;

    std::cout
        << repeat('-', tbl)
        << " " << title << " "
        << repeat('-', tbl)
        << "\n" << header
        << std::endl;


    /* ==== ANTENNAS ==== */
    for(unsigned int i=0; i < colorCount; i++) {
        const auto s = std::to_string(i);
        const auto color = m_antennas.at(i)->getColor();
        const unsigned int l = colorCount - s.size() - 1;

        const std::string sColor[] = {
            std::to_string(color.r),
            std::to_string(color.g),
            std::to_string(color.b)
        };

        std::cout << "|";

        /* ==== INDEX ==== */
        std::cout << repeat(' ', l) << s << " |";

        /* ==== COLOR ==== */
        for(unsigned int j=0; j < 3; j++) {
            const unsigned int cl = 6 - sColor[j].size() - ((j == 0)? 2 : 0);

            std::cout << repeat(' ', cl) << sColor[j];
        }

        /* ==== FREQUENCE ==== */
        const std::string freq = std::to_string(m_antennas.at(i)->getFreq());
        const unsigned int freqL = std::to_string(freqEnd).size() - freq.size();

        std::cout
            << " |   "
            << repeat(' ', freqL)
            << freq << "  |"
            << std::endl;
    }


    std::cout
        << repeat('-', headerSize)
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

void NetworkModel::clear() {
    m_antennas.clear();
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
