#pragma once

#include <vector>
#include <string>

#define EXT ".dat"
#define MAX_PATH 260 // Windows' max size for a file path

typedef struct Record {
	size_t id;
	char data[MAX_PATH];

	bool operator==(const Record& rec) const {
		return std::strcmp(data, rec.data) == 0;
	}
} Record;
