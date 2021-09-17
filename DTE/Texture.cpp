#include "Texture.h"
#include <fstream>
#include <sstream>

Texture::Texture(const char* path) {
	size = 0;

	LoadFile(path);
}

void Texture::LoadFile(const char* path) {
	std::ifstream file;
	file.open(path, std::ios_base::in);

	if (!file.is_open())
		throw std::exception("[Bitmap]: File not found");

	string line;
	while (std::getline(file, line)) {
		LoadLine(line);
	}
}

void Texture::LoadLine(string line) {
	vector<string> lineData = *new vector<string>();
	
	string pixel = "";
	for (size_t i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ') {
			pixel += line[i];
		}
		else {
			lineData.push_back(pixel);
			size++;
			pixel = "";
		}
	}
	lineData.push_back(pixel);
	size++;
	data.push_back(lineData);
}

int Texture::MaxRowSize() {
	int max = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		max = data[i].size() > max ? data[i].size() : max;
	}
	return max;
}


int Texture::ColSize() {
	return data.size();
}




double Texture::operator[](int index) {
	int k = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].size(); j++)
		{
			if (k++ == index)
				return std::stod(data[i][j]);
		}
	}

	throw std::exception("[Texture]: index out of range");
}