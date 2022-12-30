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






namespace uuid {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 15);
    static uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4() {
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

        return ss.str();
    }
}