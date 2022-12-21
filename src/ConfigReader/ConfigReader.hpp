#ifndef CONFIGREADER_HPP
#define CONFIGREADER_HPP

#include "config_interfaces.hpp"
#include "utils/IniSet/IniSet.hpp"

class ConfigReader {
	public:
		ConfigReader();
		~ConfigReader();

		AppConfig loadFromFile(const char* filepath);

	private:
		IniSet m_config;
};

#endif // CONFIGREADER_HPP