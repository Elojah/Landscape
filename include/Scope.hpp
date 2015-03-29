#ifndef SCOPE_H
# define SCOPE_H

# include "IToken.hpp"

class Scope : public IToken
{
public:
	Scope(void);
	~Scope(void);
	int				detect(const char &c);
	int				getPriority(void) const;
protected:
private:
};

#endif
