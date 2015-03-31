#include "Comment.hpp"

Comment::Comment(void) {
}

Comment::~Comment(void) {
}

int		Comment::detect(const char &c) {
	bool		emptyWord(_buffer.empty());

	if (emptyWord && c == '#') {
		_buffer.push_back(c);
		return (MASTER);
	}
	if (!emptyWord && c == '\n') {
		return (COMPLETE);
	}
	if (!emptyWord) {
		_buffer.push_back(c);
		return (FOUND);
	}
	return (NONE);
}

int		Comment::getType(void) const {
	return (COMMENT);
}
