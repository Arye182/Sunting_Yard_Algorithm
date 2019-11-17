//
// Created by arye on 04/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H
#include <stack>
#include <queue>
#include <list>
#include <map>
#include"Expression.h"
using namespace std;

// classes that inherit from Expression class
class BinaryOperator : public Expression {
 protected:
  Expression *left;
  Expression *right;
 public:
  BinaryOperator(Expression *leftE, Expression *rightE);
  virtual ~BinaryOperator() override;
};
class UnaryOperator : public Expression {
 protected:
  Expression *exp;
 public:
  explicit UnaryOperator(Expression *expression);
  virtual ~UnaryOperator() override;
};
class Value : public Expression {
 private:
  const double value;
 public:
  explicit Value(double v);
  virtual ~Value() override = default;
  double calculate() override;
};
class Variable : public Expression {
 private:
  double value;
  string name;
 public:
  Variable(string s, double v);
  virtual ~Variable() override = default;
  double calculate() override;
  Variable &operator++();
  Variable &operator++(int);
  Variable &operator--();
  Variable &operator--(int);
  Variable &operator+=(double num);
  Variable &operator-=(double num);
};

// classes that inherit from BinaryOperator
class Plus : public BinaryOperator {
 public:
  double calculate() override;
  Plus(Expression *leftE, Expression *rightE) : BinaryOperator(leftE, rightE) {}
  virtual ~Plus() override = default;
};
class Minus : public BinaryOperator {
 public:
  double calculate() override;
  Minus(Expression *leftE, Expression *rightE) : BinaryOperator(leftE,
                                                                rightE) {}
  virtual ~Minus() override = default;
};
class Mul : public BinaryOperator {
 public:
  double calculate() override;
  Mul(Expression *leftE, Expression *rightE) : BinaryOperator(leftE, rightE) {}
  virtual ~Mul() override = default;
};
class Div : public BinaryOperator {
 public:
  double calculate() override;
  Div(Expression *leftE, Expression *rightE) : BinaryOperator(leftE, rightE) {}
  virtual ~Div() override = default;
};

// classes that inherit from UnaryOperator
class UPlus : public UnaryOperator {
 public:
  double calculate() override;
  explicit UPlus(Expression *expression) : UnaryOperator(expression) {}
  virtual ~UPlus() override = default;
};
class UMinus : public UnaryOperator {
 public:
  double calculate() override;
  explicit UMinus(Expression *expression) : UnaryOperator(expression) {}
  virtual ~UMinus() override = default;
};

// iterator
class Interpreter {
 private:
  map<string, double> *varMap;
  queue<string> *outputQueue;
  stack<string> *operatorsStack;
  stack<string> *finalStack;
  list<string> *tokenList;
 public:
  Interpreter();
  ~Interpreter();
  bool isBinaryOperator(string token);
  bool isDigit(char token);
  bool isChar(char token);
  bool isValidNumber(string token);
  bool isStackTopOperatorGreaterOrEqualIt(string iterator);
  void setVariables(string vars);
  void setVariablesHelper(string var);
  void fromStringToList(string expression);
  void shuntingYard();
  void createFinalStack();
  Expression *fromPolishToTree();
  Expression *interpret(string expression);
};
#endif //EX1_EX1_H
