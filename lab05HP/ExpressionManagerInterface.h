//**** YOU MAY NOT MODIFY THIS DOCUMENT ****/
#ifndef EXPRESSION_INTERFACE_H
#define EXPRESSION_INTERFACE_H
#include <string>

class ExpressionManagerInterface
{
public:
	ExpressionManagerInterface(void) {};
	virtual ~ExpressionManagerInterface(void) {};

	/** Return the integer value of the infix expression */
	virtual int value(void) = 0;

	/** Return the infix items from the expression
		Throw an error if the expression
		1) is not balanced.
		2) the number of operators IS NOT one less than the number of operands.
		3) there are adjacent operators. */
	virtual std::string infix(void) = 0;

	/** Return a postfix representation of the infix expression */
	virtual std::string postfix(void) = 0;

	/** (BONUS) Return a prefix representation of the infix expression */
	virtual std::string prefix(void)
	{
		return "NOT IMPLEMENTED";
	}

	/** Return the infix vector'd expression items */
	virtual std::string toString() const = 0;

};
#endif	// EXPRESSION_INTERFACE_H