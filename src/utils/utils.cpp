#include "utils.hpp"

#include <random>
#include <sstream>


using namespace std;


bool endsWith(string_view str, string_view suffix) {
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

bool startsWith(string_view str, string_view prefix) {
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}

bool isInteger(const string& str) {
    for(char const &c : str) {
        if(isdigit(c) == 0)
            return false;
    }

    return true;
}

bool isFloat(const string& str) {
    std::istringstream iss(str);
    float f;
    iss >> noskipws >> f;
    return iss.eof() && !iss.fail(); 
}

string replace(const string& str, const string& find, const string& replace) {
    string result;
    size_t find_len = find.size();
    size_t pos,from = 0;

    while(string::npos != (pos = str.find(find, from))) {
        result.append(str, from, pos-from);
        result.append(replace);
        from = pos + find_len;
    }

    result.append(str, from, string::npos);
    
    return result;
}

vector<string> splitString(string sequence, const string separator) {
    size_t pos = 0;
    vector<string> splitted = {};

    while((pos = sequence.find(separator)) != string::npos) {
        splitted.push_back(sequence.substr(0, pos));
        sequence.erase(0, pos + separator.length());
    }

    if(sequence.size() > 0)
        splitted.push_back(sequence);

    return splitted;
}


std::string repeat(char c, unsigned int n) {
    std::string s = "";

    for(unsigned int i=0; i < n; i++) {
        s += c;
    }

    return s;
}





namespace uuid {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 15);
    static uniform_int_distribution<> dis2(8, 11);

    const char* generate_uuid_v4() {
        stringstream ss;
        int i;

        ss << hex;
        
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        
        ss << "-";
        
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        
        ss << "-4";
        
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        
        ss << "-";
        ss << dis2(gen);
        
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        
        ss << "-";
        
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        
        return ss.str().c_str();
    }
}

unsigned int circleToCircleCollision(const float x1, const float y1, const float r1, const float x2, const float y2, const float r2) {
    const float d = std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
 
    if(d <= r1 - r2) {
        return 3;
    }
    else if(d <= r2 - r1) {
        return 4;
    }
    else if(d < r1 + r2) {
        return 1;
    }
    else if(d == r1 + r2) {
        return 2;
    }
    else {
        return 0;
    }
}