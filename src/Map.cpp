#include "Map.hpp"
#include "IObject.hpp"
#include "Camera.hpp"

Map::Map(void) {
}

Map::~Map(void) {
}

void	Map::addObject(IObject *obj) {
	_objects.push_back(obj);
}

void	Map::draw(void) const {
	for (std::vector<IObject *>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
		(*it)->draw();
	}
}

void	Map::refresh(Camera const &cam) const {
	for (std::vector<IObject *>::const_iterator it = _objects.begin(); it != _objects.end(); ++it) {
		(*it)->refresh(cam);
	}
}
