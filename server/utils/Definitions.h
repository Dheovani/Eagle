#pragma once

#include <vector>
#include <string>

#define EXT ".dat"
#define MAX_PATH 260 // Windows' max size for a file path

typedef unsigned int UINT;

typedef struct Record {
	UINT id;
	char data[MAX_PATH];
} Record;
