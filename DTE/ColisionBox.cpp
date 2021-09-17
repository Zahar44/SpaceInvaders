#include "ColisionBox.h"

ColisionBox::ColisionBox() {
}

ColisionBox::ColisionBox(Size size, Point point, double color) {
	this->size = size;
	this->point = point;
	this->color = color;
}

std::vector<ColisionBox*>* ColisionBox::Create(Texture& texture, Size size, Point point) {
	std::vector<ColisionBox*>* out = new std::vector<ColisionBox*>();
	
	int hSize = texture.ColSize();
	const double smoothCoef = 0.1;
	Size blockSize = { size.w / texture.MaxRowSize(), size.h / texture.ColSize() };

	int k = 0;
	for (size_t i = 0; i < hSize; i++)
	{
		int wSize = texture.Size(i);
		for (size_t j = 0; j < wSize; j++)
		{
			if (texture[k++] != 0)
				out->push_back(new ColisionBox(blockSize, point, 0xffffff));
			point.x += blockSize.w - smoothCoef;
		}
		point.x -= (blockSize.w - smoothCoef) * wSize;
		point.y -= blockSize.h - smoothCoef;
	}

	return out;
}
