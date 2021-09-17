#include "Bitmap.h"
#include <string>
#include <windows.h>

void Bitmap::Resize(Grafic::Size _size) {
	_size.h = size.h;
	auto newData = new Color[_size.w * _size.h];

	int maxW = max(size.w, _size.w);
	int maxH = max(size.h, _size.h);

	double wScale = size.w / _size.w;

	if (wScale == 1)
		return;

	int index = 0;
	int offset = 0;
	for (size_t i = 0; i < _size.h; i++)
	{
		for (size_t j = 0; j < _size.w; j++)
		{
			if ((int)(index * wScale) > maxW * maxH)
				break;
			if (index > maxW * maxH)
				break;

			newData[index] = data[(int)(index * wScale)];
			index++;
		}

		if ((int)(index * wScale) > maxW * maxH)
			break;
		if (index > maxW * maxH)
			break;
	}

	if (data != nullptr)
		delete data;
	
	size = _size;
	OutputDebugString((std::to_wstring(size.w) + L" " + std::to_wstring(wScale) + L"\n").c_str());
	data = newData;
}

void Bitmap::LoadFile(const char* path) {
	std::ifstream file;
	file.open(path, std::ios_base::in | std::ios_base::binary);
	
	if (!file.is_open())
		throw std::exception("[Bitmap]: File not found");

	const int fileHeaderSize = 14;
	const int informationalHeaderSize = 108;
	char fileHeader[fileHeaderSize];
	char informationalHeader[informationalHeaderSize];

	file.read(fileHeader, fileHeaderSize);
	file.read(informationalHeader, informationalHeaderSize);

	const int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);
	const int width = informationalHeader[4] + (informationalHeader[5] << 8) + (informationalHeader[6] << 16) + (informationalHeader[7] << 24);
	const int heigth = informationalHeader[8] + (informationalHeader[9] << 8) + (informationalHeader[10] << 16) + (informationalHeader[11] << 24);
	
	size = { (double)width, (double)heigth };
	data = new Color[size.w * size.h];

	const int paddingAmount = ((4 - (width * 3) % 4) % 4);
	
	for (size_t i = 0; i < heigth; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			unsigned char color[4];
			file.read(reinterpret_cast<char*>(color), 4);

			data[i * width + j].r = color[0];
			data[i * width + j].g = color[1];
			data[i * width + j].b = color[2];
		}

		file.ignore(paddingAmount);
	}

	file.close();
}
