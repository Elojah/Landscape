#ifndef PARSER_H
# define PARSER_H

# include <set>
# include <vector>
# include <string>

# include "IToken.hpp"
class IToken;

class Parser
{
public:
	Parser(const std::string &filename);
	~Parser(void);
	void									display(void);
	const std::vector<sReadToken>		getRead(void) const;
protected:
private:
	typedef		std::vector<IToken *>				tSetTokens;
	typedef		std::vector<sReadToken>			tTokens;

	Parser(void);

	void									initGlobalTokens(void);
	void									resetGlobalTokens(void);
	void									exec(std::ifstream &ifs);
	bool									tokenizing(void) const;
	static bool								isSeparator(char const &c);


	tSetTokens								_globalTokens;
	tTokens									_readTokens;
};

#endif
