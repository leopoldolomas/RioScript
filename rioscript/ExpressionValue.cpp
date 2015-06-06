#include "ExpressionValue.h"

ExpressionValue::ExpressionValue(double value) {
	m_type = IExpressionValue::DOUBLE;
	m_intValue = (int)value;
	m_doubleValue = value;
}

IExpressionValue::ValueType ExpressionValue::type() {
	return m_type;
}

int ExpressionValue::valueAsInt() {
	return m_intValue;
}

double ExpressionValue::valueAsDouble() {
	return m_doubleValue;
}

const char* ExpressionValue::valueAsCStr() {
	return NULL; // TODO
}

ExpressionValue::~ExpressionValue() {
}
