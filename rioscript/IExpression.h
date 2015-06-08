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