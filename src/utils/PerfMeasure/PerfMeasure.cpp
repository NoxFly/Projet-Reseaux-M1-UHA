// Author : NoxFly
// Copyrights 2017 - 2023

#include "PerfMeasure.hpp"

#include "utils/utils.hpp"

using namespace std;
using namespace std::chrono;



PerfMeasure::PerfMeasure():
    m_hasStarted(false),
    m_timestamps{}
{}

PerfMeasure::~PerfMeasure() {

}


void PerfMeasure::start() {
    if(!m_hasStarted) {
        m_hasStarted = true;
        m_timestamps.clear();
        m_timestamps.push_back(now<nanoseconds>());
    }
}

void PerfMeasure::flag() {
    if(m_hasStarted) {
        m_timestamps.push_back(now<nanoseconds>());
    }
}

void PerfMeasure::end() {
    if(m_hasStarted) {
        m_hasStarted = false;
        m_timestamps.push_back(now<nanoseconds>());
    }
}

int64_t PerfMeasure::getStartTime() const {
    if(m_timestamps.size() > 0) {
        return m_timestamps[0];
    }

    return 0;
}

int64_t PerfMeasure::getEndTime() const {
    if(m_timestamps.size() > 0) {
        return m_timestamps[m_timestamps.size()-1];
    }

    return 0;
}

int64_t PerfMeasure::getDuration() const {
    return getEndTime() - getStartTime();
}


int64_t PerfMeasure::getFlag(const unsigned int i) const {
    const unsigned int l = m_timestamps.size();

    if(l < 3 || i >= l - 2) {
        return 0;
    }

    return m_timestamps[1+i];
}


std::string PerfMeasure::getTime(const unsigned int step) const {
    if(step < m_timestamps.size() - 1) {
        return nsToTime(m_timestamps[step+1] - m_timestamps[step]);
    }

    return "";
}

std::string PerfMeasure::getTotalTime() const {
    return nsToTime(getDuration());
}



template <typename Duration>
std::string print_time(tm t, Duration fraction) {
    char buff[24];

    sprintf(buff,
        "%04u-%02u-%02u %02u:%02u:%02u.%03u",
        t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
        t.tm_hour, t.tm_min, t.tm_sec,
        static_cast<unsigned>(fraction / milliseconds(1))
    );

    return std::string(buff);
}


ostream& operator<<(ostream& os, const PerfMeasure& perf) {
    const unsigned int l = perf.m_timestamps.size();

    if(l > 0) {
        os << nsToTime(perf.getDuration());
    }
    else {
        os << "The performance recorder has not started yet." << std::endl;
    }

    return os;
}