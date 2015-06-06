#ifndef _EXPRESSION_VALUE_H
#define _EXPRESSION_VALUE_H

#include "IExpression.h"
class ExpressionValue : public IExpressionValue
{
public:
	ExpressionValue(double value);
	/*ExpressionValue(int value);
	ExpressionValue(const char* value);*/
	~ExpressionValue();

	virtual ValueType type();

	virtual int valueAsInt();
	virtual double valueAsDouble();
	virtual const char* valueAsCStr();
	
protected:
	ValueType m_type;

	int m_intValue;
	double m_doubleValue;
	const char* m_strValue;
};

#endif // _EXPRESSION_VALUE_H
