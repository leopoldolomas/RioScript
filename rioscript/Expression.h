#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <vector>
#include "stdafx.h"
#include "IExpression.h"

class Expression : public IExpression {
public:
	Expression(const char* operator_name, ExpressionType type /*expressions...*/);

	virtual const char* operatorName();
	virtual IExpressionValue* evaluate();
	virtual std::vector<IExpression*>* arguments();
	virtual ExpressionType type();

	virtual ~Expression();

private:
	ExpressionType m_type;
	char* m_operatorName;
	std::vector<IExpression*> m_arguments;
};

#endif // _EXPRESSION_H_
