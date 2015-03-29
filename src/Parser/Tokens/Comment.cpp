#include "Comment.hpp"

Comment::Comment(void) {
	_read.type = COMMENT;
}

Comment::~Comment(void) {
}

int		Comment::detect(const char &c) {
	bool		emptyWord(_read.word.empty());

	if (emptyWord && c == '#') {
		_read.word.push_back(c);
		return (MASTER);
	}
	if (!emptyWord && c == '\n') {
		return (COMPLETE);
	}
	if (!emptyWord) {
		_read.word.push_back(c);
		return (FOUND);
	}
	return (NONE);
}

int		Comment::getPriority(void) const {
	return (1);
}
