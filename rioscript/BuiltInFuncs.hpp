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

#ifndef _FUNCS_H_
#define _FUNCS_H_

#include <assert.h>
#include "IExpression.h"
#include "ExpressionValue.h"

namespace BuiltInFuncs {
	IExpressionValue* sum(std::vector<IExpression*>* args) {
		assert(args != NULL);
		assert(args->size() > 0);

		double result = 0.0;
		for (auto it = args->begin(); it != args->end(); ++it) {
			auto value = (*it)->evaluate();
			assert(value->type() == IExpressionValue::DOUBLE || value->type() == IExpressionValue::INT);
			result += value->valueAsDouble();
		}
		return new ExpressionValue(result);
	}

	IExpressionValue* sub(std::vector<IExpression*>* args) {
		assert(args != NULL);
		assert(args->size() > 0);

		double result = args->at(0)->evaluate()->valueAsDouble() * (args->size() == 1 ? -1.0 : 1.0);
		for (auto it = args->begin() + 1; it != args->end(); ++it) {
			auto value = (*it)->evaluate();
			assert(value->type() == IExpressionValue::DOUBLE || value->type() == IExpressionValue::INT);
			result -= value->valueAsDouble();
		}
		return new ExpressionValue(result);
	}

	IExpressionValue* mul(std::vector<IExpression*>* args) {
		assert(args != NULL);

		double result = 1.0;

		if (args->size() > 0) {

			for (auto it = args->begin(); it != args->end(); ++it) {
				auto value = (*it)->evaluate();
				assert(value->type() == IExpressionValue::DOUBLE || value->type() == IExpressionValue::INT);
				result *= value->valueAsDouble();
			}
		}

		return new ExpressionValue(result);
	}

	IExpressionValue* div(std::vector<IExpression*>* args) {
		assert(args != NULL);
		assert(args->size() > 0);

		bool isSingleArgument = (args->size() == 1);
		double result = (isSingleArgument ? 1.0 : args->at(0)->evaluate()->valueAsDouble());
		int offset = (isSingleArgument ? 0 : 1);

		for (auto it = args->begin() + offset; it != args->end(); ++it) {
			auto value = (*it)->evaluate();
			assert(value->type() == IExpressionValue::DOUBLE || value->type() == IExpressionValue::INT);
			result /= value->valueAsDouble();
		}

		return new ExpressionValue(result);
	}

	IExpressionValue* mod(std::vector<IExpression*>* args) {
		assert(args != NULL);
		assert(args->size() == 2);

		return new ExpressionValue(fmod(args->at(0)->evaluate()->valueAsDouble(), args->at(1)->evaluate()->valueAsDouble()));
	}
};

#endif // _FUNCS_H_