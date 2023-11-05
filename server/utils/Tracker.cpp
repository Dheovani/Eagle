#include "Tracker.h"

using utils::Tracker;

inline UINT hashString(const std::string& input) {
	UINT hash = 0;

	for (char ch : input)
		hash = (hash * 31) + static_cast<unsigned int>(ch);

	return hash;
}

bool Tracker::hasValidExtension(const std::string& fileName) noexcept
{
	fs::path filePath(fileName);

	if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
		std::string fileExtension = filePath.extension().string();

		if (!fileExtension.empty() && fileExtension[0] == '.') {
			fileExtension = fileExtension.substr(1);
		}

		return std::find(filters.begin(), filters.end(), fileExtension) != filters.end();
	}

	return false;
}

void Tracker::traverseDirectory(const std::string& search, const fs::path& directory, Json::Value& files)
{
	for (const auto& entry : fs::directory_iterator(directory)) {
		std::string fileName = entry.path().filename().string();

		if (std::find(invalidPaths.begin(), invalidPaths.end(), fileName) != invalidPaths.end())
			continue;

		if (entry.is_directory()) {
			traverseDirectory(search, entry.path(), files);
		}
		else if (entry.is_regular_file() && hasValidExtension(fileName)) {
			scanFile(search, fileName, files);
		}
	}
}

void Tracker::scanFile(const std::string& search, const std::string& fileName, Json::Value& files)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::string line;
		UINT cont = 1;

		while (std::getline(file, line)) {
			if (line.find(search) != std::string::npos) {
				UINT hash = hashString(fileName);

				if (files[hash].isNull()) {
					Json::Value file;
					file["path"] = fileName;

					files[hash] = file;
				}

				Json::Value lineJSON;
				lineJSON["content"] = line;
				lineJSON["num"] = cont;

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
