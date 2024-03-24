#include <gtest.h>

#include "tpolynom.h"

/*
TEST(TPolynom, TEST_NAME) {

}
*/

// DefaultConstructorTest
TEST(TPolynom, DefaultConstructorTest) {
	EXPECT_NO_THROW(TPolynom p);
}

// ParameterizedConstructorTest
TEST(TPolynom, ParameterizedConstructorTest) {
	string name = "-y*z+x^1*y^1*z^1+2*x^2*y^2*z^2+3*x^3*y^3*z^3-x*z";
	EXPECT_NO_THROW(TPolynom p(name));
}

TEST(TPolynom, ParameterizedConstructorTest_StringPolynom) {
	string name = "-y*z+x^1*y^1*z^1+2*x^2*y^2*z^2+3*x^3*y^3*z^3-x*z";
	string exp_str = "-1.000000*y*z-1.000000*x*z-1.000000*x*y*z-2.000000*x^2*y^2*z^2-3.000000*x^3*y^3*z^3";
	TPolynom p(name);

	EXPECT_EQ(exp_str, p.get_string());
}

// AssignmentOperatorTest

// Addition

// Subtraction

// Multiplication

// CalculateValue

// DifferentiationXTest

// DifferentiationYTest

// DifferentiationZTest


// TODO:
// Constructors, op=, op+, op-, op*, op(), dif