// rioscript.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <assert.h>
#include "stdafx.h"
#include "Parser.h"
#include "ExpressionValue.h"
#include "BuiltInFuncs.hpp"

#define PROJECT_DIR "C:\\rioscript\\rioscript\\"

void testNumeric(const char* script_name, double expected_value) {
	auto expressions = Parser().parseFile(script_name);
	assert(expressions.at(0)->evaluate()->valueAsDouble() == expected_value);
}

int _tmain(int argc, _TCHAR* argv[]) {
	REGISTER_FUNCTION("+", &BuiltInFuncs::sum);
	REGISTER_FUNCTION("-", &BuiltInFuncs::sub);
	REGISTER_FUNCTION("*", &BuiltInFuncs::mul);
	REGISTER_FUNCTION("/", &BuiltInFuncs::div);
	REGISTER_FUNCTION("%", &BuiltInFuncs::mod);

	std::string projectDir = std::string(PROJECT_DIR);

	testNumeric((projectDir + "tests\\1_sum_a.rioscript").c_str(), 6.0);
	testNumeric((projectDir + "tests\\2_sum_b.rioscript").c_str(), 10.0);
	testNumeric((projectDir + "tests\\3_sub_a.rioscript").c_str(), -2.0);
	testNumeric((projectDir + "tests\\4_sub_b.rioscript").c_str(), -1.0);
	testNumeric((projectDir + "tests\\5_sub_c.rioscript").c_str(), 73.0);
	testNumeric((projectDir + "tests\\6_sub_d.rioscript").c_str(), 73.0);
	testNumeric((projectDir + "tests\\7_mul_a.rioscript").c_str(), 1.0);
	testNumeric((projectDir + "tests\\8_mul_b.rioscript").c_str(), 2.0);
	testNumeric((projectDir + "tests\\9_mul_c.rioscript").c_str(), 120.0);
	testNumeric((projectDir + "tests\\10_div_a.rioscript").c_str(), 0.5);
	testNumeric((projectDir + "tests\\11_div_b.rioscript").c_str(), 2.0);
	testNumeric((projectDir + "tests\\12_div_c.rioscript").c_str(), 1.0);
	testNumeric((projectDir + "tests\\13_mod_a.rioscript").c_str(), 0.0);
	testNumeric((projectDir + "tests\\14_mod_b.rioscript").c_str(), 2.0);

	return 0;
}

