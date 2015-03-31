#include "Number.hpp"
#include <ctype.h>

Number::Number(void) {
}

Number::~Number(void) {
}

int			Number::detect(const char &c) {
	if (isdigit(c)) {
		_buffer.push_back(c);
		return (FOUND);
	}
	if (!isEmptyWord()) {
		return (COMPLETE);
	} else {
		return (NONE);
	}
}

int			Number::getType(void) const {
	return (NUMBER);
}
