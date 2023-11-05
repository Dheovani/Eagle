#pragma once

#include <iostream>
#include <fstream>
#include "Definitions.h"

using std::ofstream, std::ifstream, std::ios;

namespace utils
{
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
