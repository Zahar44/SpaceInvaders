#include "Texture.h"
#include <fstream>
#include <sstream>
#include <algorithm>

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
		line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
		LoadLine(line);
	}
}

void Texture::LoadLine(string line) {
	std::stringstream stream(line);
	string value;
	vector<PixelInfo> pixels;

	while (std::getline(stream, value, ',')) {
		pixels.push_back(GetPixel(value));
		size++;
	}

	data.push_back(pixels);
}

PixelInfo& Texture::GetPixel(string value) {
	PixelInfo pixel = { 0xffffff, false };

	if (value[0] == '{') {
		pixel.exist = value.substr(value.find_first_of('{') + 1, value.find_first_of(':') - 1) == "1";
		string s = value.substr(value.find_first_of(':') + 1, value.find_first_of('}') - 3);
		pixel.color = stod(s);
	}
	else {
		pixel.exist = std::stoi(value);
	}

	return pixel;
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




PixelInfo Texture::operator[](int index) {
	int k = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[i].size(); j++)
		{
			if (k++ == index)
				return data[i][j];
		}
	}

	throw std::exception("[Texture]: index out of range");
}