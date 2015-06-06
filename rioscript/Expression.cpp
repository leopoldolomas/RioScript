#include <assert.h>
#include "Expression.h"
#include "ExpressionValue.h"

Expression::Expression(const char* operator_name, IExpression::ExpressionType type /*expressions*/) {
	assert(operator_name);

	m_type = type;
	m_operatorName = new char[strlen(operator_name)];
	strcpy(m_operatorName, operator_name);
}

const char* Expression::operatorName() {
	return m_operatorName;
}

std::vector<IExpression*>* Expression::arguments() {
	return &m_arguments;
}

IExpressionValue* Expression::evaluate() {
	switch (m_type) {
	case IExpression::NUMERIC:
		return new ExpressionValue(atof(m_operatorName));
		break;
	case IExpression::VAR:
		 // TODO retrieve value from memory
		break;
	case IExpression::OPERATOR:
		return funcs.at(m_operatorName)(&m_arguments);
		break;
	}
	return NULL;
}

IExpression::ExpressionType Expression::type() {
	return m_type;
}

Expression::~Expression() {
	delete[] m_operatorName;
}
