#ifndef _PARSER_H_
#define _PARSER_H_

#include "Expression.h"

class Parser {
public:
	Parser();

	std::vector<IExpression*> parseFile(const char* filename);

	~Parser();

private:
	std::vector<std::string> splitExpression(const std::string& expression);
	std::string& formatFileContents(std::string& fileContents);
	std::vector<IExpression*> parseFileContents(const char* fileContents);
	IExpression* parseExpression(const char* expression);
};

#endif // _PARSER_H_