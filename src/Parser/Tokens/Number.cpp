#include "Number.hpp"
#include <ctype.h>

Number::Number(void) {
	_read.type = NUMBER;
}

Number::~Number(void) {
}

int			Number::detect(const char &c) {
	if (isdigit(c)) {
		_read.word.push_back(c);
		return (FOUND);
	}
	if (!isEmptyWord()) {
		return (COMPLETE);
	} else {
		return (NONE);
	}
}

int			Number::getPriority(void) const {
	return (1);
}
