#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#define EXT ".dat"
#define MAX_PATH 260 // Windows' max size for a file path

using std::ofstream, std::ifstream, std::ios;

typedef unsigned int UINT;

namespace utils
{
	typedef struct Record {
		UINT id;
		char data[MAX_PATH];
	} Record;

	class BWriter final
	{
	private:
		std::string file;

		void overrideRecords(std::vector<Record> records) const;

	public:
		BWriter(const std::string& name);

		void write(Record value) const;

		void write(Record values[]) const;

		Record read(UINT id) const;

		std::vector<Record> readAll() const;

		UINT nextId() const;

		void deleteRecord(UINT targetId) const;
	};
}
