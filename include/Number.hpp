#ifndef NUMBER_H
# define NUMBER_H

# include "IToken.hpp"

class Number : public IToken
{
public:
	Number(void);
	~Number(void);
	int				detect(const char &c);
	int				getPriority(void) const;
protected:
private:
};

#endif
