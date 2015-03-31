#ifndef I_TOKEN_H
# define I_TOKEN_H

# include <string>
# include <set>
# include <ctype.h>
# include <iostream>

struct sReadToken{
	std::string		buffer;
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
	virtual int				getType(void) const = 0;
	virtual void				reset(void) {
		_buffer.clear();
	}
	virtual sReadToken		getAsRead(void) const {
		return ((sReadToken){_buffer, getType()});
	}
	virtual bool				isEmptyWord(void) const {
		return (_buffer.empty());
	}
	virtual void				display(void) const {
		std::cout << _buffer << std::endl;
	}
protected:
	std::string				_buffer;
private:
};

#endif
