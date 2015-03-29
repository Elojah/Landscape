#ifndef COMMENT_H
# define COMMENT_H

# include "IToken.hpp"

class Comment : public IToken
{
public:
	Comment(void);
	~Comment(void);
	int				detect(const char &c);
	int				getPriority(void) const;
protected:
private:
};

#endif
