#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include "json/json.h"
#include "Definitions.h"

namespace fs = std::filesystem;

namespace utils
{
	class Tracker
	{
	private:
		std::vector<std::string> filters = std::vector<std::string>{};
		std::vector<std::string> validPaths = std::vector<std::string>{};
		std::vector<std::string> invalidPaths = std::vector<std::string>{};

		bool hasValidExtension(const std::string& fileName) noexcept;

		void traverseDirectory(const std::string& search, const fs::path& directory, Json::Value& files);

		void scanFile(const std::string& search, const std::string& fileName, Json::Value& files);

	public:
		Json::Value search(const std::vector<std::string>& keywords);

		void setFilters(std::vector<std::string> filters) noexcept;

		void setPaths(std::vector<std::string> paths) noexcept;
	};
}