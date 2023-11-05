#include "Tracker.h"

using utils::Tracker;

inline std::string hashString(const std::string& input) {
	unsigned int hash = 0;

	for (char ch : input)
		hash += static_cast<unsigned int>(ch);

	return std::to_string(hash);
}

bool Tracker::hasValidExtension(const fs::path& file) noexcept
{
	if (filters.empty())
		return true;

	if (fs::exists(file) && fs::is_regular_file(file)) {
		std::string fileExtension = file.extension().string();

		return std::find(filters.begin(), filters.end(), fileExtension) != filters.end();
	}

	return false;
}

bool Tracker::hasInvaliPath(const std::string& fileName)
{
	for (std::string& path : invalidPaths) {
		path = path.substr(1); // Remove '!'

		if (fileName.find(path) != std::string::npos)
			return true;
	}

	return false;
}

void Tracker::traverseDirectory(const std::string& search, const fs::path& directory, Json::Value& files)
{
	for (const auto& entry : fs::directory_iterator(directory)) {
		std::string fileName = entry.path().filename().string();

		if (hasInvaliPath(fileName))
			continue;

		if (entry.is_directory()) {
			traverseDirectory(search, entry.path(), files);
		}
		else if (entry.is_regular_file() && hasValidExtension(entry.path())) {
			scanFile(search, entry.path().string(), files);
		}
	}
}

void Tracker::scanFile(const std::string& search, const std::string& fileName, Json::Value& files)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		UINT cont = 0;
		std::string line;
		std::string hash = hashString(fileName);

		while (std::getline(file, line)) {
			if (line.find(search) != std::string::npos) {
				if (!files.isMember(hash)) {
					Json::Value fileJSON;
					fileJSON["path"] = fileName;
					files[hash] = fileJSON;
				}

				Json::Value lineJSON;
				lineJSON["content"] = line;
				lineJSON["num"] = ++cont;

				files[hash]["lines"].append(lineJSON);
			}
		}

		file.close();
	}
	else {
		std::cerr << "Couldn't open file " << fileName << std::endl;
	}
}

Json::Value Tracker::search(const std::vector<std::string>& keywords)
{
	Json::Value files;

	for (const std::string& keyword : keywords) {
		for (std::string& path : validPaths) {
			const fs::path dir(path);
			traverseDirectory(keyword, dir, files);
		}
	}

	return files;
}

void Tracker::setFilters(std::vector<std::string> filters) noexcept
{
	this->filters = filters;
}

void Tracker::setPaths(std::vector<std::string> paths) noexcept
{
	for (std::string& path : paths) {
		if (path[0] == '!')
			invalidPaths.push_back(path);
		else
			validPaths.push_back(path);
	}
}
