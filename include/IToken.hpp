#ifndef I_TOKEN_H
# define I_TOKEN_H

# include <string>
# include <set>
# include <ctype.h>
# include <iostream>

struct sReadToken{
	std::string		word;
	int				type;
};

enum {
	NONE = 0,
	FOUND,
	COMPLETE,
	MASTER
};

enum {
	NO_VALID = 0,
	NUMBER,
	SCOPE,
	COMMENT
};

class IToken
{
public:
	virtual ~IToken(void) {};

	typedef std::set<std::string>		tSymbols;

	virtual int				detect(const char &c) = 0;
	virtual int				getPriority(void) const = 0;
	virtual void				reset(void) {
		_read.word.clear();
	}
	virtual sReadToken		getAsRead(void) const {
		return (_read);
	}
	virtual bool				isEmptyWord(void) const {
		return (_read.word.empty());
	}
	virtual void				display(void) const {
		std::cout << _read.word << std::endl;
	}
protected:
	sReadToken			_read;
	tSymbols				_sym;
private:
};

#endif
