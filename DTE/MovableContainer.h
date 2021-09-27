#pragma once
#include <vector>
#include <algorithm>

#include "Movable.h";

class MovableContainer {
public:
	MovableContainer() {}

	void Add(Movable& m);
	void Remove(Movable& m);
	int Count();
	
	Movable& operator[](int i) {
		return *items[i];
	}
private:
	std::vector<Movable*> items;
};

