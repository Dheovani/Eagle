#include "BWriter.h"

using namespace utils;

BWriter::BWriter(const std::string& name) : file(name + EXT)
{
	fstream fout;
	fout.open(file, ios::out | ios::binary);
}

void BWriter::overrideRecords(std::vector<Dao> records) const
{
	fstream fout(file, ios::out | ios::binary);

    size_t i, size = records.size();
	Dao* daoArray = new Dao[size];

    for (i = 0; i < size; i++)
        daoArray[i] = records.at(i);

    if (fout) {
        fout.write(reinterpret_cast<char*>(daoArray), sizeof(Dao) * size);
        fout.close();
    }
    else {
		std::cerr << "Error opening file!!" << std::endl;
    }

	delete[] daoArray;
}

void BWriter::write(Dao value) const
{
	fstream fout;
	fout.open(file, ios::app | ios::binary);

	if (fout) {
		fout.write(reinterpret_cast<char*>(&value), sizeof(value));
		fout.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}
}

void BWriter::write(Dao values[]) const
{
	fstream fout;
	fout.open(file, ios::app | ios::binary);

	if (fout) {
		size_t size = sizeof(values) / sizeof(values[0]);
		fout.write(reinterpret_cast<char*>(values), sizeof(Dao) * size);
		fout.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}
}

Dao BWriter::read(UINT id) const
{
	fstream fin;
	fin.open(file, ios::in | ios::binary);

	if (fin) {
		Dao record;
		while (fin.read(reinterpret_cast<char*>(&record), sizeof(Dao))) {
			if (record.id == id) {
				fin.close();
				return record;
			}
		}

		fin.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}

	throw std::exception("Value not found!");
}

std::vector<Dao> BWriter::readAll() const
{
	std::vector<Dao> result;
	fstream fin;
	fin.open(file, ios::in | ios::binary);

	if (fin) {
		Dao record;
		while (fin.read(reinterpret_cast<char*>(&record), sizeof(Dao))) {
			result.push_back(record);
		}

		fin.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}

	return result;
}

UINT BWriter::nextId() const
{
	return readAll().size();
}

void BWriter::deleteRecord(UINT targetId) const
{
	std::vector<Dao> records = readAll();

	auto it = std::remove_if(records.begin(), records.end(), [targetId](const Dao& record) {
		return record.id == targetId;
	});

	if (it != records.end()) {
		records.erase(it, records.end());
	}

	overrideRecords(records);
}
