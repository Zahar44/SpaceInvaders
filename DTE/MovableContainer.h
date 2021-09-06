#pragma once
#include <vector>
#include <algorithm>

#include "Movable.h";

class MovableContainer
{
public:
	MovableContainer() {}

	void Add(Movable& m) {
		items.push_back(&m);
	}

	void Remove(Movable& m) {
		for (size_t i = 0; i < items.size(); i++)
		{
			if (&m == items[i]) {
				items.erase(items.begin() + i);
				break;
			}
		}
	}

	int Count() {
		return items.size();
	}

	Movable& operator[](int i) {
		return *items[i];
	}
private:
	std::vector<Movable*> items;
};

