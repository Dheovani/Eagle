#include "BWriter.h"

using namespace utils;

BWriter::BWriter(const std::string& name) : file(name + EXT)
{
	ofstream fout(file, ios::binary | ios::app);
}

void BWriter::overrideRecords(std::vector<Record> records) const
{
	ofstream fout(file, ios::out | ios::binary);

	size_t i, size = records.size();
	Record* daoArray = new Record[size];

	for (i = 0; i < size; i++)
		daoArray[i] = records.at(i);

	if (fout) {
		fout.write(reinterpret_cast<char*>(daoArray), sizeof(Record) * size);
		fout.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}

	delete[] daoArray;
}

void BWriter::write(Record value) const
{
	auto records = readAll();
	for (const auto& rec : records) {
		if (rec.data == value.data)
			return;
	}

	ofstream fout(file, ios::binary | ios::app);

	if (fout) {
		fout.write(reinterpret_cast<char*>(&value), sizeof(value));
		fout.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}
}

void BWriter::write(Record values[]) const
{
	ofstream fout(file, ios::binary | ios::app);

	if (fout) {
		size_t size = sizeof(values) / sizeof(values[0]);
		fout.write(reinterpret_cast<char*>(values), sizeof(Record) * size);
		fout.close();
	}
	else {
		std::cerr << "Error opening file!!" << std::endl;
	}
}

Record BWriter::read(UINT id) const
{
	ifstream fin(file, ios::binary | ios::in);

	if (fin) {
		Record record;
		while (fin.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
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

std::vector<Record> BWriter::readAll() const
{
	std::vector<Record> result;
	ifstream fin(file, ios::binary);

	if (fin) {
		Record record;
		while (fin.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
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
	std::vector<Record> records = readAll();

	auto it = std::remove_if(records.begin(), records.end(), [targetId](const Record& record) {
		return record.id == targetId;
	});

	if (it != records.end()) {
		records.erase(it, records.end());
	}

	overrideRecords(records);
}
