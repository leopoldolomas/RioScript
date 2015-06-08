//--------------------------------------------------------------- @License begins
// 2015 Leopoldo Lomas Flores. Torreon, Coahuila. MEXICO
// leopoldolomas [at] gmail
// www.leopoldolomas.info
// 
// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
// software, either in source code form or as a compiled binary, for any purpose,
// commercial or non-commercial, and by any means.
// 
// In jurisdictions that recognize copyright laws, the author or authors of this
// software dedicate any and all copyright interest in the software to the public
// domain. We make this dedication for the benefit of the public at large and to
// the detriment of our heirs and successors. We intend this dedication to be
// an overt act of relinquishment in perpetuity of all present and future
// rights to this software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//--------------------------------------------------------------- @License ends

#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "HelperFuncs.hpp"
#include "Parser.h";
#include "Expression.h"

Parser::Parser() {
}

std::vector<IExpression*> Parser::parseFile(const char* filename) {
	std::string line;
	std::ifstream fileStream(filename);

	std::stringstream stringStream;

	if (fileStream.is_open()) {
		while (getline(fileStream, line)) {
			size_t index = line.find(';');
			if (index <= line.size()) {
				line.erase(index); // remove comments from source code
			}
			stringStream << line;
		}
		fileStream.close();
	}
	else {
		// TODO
	}

	std::string fileContents = stringStream.str();
	char* mystring = new char[fileContents.length()];
	strcpy(mystring, fileContents.c_str());

	return parseFileContents(mystring);
}

std::vector<std::string> Parser::splitExpression(const std::string& expressionStr) {
	std::string expression = expressionStr.substr(1, expressionStr.size() - 2);
	std::vector<std::string> expressionElements;

	bool isReadingExpression = false;
	int startIndex = 0;

	for (int i = 0; i < expression.size(); i++) {
		if (expression.at(i) == '(') {
			isReadingExpression = true;
		} else {			
			bool eol = (i == expression.size() - 1);
			char argumentEnd = isReadingExpression ? ')' : ' ';
			if (eol || expression.at(i) == argumentEnd) {
				int offset = (eol ? 1 : 0);
				expressionElements.push_back(expression.substr(
					startIndex, i - startIndex + (isReadingExpression ? 1 : 0) + offset));
				startIndex = i + 1;
				isReadingExpression = false;
			}
		}
	}

	return expressionElements;
}

std::string& Parser::formatFileContents(std::string& s) {
	replaceChar(s, '\t', ' ');
	trim(s);
	removeDuplicateSpaces(s);
	replaceSubstring(s, "( ", "(");
	replaceSubstring(s, " )", ")");
	replaceSubstring(s, ") ", ")");

	return s;
}

std::vector<IExpression*> Parser::parseFileContents(const char* fileContents) {
	assert(fileContents != NULL);

	int len = strlen(fileContents);
	assert(len > 0);
	//assert(expression[0] == '(');
	//assert(expression[len - 1] == ')');
	std::vector<IExpression*> expressions;

	std::string fileContentsStr = std::string(fileContents);
	formatFileContents(fileContentsStr);
	assert(fileContentsStr.at(0) == '(');

	int index = 0;
	int subexpressionCount = 0;
	for (int i = index; i < fileContentsStr.length(); i++) {
		switch (fileContentsStr.at(i)) {
		case '(':
			subexpressionCount++;
			break;
		case ')':
			subexpressionCount--;
			break;
		}
		if (subexpressionCount == 0) {
			expressions.push_back(parseExpression(fileContentsStr.substr(index, (i - index + 1)).c_str()));
			index = i + 1;
			if (index < fileContentsStr.length()) {
				assert(fileContentsStr.at(index) == '(');
			}
		}
	}
	return expressions;
}

IExpression* Parser::parseExpression(const char* expression_str) {
	assert(expression_str != NULL);
	assert(strlen(expression_str) > 0);

	Expression* expression = NULL;

	bool isExpression = (expression_str[0] == '(');
	std::string expressionStr = std::string(expression_str);

	std::vector<std::string> expressionElements;
	if (isExpression) {
		expressionElements = splitExpression(expression_str);
		expression = new Expression(expressionElements.at(0).c_str(), IExpression::OPERATOR);

		for (int i = 1; i < expressionElements.size(); i++) {
			IExpression* exp = parseExpression(expressionElements.at(i).c_str());
			expression->arguments()->push_back(exp);			
		}
	} else {
		IExpression::ExpressionType type = IExpression::VAR;
		if (expressionStr.at(0) == '\"' && expressionStr.at(expressionStr.size() - 1) == '\"') {
			type = IExpression::STRING;
		} else {
			double number = -1.0f;
			number = atof(expressionStr.c_str()); // TODO a better approach is needed to identify numbers

			type = (number != 0.0 ? IExpression::NUMERIC : IExpression::VAR);
			expression = new Expression(expressionStr.c_str(), type);
		}
	}

	return expression;
}

Parser::~Parser() {
}
