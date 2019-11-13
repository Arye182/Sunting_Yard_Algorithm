#include <iostream>
#include <stdexcept>
#include <utility>
#include"Expression.h"
#include "ex1.h"
using namespace std;

// part 1 of the EX 1:
// implementations of constructors:
Value::Value(const double v) : value(v) {}
Variable::Variable(string s, double v) {
  this->value = v;
  this->name = s;
}
BinaryOperator::BinaryOperator(Expression *left, Expression *right) {
  this->left = left;
  this->right = right;
}
UnaryOperator::UnaryOperator(Expression *exp) {
  this->exp = exp;
}

// destructors:
BinaryOperator::~BinaryOperator() {
  delete (this->left);
  delete (this->right);
}
UnaryOperator::~UnaryOperator() {
  delete (this->exp);
}

// getters & setters
void Variable::setValue(double val) {
  this->value = val;
}

// implementations of methods:
Variable &Variable::operator++() {
  this->value += 1;
  return *this;
}
Variable &Variable::operator++(int) {
  this->value += 1;
  return *this;
}
Variable &Variable::operator--() {
  this->value -= 1;
  return *this;
}
Variable &Variable::operator--(int) {
  this->value -= 1;
  return *this;
}
Variable &Variable::operator+=(double num) {
  this->value += num;
  return *this;
}
Variable &Variable::operator-=(double num) {
  this->value -= num;
  return *this;
}

double Value::calculate() {
  return this->value;
}
double Variable::calculate() {
  return this->value;
}
double Plus::calculate() {
  return (this->left->calculate() + this->right->calculate());
}
double Minus::calculate() {
  return (this->left->calculate() - this->right->calculate());
}
double Mul::calculate() {
  return (this->left->calculate() * this->right->calculate());
}
double Div::calculate() {
  if ((this->right->calculate()) == 0) {
    throw invalid_argument("divided by zero");
  }
  return (this->left->calculate() / this->right->calculate());
}
double UPlus::calculate() {
  return this->exp->calculate();
}
double UMinus::calculate() {
  return -(this->exp->calculate());
}

// Part 2 of EX1:
// Interpreter Part using Shunting Yard Algorithm
Interpreter::Interpreter() {
  this->outputQueue = new queue<string>();
  this->operatorsStack = new stack<string>;
  this->tokenList = new list<string>();
  this->finalStack = new stack<string>();
}
Interpreter::~Interpreter() {
  delete (this->tokenList);
  delete (this->outputQueue);
  delete (this->operatorsStack);
  delete (this->finalStack);
}
bool Interpreter::isDigit(char token) {
  return (token <= 57 && token >= 48);
}
bool Interpreter::isBinaryOperator(string token) {
  return (token == "/" || token == "*"
      || token == "+" || token == "-");
}
bool Interpreter::isStackTopOperatorGreaterOrEqualIt(string iterator) {
  string top = this->operatorsStack->top();
  if (top == "$" || top == "#") {
    return true;
  }
  if (this->operatorsStack->empty()) {
    return false;
  };
  if ((top == "+" || top == "-") && (iterator == "*" || iterator == "/")) {
    return false;
  }
  if ((top == "*" || top == "/") && (iterator == "+" || iterator == "-")) {
    return true;
  }
  if ((top == "+" || top == "-") && (iterator == "+" || iterator == "-")) {
    return true;
  }
  return (top == "*" || top == "/") && (iterator == "*" || iterator == "/");
}
void Interpreter::setVariables(string vars) {

}
void Interpreter::fromStringToList(string expression) {
  // iterate all the chars in the string
  for (int i = 0, j = 0; i < expression.size(); i++, j++) {
    string token;
    bool isUMinus = false;
    bool isUPlus = false;
    char current = expression[i];
    // if we have number upcoming
    if (this->isDigit(current) || (current == '-' && this->isDigit
        (expression[j + 1]))) {
      while (this->isDigit(expression[j + 1]) || expression[j + 1] == 46) {
        j++;
      }
    }
    // if we have variable upcoming
    if (this->isChar(current)) {
      while (this->isDigit(expression[j + 1]) ||
          this->isChar(expression[j + 1]) || expression[j + 1] == 95) {
        j++;
      }
    }
    // if we have unary operator
    if (current == '-' && expression[j + 1] == '(') {
      isUMinus = true;
    }
    if (current == '+' && expression[j + 1] == '(') {
      isUPlus = true;
    }


    // preparing to insert to the list
    int tokenLen = j - i + 1;
    for (int k = 0, z = i; k < tokenLen; k++, z++) {
      if (isUMinus) {
        token = '$';
      } else if (isUPlus) {
        token = '#';
      } else {
        token += expression[z];
      }
    }
    this->tokenList->push_back(token);
    if (tokenLen > 1) {
      i = j;
    }
  }
}
/*
 * function : shunting yard:
 * i wrote this code base on shunting yard pseudo code from
 * https://brilliant.org/wiki/shunting-yard-algorithm/#
 * the validation of the correctness of the mathematical expression is used
 * with the help of this pseudo code:
 * https://stackoverflow.com/questions/16380234/
 * handling-extra-operators-in-shunting-yard
 *
 * this way we check the expression during the algorithm itself and by that
 * save run time complexity.
 *
 * */
void Interpreter::shuntingYard() {
  // the machine will have 2 states ExpectOperand and ExpectOperator.
  // ExpectOperand == 0 , ExpectOperator == 1;
  int machineState = 0;
  // we will use the list iterator :)
  for (list<string>::iterator it = tokenList->begin(); it != tokenList->end();
       ++it) {
    // If it's a number
    if (this->isDigit((*it)[0]) || ((*it)[0] == '-' && this->isDigit((*it)
                                                                     [1]))) {
      // if machine expect to get operator and we actually have an operand...
      if (machineState == 1) {
        __throw_invalid_argument("bad input");
      }
      // push it to queue
      this->outputQueue->push(*it);
      machineState = 1;
    }

    //    If token is a variable.
    //        Error if state is not ExpectOperand.
    //        Push token to output queue.
    //        Set state to ExpectOperator.

    // If token is a unary operator.
    if (*it == "#" || *it == "$") {
      // Error if the state is not ExpectOperator
      if (machineState == 0) {
        __throw_invalid_argument("bad input");
      }
      // Push the token to the operator stack.
      this->operatorsStack->push(*it);
      // Set the state to ExpectOperand.
      machineState = 0;
    }

    //  If it's a binary operator
    if (this->isBinaryOperator(*it)) {
      if (machineState == 0) {
        __throw_invalid_argument("bad input - expected operand but gave an "
                                 "operator");
      }
      // While there's an operator on the top of the stack with greater
      // precedence: -------------------------------------___
      // >>>>>>>>>>>>>>>>>>>>>IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      while (this->isStackTopOperatorGreaterOrEqualIt(*it)) {
        // Pop operators from the stack onto the output queue
        string tmp = operatorsStack->top();
        outputQueue->push(tmp);
        operatorsStack->pop();
      }
      // Push the current operator onto the stack
      this->operatorsStack->push(*it);
      machineState = 0;
    }

    // If it's a left bracket push it onto the stack
    if (*it == "(") {
      if (machineState == 1) {
        __throw_invalid_argument("bad input - expected operator, not "
                                 "parentheses");
      }
      this->operatorsStack->push(*it);
      machineState = 0;
    }

    // If it's a right bracket
    if (*it == ")") {
      if (machineState == 0) {
        __throw_invalid_argument("bad input");
      }
      // While there's not a left bracket at the top of the stack:
      while (!(this->operatorsStack->empty()) && !(this->operatorsStack->top()
          == "(")) {
        // Pop operators from the stack onto the output queue.
        string tmp = operatorsStack->top();
        outputQueue->push(tmp);
        operatorsStack->pop();
      }
      // check if there were too many parenthesis
      if (this->operatorsStack->empty()) {
        __throw_invalid_argument("bad input - too many parenthesis");
      } else {
        // Pop the left bracket from the stack and discard it
        operatorsStack->pop();
        machineState = 1;
      }
    }
  }
  //  While there are operators on the stack, pop them to the queue
  while (!(operatorsStack->empty())) {
    if (operatorsStack->top() == "(" || operatorsStack->top() == ")") {
      __throw_invalid_argument("bad input - mismatched parenthesis"); // mismatched parenthesis
    }
    string tmp = operatorsStack->top();
    outputQueue->push(tmp);
    operatorsStack->pop();
  }
  // end of shunting yard
}
Expression *Interpreter::fromPolishToTree() {
  if (isDigit(this->finalStack->top()[0]) || this->finalStack->top()[0] ==
      '-') {
    string::size_type st;
    double val = stod(this->finalStack->top(), &st);
    this->finalStack->pop();
    return new Value(val);
  }
  char operatorChar = this->finalStack->top()[0];
  switch (operatorChar) {
    case ('+'):this->finalStack->pop();
      return new Plus(this->fromPolishToTree(), this->fromPolishToTree());
    case ('-'):this->finalStack->pop();
      return new Minus(fromPolishToTree(), fromPolishToTree());
    case ('*'):this->finalStack->pop();
      return new Mul(fromPolishToTree(), fromPolishToTree());
    case ('/'):this->finalStack->pop();
      return new Div(fromPolishToTree(), fromPolishToTree());
    case ('$'):this->finalStack->pop();
      return new UMinus(fromPolishToTree());
    case ('#'):this->finalStack->pop();
      return new UPlus(fromPolishToTree());
  }
  return nullptr;
}
Expression *Interpreter::interpret(string expression) {
  // first stage of the interpreter
  fromStringToList(expression);
  // second stage of interpreter - shunting yard
  shuntingYard();
  // creating the final stack
  createFinalStack();
  // third stage - creating the expression tree
  return fromPolishToTree();
}
void Interpreter::createFinalStack() {
  while (!this->outputQueue->empty()) {
    string tmp = this->outputQueue->front();
    this->finalStack->push(tmp);
    this->outputQueue->pop();
  }
}
bool Interpreter::isChar(char token) {
  return (token <= 90 && token >= 65) || (token <= 122 && token >= 97);
}


