#include "Parser.hpp"
#include "Number.hpp"
#include "Scope.hpp"
#include "Comment.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

Parser::Parser(void) {
}

Parser::~Parser(void) {
	for (tSetTokens::iterator iTok = _globalTokens.begin(); iTok != _globalTokens.end(); ++iTok) {
		delete (*iTok);
	}
}

Parser::Parser(const std::string &filename) {
	std::ifstream		ifs(filename.c_str());

	initGlobalTokens();
	if (ifs.fail()) {
		std::cout << "File is not valid" << std::endl;
		return ;
	}
	exec(ifs);
}

void			Parser::exec(std::ifstream &ifs) {
	char				c;
	int					n;
	int					nbToken;
	size_t				tokenMask;
	int					response;
	std::string			line;

	nbToken = _globalTokens.size();
	tokenMask = (1L << _globalTokens.size()) - 1;
	while (ifs.get(c)) {
		for (n = 0; n < nbToken; ++n) {
			if (!((tokenMask >> n) & 1)) {
				continue ;
			}
			response = _globalTokens[n]->detect(c);
			if (response == FOUND) {
				continue ;
			} else if (response == COMPLETE) {
				_readTokens.push_back(_globalTokens[n]->getAsRead());
				resetGlobalTokens();
				tokenMask = (1L << _globalTokens.size()) - 1;
				n = -1;
			} else if (response == MASTER) {
				tokenMask = (1L << n);
			} else if (response == NONE) {
				tokenMask &= ~(1L << n);
				if (tokenMask == 0) {
					if (!isSeparator(c)) {
						std::cout << "\033[1;31mParsing error on char\033[0m:\t" << c << std::endl;
						std::cout << "Unrecognized symbol." << std::endl;
					} else if (tokenizing()) {
						std::cout << "\033[1;31mParsing error on char\033[0m:\t" << c << std::endl;
						std::cout << "Unfinished expression." << std::endl;
					}
					resetGlobalTokens();
					tokenMask = (1L << _globalTokens.size()) - 1;
				}
			}
		}
	}
}

bool			Parser::isSeparator(char const &c) {
	return (c == ' ' || c == ',' || c == '\t' || c == '\n');
}

bool			Parser::tokenizing(void) const {
	for (tSetTokens::const_iterator iTok = _globalTokens.begin(); iTok != _globalTokens.end(); ++iTok) {
		if (!(*iTok)->isEmptyWord()) {
			return (true);
		}
	}
	return (false);
}

void			Parser::resetGlobalTokens(void) {
	for (tSetTokens::iterator iTok = _globalTokens.begin(); iTok != _globalTokens.end(); ++iTok) {
		(*iTok)->reset();
	}
}

void			Parser::initGlobalTokens(void) {
	_globalTokens.push_back(new Number());
	_globalTokens.push_back(new Scope());
	_globalTokens.push_back(new Comment());
}

void			Parser::display(void) {
	for (tTokens::iterator iTok = _readTokens.begin(); iTok != _readTokens.end(); ++iTok) {
		std::cout << "READ:\t" << iTok->buffer << " of type " << iTok->type << std::endl;
	}
}

const std::vector<sReadToken>		Parser::getRead(void) const {
	return (_readTokens);
}
