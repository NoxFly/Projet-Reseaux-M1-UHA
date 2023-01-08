// Author : NoxFly
// Copyrights 2017 - 2023

#ifndef PERFMEASURE_HPP
#define PERFMEASURE_HPP

#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

class PerfMeasure {
	public:
		PerfMeasure();
		~PerfMeasure();

        void start();
        void flag();
        void end();

        int64_t getStartTime() const;
        int64_t getEndTime() const;
        int64_t getDuration() const;

        int64_t getFlag(const unsigned int i) const;

        std::string getTime(const unsigned int step) const;
        std::string getTotalTime() const;

        friend ostream& operator<<(ostream& os, const PerfMeasure& perf);

    protected:
        bool m_hasStarted;
        std::vector<int64_t> m_timestamps;
};

#endif // PERFMEASURE_HPP