#ifndef UTILS_HPP
#define UTILS_HPP

#include <string_view>
#include <vector>

#ifdef WINDOWS
#define DIRECTORY_SEPARATOR "\\"
#else // Linux or MacOS
#define DIRECTORY_SEPARATOR "/"
#endif

// bug with splitString for no reason.
// using namespace std;


/**
 * Returns either a suffix is at the end of a string or not
 * @param str The parent string to search the suffix in
 * @param suffix The suffix to search
 * @return Either the string has the suffix or not
 */
bool endsWith(std::string_view str, std::string_view suffix);

/**
 * Returns either a prefix is at the start of a string or not
 * @param str The parent string to search the prefix in
 * @param prefix The preefix to search
 * @return Either the string has the prefix or not
 */
bool startsWith(std::string_view str, std::string_view prefix);

/**
 * Returns either a given string is an integer or not
 * @param str The string to check
 * @return Either the string can be converted to an integer or not
 */
bool isInteger(const std::string& str);

/**
 * Returns either a given string is a float or not
 * @param str The string to check
 * @return Either the string can be converted to a float or not
 */
bool isFloat(const std::string& str);

/**
 * Replaces a substring in the given string
 * @param str The main string
 * @param find The substring to replace
 * @param replace The substring to replace by
 * @return The modified string
 */
std::string replace(const std::string& str, const std::string& find, const std::string& replace);

/**
 * Splits the given string in vector of substrings, delimited by the given separator
 * @param sequence The string to split
 * @param separator The delimiter
 * @return The vector of splitted substrings
 */
std::vector<std::string> splitString(std::string sequence, const std::string separator);

// namespace used to
// isolate all stl random variables
// from outside.
namespace uuid {
    /**
     * Generates and returns a 36-char uuid.
     */
    const char* generate_uuid_v4();
}

/**
 * Returns either 2 circles collides.
 * 0 : no collisions
 * 1 : intersection
 * 2 : touch
 * 3 : c2 inside c1
 * 4 : c1 inside c2
 * @param x1 - The position x-axis of the first circle
 * @param y1 - The position y-axis of the first circle
 * @param r1 - The radius of the first circle
 * @param x2 - The position x of the second circle
 * @param y2 - The position y of the second circle
 * @param r2 - The radius of the second circle
 */
unsigned int circleToCircleCollision(const float x1, const float y1, const float r1, const float x2, const float y2, const float r2);

#endif // UTILS_HPP