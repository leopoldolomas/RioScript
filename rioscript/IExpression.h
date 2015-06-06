#ifndef _IEXPRESSION_H_
#define _IEXPRESSION_H_

#include <vector>
#include <map>
#include "stdafx.h"

#ifndef REGISTER_FUNCTION
#define REGISTER_FUNCTION(str, func) IExpression::funcs.insert(std::make_pair(str, func));
#endif

class IExpression;
class IExpressionValue;

typedef IExpressionValue*(*ScriptFunction)(std::vector<IExpression*>*); // function pointer type

class IExpressionValue {
public:
	enum ValueType { INT = 0, DOUBLE = 1, STRING = 2 };

	virtual ValueType type() = 0;
	virtual int valueAsInt() = 0;
	virtual double valueAsDouble() = 0;
	virtual const char* valueAsCStr() = 0;
};

class IExpression {
public:
	enum ExpressionType { NUMERIC = 0, STRING = 1, VAR = 2, OPERATOR = 3 };

	virtual const char* operatorName() = 0;
	virtual IExpressionValue* evaluate() = 0;
	virtual std::vector<IExpression*>* arguments() = 0;
	virtual ExpressionType type() = 0;
	virtual ~IExpression() { }

//private:
	static std::map<std::string, ScriptFunction> funcs;
};

#endif // _IEXPRESSION_H_