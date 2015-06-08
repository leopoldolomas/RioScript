//--------------------------------------------------------------- @License begins
// "FSXAssistant"
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
