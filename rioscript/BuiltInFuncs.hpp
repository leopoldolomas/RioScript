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