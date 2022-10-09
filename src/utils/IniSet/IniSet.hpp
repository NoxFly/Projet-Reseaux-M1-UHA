#ifndef INISET_HPP
#define INISET_HPP

#include <string>
#include <vector>
#include <map>

using namespace std;

/**
 * A parser for .ini files.
 * Not the more efficient, but it does the job.
 * It only allows to read and parse from a file, then get its values.
 * It cannot set newer values.
 * Also, it allows to export the config in ini or json format.
 * 
 * example of .ini file :
 * 
 * key=value
 * 
 * [section]
 * subkey=subvalue
 * 
 * [anotherSection]
 * anotherkey=anothervalue
 * 
 * /!\ This does not handles an array for now.
 */
class IniSet {
	public:
		explicit IniSet();
		~IniSet();

        /**
         * Loads a configuration from file, and returns either it has been successfully loaded or not.
         * If it couldn't, then the configuration's object is empty.
         * @param filepath The file to read its configuration
         * @returns Either it has successfully read the file and loaded the configuration.
         */
        bool loadFromFile(const string& filepath);
        
        /**
         * Returns the configuration in a string format. Written like a .ini file.
         * @return The configuration in a string format.
         */
        string toString() const;

        /**
         * Returns the configuration in a json format, as a string.
         * @returns The configuration in a json string format.
         */
        string toJSONString() const;

		/**
		 * Allows to log easily the config file.
		 */
        friend ostream& operator<<(ostream& os, const IniSet& ini);


		// === GETTERS ===

		/**
		 * @returns a list of all sections name.
		 */
        vector<string> getSections() const;
		/**
		 * @returns A list of pairs [key, value] in the root level.
		 */
        map<string, pair<string, string>> getEntries() const;
		/**
		 * @param section The section to search in
		 * @returns A list of pairs [key, value] in a given section.
		 */
        map<string, pair<string, string>> getEntries(const string& section) const;

		/**
		 * @returns The list of all the keys in the root level.
		 */
        vector<string> getKeys() const;
		/**
		 * @param section The section to search in
		 * @returns The list of all the keys in the given section.
		 */
        vector<string> getKeys(const string& section) const;

		/**
		 * @returns A list of all the values in the root level
		 */
        vector<string> getValues() const;
		/**
		 * @param section The section to search in
		 * @returns A list of all the values in the given section.
		 */
        vector<string> getValues(const string& section) const;

		
        // === section value ===

		/**
		 * @param section The section to search in
		 * @param key The key to search
		 * @returns The value as a string of the given key in the given section.
		 */
        string getValue(const string& section, const string& key) const;

        /**
         * @param section The section to search in
         * @param key The key to search
         * @returns The pair <key, value> of the searched value in the given section.
         */
        pair<string, string> getPairValue(const string& section, const string& key) const;
        /**
         * @param section The section to search in
         * @param key The key to search
         * @param defaultValue The returned value if the searched one does not exist or isn't an int.
         * @returns The int value of the search key, in the given section. If the value is not found or is not an integer, returns the given default value instead.
         */
        int getIntValue(const string& section, const string& key, int defaultValue) const;

        /**
         * @param section The section to search in
         * @param key The key to search
         * @param defaultValue The returned value if the searched one does not exist or isn't a float.
         * @returns The float value of the search key, in the given section. If the value is not found or is not a float, returns the given default value instead.
         */
        float getFloatValue(const string& section, const string& key, float defaultValue) const;

        /**
         * @param section The section to search in
         * @param key The key to search
         * @param defaultValue The returned value if the searched one does not exist or isn't a boolean.
         * @returns The boolean value of the search key, in the given section. If the value is not found or is not a boolean, returns the given default value instead.
         */
        bool getBoolValue(const string& section, const string& key, bool defaultValue) const;

        /**
         * @param section The section to search in
         * @param key The key to search
         * @returns The type of the key in the given section.
         */
        string getType(const string &section, const string &key) const;


		// === root value ===

        /**
         * @param key The key to search
         * @returns The value of the given key in the root level
         */
        string getValue(const string& key) const;
        /**
         * @param key The key to search
         * @returns The pair <key, value> of the given key in the root level
         */
        pair<string, string> getPairValue(const string& key) const;
        /**
         * @param key The key to search
         * @param defaultValue The returned value if the searched one does not exist or isn't an int.
         * @returns The value as int of the given key in the root level, defaultValue if it does not exist or is not an integer.
         */
        int getIntValue(const string& key, int defaultValue) const;
        /**
         * @param key The key to search
         * @param defaultValue The returned value if the searched one does not exist or isn't a float.
         * @returns The value as float of the given key in the root level, defaultValue if it does not exist or is not an float.
         */
        float getFloatValue(const string& key, float defaultValue) const;
        /**
         * @param key The key to search
         * @param defaultValue The returned value if the searched one does not exist or isn't a boolean.
         * @returns The value as boolean of the given key in the root level, defaultValue if it does not exist or is not a boolean.
         */
        bool getBoolValue(const string& key, bool defaultValue) const;

        /**
         * @param key The key to search
         * @returns The type of the key in the root level.
         */
        string getType(const string &key) const;

        /**
         * @param section The section to search
         * @returns Either the given section exists or not.
         */
        bool hasSection(const string& section) const;
        /**
         * @param key The key to search
         * @returns Either the root level contains the given key or not.
         */
        bool hasKey(const string& key) const;
        /**
         * @param section The section to search in
         * @param key The key to search
         * @returns Either the key exists or not in the given section. If the section does not exists, returns false.
         */
        bool hasKey(const string& section, const string& key) const;

    private:
        static string pairSeparator;

        int stringIsValidPair(const string& str) const;
        void assignFromRawString(const string& section, const string& str);

        // { section: { key: { type, value } } }
        map<string, map<string, pair<string, string>>> m_iniMap;
        // { key: { type, value } }
        map<string, pair<string, string>> m_rootMap;
        int m_sectionCount;
};

#endif // INISET_HPP