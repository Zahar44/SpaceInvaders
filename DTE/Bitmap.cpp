#include "Bitmap.h"

void Bitmap::LoadFile(const char* path) {
	std::ifstream file;
	file.open(path);
	
	if (!file.is_open())
		throw std::exception("Can not open file");

	const int fileHeaderSize = 14;
	const int informationalHeaderSize = 14;
	char fileHeader[fileHeaderSize];
	char informationalHeader[informationalHeaderSize];

	file.read(fileHeader, fileHeaderSize);
	file.read(informationalHeader, informationalHeaderSize);

	const int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
	const int width = informationalHeader[4] + (informationalHeader[5] << 8) + (informationalHeader[6] << 16) + (informationalHeader[7] << 24);
	const int heigth = informationalHeader[8] + (informationalHeader[9] << 8) + (informationalHeader[10] << 16) + (informationalHeader[11] << 24);

	size = width * heigth;
	data = new Color[size];

	const int paddingAmount = ((4 - (width * 3) % 4) % 4);

	for (size_t i = 0; i < heigth; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			unsigned char color[3];
			file.read(reinterpret_cast<char*>(color), 3);
			data[i * width + j].r = color[2];
			data[i * width + j].g = color[1];
			data[i * width + j].b = color[0];
		}

		file.ignore(paddingAmount);
	}

	file.close();
}
