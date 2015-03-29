#include "Scope.hpp"
#include <ctype.h>

Scope::Scope(void) {
	_read.type = SCOPE;
}

Scope::~Scope(void) {
}

int			Scope::detect(const char &c) {
	bool		empty(isEmptyWord());

	if (empty && (c == '(' || c == ')')) {
		_read.word.push_back(c);
		return (FOUND);
	}
	if (!isEmptyWord()) {
		return (COMPLETE);
	} else {
		return (NONE);
	}
}

int			Scope::getPriority(void) const {
	return (1);
}
