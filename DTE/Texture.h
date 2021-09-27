#pragma once
#include <vector>
#include <string>

#include "Drawer.h"

using std::string;
using std::vector;

struct PixelInfo {
	double color;
	bool exist;
};

class Texture {
public:
	Texture(const char* path);

	void LoadFile(const char* path);

	int Size() {
		return size;
	}
	int Size(int i) {
		if (data[i].size() < i)
			throw std::exception("[Texture]: index out of range");

		return data[i].size();
	}

	int MaxRowSize();
	int ColSize();
	
	PixelInfo operator [](int index);
private:
	vector<vector<PixelInfo>> data;
	int size;

	void LoadLine(string line);
	PixelInfo& GetPixel(string value);
};

