#ifndef CONFIGREADER_HPP
#define CONFIGREADER_HPP

#include "config_interfaces.hpp"
#include "IniSet.hpp"

class ConfigReader {
	public:
		ConfigReader();
		~ConfigReader();

		AppConfig loadFromFile(char* filepath);

	private:
		IniSet m_config;
};

#endif // CONFIGREADER_HPP