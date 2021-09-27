#include "MovableContainer.h"

void MovableContainer::Add(Movable& m) {
	items.push_back(&m);
}

void MovableContainer::Remove(Movable& m) {
	for (size_t i = 0; i < items.size(); i++)
	{
		if (&m == items[i]) {
			items.erase(items.begin() + i);
			break;
		}
	}
}

int MovableContainer::Count() {
	return items.size();
}
