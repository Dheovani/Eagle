#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#define EXT ".dat"

using std::fstream, std::ios;
typedef unsigned int UINT;

namespace utils
{
	typedef struct Dao {
		UINT id;
		std::string data;
	} Dao;

	class BWriter final
	{
	private:
		std::string file;

		void overrideRecords(std::vector<Dao> records) const;

	public:
		BWriter(const std::string& name);

		void write(Dao value) const;

		void write(Dao values[]) const;

		Dao read(UINT id) const;

		std::vector<Dao> readAll() const;

		UINT nextId() const;

		void deleteRecord(UINT targetId) const;
	};
}
