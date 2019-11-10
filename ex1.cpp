#include <iostream>
#include <stdexcept>
#include <utility>
#include"Expression.h"
#include "ex1.h"
using namespace std;

// part 1 of the EX 1:
// implementations of constructors:
Value::Value(double v) {
  this->value = v;
}
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
}
Interpreter::~Interpreter() {
  delete (this->tokenList);
  delete (this->outputQueue);
  delete (this->operatorsStack);
}
bool Interpreter::isDigit(char token) {
  return (token <= 57 && token >= 48);
}
bool Interpreter::isOperator(string token) {
  return (token == "/" || token == "*"
      || token == "+" || token == "-");
}
void Interpreter::setVariables(string vars) {

}
void Interpreter::fromStringToList(string expression) {
  for (int i = 0, j = 0; i < expression.size(); i++) {
    // token in string is not a number....
    if (!this->isDigit(expression[i])) {
      char token = expression[i];
      this->tokenList->push_front(&token);
      j++;
      continue;
    }
    // token is a number
    while (j < expression.size() && ((this->isDigit(expression[j + 1])
        || expression[j + 1] == 46))) {
      j++;
    }
    // preparing the more then 1 digit number to insert to the list
    int tokenLen = j - i + 1;
    string token;
    for (int k = 0; k < tokenLen; k++, i++) {
      token += expression[i];
    }
    this->tokenList->push_front(token);
    i = j;
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
void Interpreter::shuntingYard(list<string> *tokenList) {
  // the machine will have 2 states ExpectOperand and ExpectOperator.
  // ExpectOperand == 0 , ExpectOperator == 1;
  int machineState = 0;
  // we will use the list iterator :)
  for (list<string>::iterator it = tokenList->begin(); it != tokenList->end();
       ++it) {
    // If it's a number
    if (this->isDigit((*it)[0])) {
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


    //     If token is a unary operator.
    //        Error if the state is not ExpectOperand.
    //        Push the token to the operator stack.
    //        Set the state to ExpectOperand.



    //  If it's a binary operator
    if (this->isOperator(*it)) {
      if (machineState == 0) {
        __throw_invalid_argument("bad input");
      }
      // While there's an operator on the top of the stack with greater
      // precedence:
      while (operatorsStack->top() == "*") {
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



    // If it's a right bracket
    if (this->tokenList->front() == ")") {
      // While there's not a left bracket at the top of the stack:
      while (!(this->operatorsStack->top() == "(")) {
        // Pop operators from the stack onto the output queue.


      }
      // Pop the left bracket from the stack and discard it

    }

  }
  //  While there are operators on the stack, pop them to the queue

  //__throw_invalid_argument("bad input");

  // end of shunting yard
}
Expression *Interpreter::fromPolishToTree(queue<string> *yardOutput) {
  return nullptr;
}
Expression *Interpreter::interpret(string expression) {
  // first stage of the interpreter
  fromStringToList(expression);
  // programmer test before s.y
  while (!tokenList->empty()) {
    cout << tokenList->front() << endl;
    tokenList->pop_front();
  }
  // second stage of interpreter - shunting yard
  shuntingYard(this->tokenList);
  // third stage - creating the expression tree
  Expression *after = fromPolishToTree(this->outputQueue);
  return after;
}
