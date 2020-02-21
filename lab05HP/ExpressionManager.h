#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H
#include <stack>
#include <vector>
#include "ExpressionManagerInterface.h"
using std::string;
using std::ostream;


/* Expression Manager */
class ExpressionManager : public ExpressionManagerInterface
{
private:
	string expression_;
	std::vector<string> inFix_;
	std::vector<string> postFix_;
	std::vector<string> preFix_;
	const string operators = "([{ -+  */% ";

public:
	ExpressionManager() { }
	ExpressionManager(string exp) :
		expression_(exp), inFix_(NULL), postFix_(NULL), preFix_(NULL) { }
	~ExpressionManager() { }

	virtual int value(void); /** Return the integer value of the infix expression */

	virtual string infix(void); /** Return the infix expression / rejects invalid */

	virtual string postfix(void); /** Return a postfix representation */

	virtual string prefix(void); /** (BONUS) Return a prefix representation */

	virtual string toString() const; /** Return the infix vector'd expression items */


	std::vector<string> tokenize(string sValue);

	void initialize(string expression);	// Initializing the expression



};
#endif // EXPRESSION_MANAGER_H