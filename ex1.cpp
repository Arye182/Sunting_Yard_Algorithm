#include <iostream>
#include <utility>
#include"Expression.h"
#include "ex1.h"
using namespace std;

// implementations of constructors:
Value::Value(double v) {
  this->value = v;
}
Variable::Variable(string s, double v) {
  this->value = v;
  this->name = move(s);
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
  delete(this->left);
  delete(this->right);
}
UnaryOperator::~UnaryOperator() {
  delete(this->exp);
}

// getters & setters
void Variable::setValue(double val) {
  this->value = val;
}

// implementations of methods:
Variable& Variable::operator++() {
  this->value += 1;
  return *this;
}
Variable& Variable::operator++(int) {
  this->value += 1;
  return *this;
}
Variable& Variable::operator--() {
  this->value -= 1;
  return *this;
}
Variable& Variable::operator--(int) {
  this->value -= 1;
  return *this;
}
Variable& Variable::operator+=(double num) {
  this->value += num;
  return *this;
}
Variable& Variable::operator-=(double num) {
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
  return (this->left->calculate() / this->right->calculate());
}
double UPlus::calculate() {
  return this->exp->calculate();
}
double UMinus::calculate() {
  return -(this->exp->calculate());
}




