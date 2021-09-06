#pragma once
#include <fstream>

struct Color
{
	char r, g, b;
};

class Bitmap {
public:
	Bitmap() {}

	Bitmap(const char* path) {
		LoadFile(path);
	}

	~Bitmap() {
		delete data;
	}

	size_t operator[](int i) {
		if (i > size)
			throw std::exception("Out of range");
		return ((data[i].r & 0xff) << 16) + ((data[i].g & 0xff) << 8) + (data[i].b & 0xff);
	}

	size_t Size() {
		return size;
	}

	void LoadFile(const char* path);
private:
	Color* data;
	size_t size;
};

