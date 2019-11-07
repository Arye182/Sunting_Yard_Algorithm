//
// Created by arye on 04/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H
#include"Expression.h"
using namespace std;

// classes that inherit from Expression class
class BinaryOperator : public Expression{
 protected:
  Expression *left;
  Expression *right;
 public:
  BinaryOperator(Expression *left, Expression *right);
  virtual ~BinaryOperator() override ;
};
class UnaryOperator : public Expression {
 protected:
  Expression *exp;
 public:
  explicit UnaryOperator(Expression *exp);
  virtual ~UnaryOperator() override ;
};
class Value : public Expression{
 private:
  double value;
 public:
  explicit Value(double v);
  virtual ~Value() override = default;
  double calculate() override;
};
class Variable : public Expression{
 private:
  double value;
  string name;
 public:
  Variable(string s, double v);
  virtual ~Variable() override = default;
  double calculate() override;
  Variable& operator++();
  Variable& operator++(int);
  Variable& operator--();
  Variable& operator--(int);
  Variable& operator +=(double num);
  Variable& operator -=(double num);
  void setValue(double val);
};

// classes that inherit from BinaryOperator
class Plus : public BinaryOperator{
 public:
  double calculate() override;
  Plus(Expression *left, Expression *right) : BinaryOperator(left, right){}
  virtual ~Plus() override = default;;
};
class Minus : public BinaryOperator{
 public:
  double calculate() override;
  Minus(Expression *left, Expression *right) : BinaryOperator(left, right){}
  virtual ~Minus() override = default;;
};
class Mul : public BinaryOperator{
 public:
  double calculate() override;
  Mul(Expression *left, Expression *right) : BinaryOperator(left, right){}
  virtual ~Mul() override = default;
};
class Div : public BinaryOperator{
 public:
  double calculate() override;
  Div(Expression *left, Expression *right) : BinaryOperator(left, right){}
  virtual ~Div() override = default;
};

// classes that inherit from UnaryOperator
class UPlus : public UnaryOperator{
 public:
  double calculate() override;
  explicit UPlus(Expression *exp) : UnaryOperator(exp){}
  virtual ~UPlus() override = default;
};
class UMinus : public UnaryOperator{
 public:
  double calculate() override;
  explicit UMinus(Expression *exp) : UnaryOperator(exp){}
  virtual ~UMinus() override = default;
};

#endif //EX1_EX1_H
