#include <iostream>
using namespace std;

class UofM {
public:
  UofM() {
    cout << "UofM ctor" << endl;
  }
  void print() const {
    cout << "I'm a Wolverine!" << endl;
  }
};

class EECS : public UofM {
public:
  EECS() {
    cout << "EECS ctor" << endl;
  }
  void print() const {
    cout << "I'm an EECS student!" << endl;
  }
  virtual void code() {
    cout << "I can code!" << endl;
  }
};

class EECS280 : public EECS {
public:
  EECS280() {
    cout << "EECS280 ctor" << endl;
  }
  void print() const {
    cout << "I'm an EECS280 student!" << endl;
  }
  void code() override {
    cout << "I like to code!" << endl;
  }
};


int main() {
    EECS280 foo;
    UofM bar;
  
    UofM *ptr = &foo;
    ptr->print();
  
    ptr = &bar;
    ptr->print();
  }
  
  
