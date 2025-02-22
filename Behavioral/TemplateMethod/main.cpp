#include <iostream>
#include <ostream>
#include <typeinfo>

using std::cout;
using std::endl;

class AbstractAlgorithm {
 protected:
  void CommonOperation1() { cout << "Common first step" << endl; }
  void CommonOperation2() { cout << "Common second step" << endl; }
  virtual void CustomOperation1() = 0;
  virtual void CustomOperation2() = 0;
  // We might override this if we need additional steps
  virtual void hook() {}

 public:
  void TemplateMethod() {
    CommonOperation1();
    CustomOperation1();
    hook();
    CommonOperation2();
    CustomOperation2();
  }
};

class Concrete1Algorithm : public AbstractAlgorithm {
 protected:
  void CustomOperation1() override {
    cout << "First custom operation in: " << typeid(*this).name() << endl;
  }
  void CustomOperation2() override {
    cout << "Second custom operation in: " << typeid(*this).name() << endl;
  }
};

class Concrete2Algorithm : public AbstractAlgorithm {
 protected:
  void CustomOperation1() override {
    cout << "First custom operation in: " << typeid(*this).name() << endl;
  }
  void CustomOperation2() override {
    cout << "Second custom operation in: " << typeid(*this).name() << endl;
  }
  void hook() override { cout << "Print everything in the middle" << endl; }
};

void ClientCode(AbstractAlgorithm* algo) { algo->TemplateMethod(); }

int main() {
  Concrete1Algorithm* algo1 = new Concrete1Algorithm;
  ClientCode(algo1);
  cout << endl;
  Concrete2Algorithm algo2;
  ClientCode(&algo2);
  delete algo1;
  return 0;
}
