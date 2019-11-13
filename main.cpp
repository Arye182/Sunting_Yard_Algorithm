#include <iostream>

#include "ex1.h"
#include "Expression.h"



int main() {

    // 1
    Variable *x1 = new Variable("x1", 3);// x1=3
    Expression* e1 = new Mul( new UMinus(new Value(5.0) ) , new Plus( new Value(3.5) , &(++(*x1))) );// -5*(3.5+(++x1))
    cout << "1: " << e1->calculate() <<endl; //-37.5
    delete e1;

    // 2
    Variable *x2 = new Variable("x2", 5.0);// x2=5.0
    Variable *x3 = new Variable("x3", 10.0);// x3=10.0
    Expression* e2 = new Div(x2, new UMinus(new UPlus(new UMinus(x3))));// 5/-(+(-(10.0)))
    cout << "2: " << e2->calculate() << endl; //0.5
    delete e2;

    // 3
    Variable *x4 = new Variable("x4", 2.0);// x4=2.0
    Variable *x5 = new Variable("x5", -4.5);// x5=-4.5
    Expression* e3 = new Mul(&(++(*x4)), &((*x5)++));// (++x4)*(x5++)
    cout << "3: " << e3->calculate() << endl; //-10.5
    delete e3;

  // 4
  Interpreter *i1 = new Interpreter();
  Expression *e4 = i1->interpret("(3*5)");
  std::cout << "4: " << e4->calculate() << std::endl;//-14
  delete e4;
//
//    // 5
//    Interpreter* i2 = new Interpreter();
//    i2->setVariables("x=2;y=4");
//    i2->setVariables("x=3");
//    Expression* e5 = i2->interpret("2*(-x+y)");
//    std::cout << "5: " << e5->calculate() << std::endl;//2
//    delete e5;
//
//    // 6
//    Interpreter* i3 = new Interpreter();
//    i3->setVariables("x=1.5;y=8.5");
//    i2->setVariables("x=3");
//    Expression* e6 = i3->interpret("-(-(-((x+0.5)*(y+(-3.5)))))");
//    std::cout << "6: " << e6->calculate() << std::endl;//-17.5
//    delete e6;
//
//    Interpreter* i4 = new Interpreter();
//    Expression* e7 = nullptr;
//    try {
//        // 7
//        i4->setVariables("x2=@;y=8.5");//error
//        e7 = i4->interpret("-(-(-((x+0.5)*(y+(-3.5)))))");
//        std::cout << "7: " << e7->calculate() << std::endl;
//        delete e7;
//    } catch (const char* e) {
//        if (e7 != nullptr) {
//            delete e7;
//        }
//        std::cout << e << std::endl;
//    }

    return 0;
}