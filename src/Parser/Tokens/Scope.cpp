#include "Scope.hpp"
#include <ctype.h>

Scope::Scope(void) {
}

Scope::~Scope(void) {
}

int			Scope::detect(const char &c) {
	bool		empty(isEmptyWord());

	if (empty && (c == '(' || c == ')')) {
		_buffer.push_back(c);
		return (FOUND);
	}
	if (!isEmptyWord()) {
		return (COMPLETE);
	} else {
		return (NONE);
	}
}

int			Scope::getType(void) const {
	return (SCOPE);
}
