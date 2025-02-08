#include <array>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class ComponentA;
class ComponentB;
class ComponentC;

class Visitor {
 public:
  virtual void visitComponentA(const ComponentA* comp) const = 0;
  virtual void visitComponentB(const ComponentB* comp) const = 0;
  virtual void visitComponentC(const ComponentC* comp) const = 0;
  virtual ~Visitor() = default;
};

class Component {
 public:
  virtual void accept(Visitor* visitor) const = 0;
  virtual ~Component() = default;
};

class ComponentA : public Component {
 public:
  void accept(Visitor* visitor) const override {
    visitor->visitComponentA(this);
  }
  std::string getName() const { return "ComponentA"; }
  int getInt() const { return 99; }
};

class ComponentB : public Component {
 public:
  void accept(Visitor* visitor) const override {
    visitor->visitComponentB(this);
  }
  std::string getNumbers() const { return "12345"; }
  float getFloat() const { return 9.9f; }
};

class ComponentC : public Component {
 public:
  void accept(Visitor* visitor) const override {
    visitor->visitComponentC(this);
  }
  std::string getCode() const { return "987*123&654$"; }
  double getDouble() const { return 20.9f; }
};

class Visitor1 : public Visitor {
  void visitComponentA(const ComponentA* comp) const override {
    cout << comp->getName() << endl;
  };
  void visitComponentB(const ComponentB* comp) const override {
    cout << comp->getNumbers() << endl;
  };
  void visitComponentC(const ComponentC* comp) const override {
    cout << comp->getCode() << endl;
  };
};

class Visitor2 : public Visitor {
  void visitComponentA(const ComponentA* comp) const override {
    cout << comp->getInt() << endl;
  };
  void visitComponentB(const ComponentB* comp) const override {
    cout << comp->getFloat() << endl;
  };
  void visitComponentC(const ComponentC* comp) const override {
    cout << comp->getDouble() << endl;
  };
};

int main() {
  std::vector<Component*> components{new ComponentA, new ComponentB,
                                     new ComponentC};
  Visitor1* visitor1 = new Visitor1;
  Visitor2* visitor2 = new Visitor2;

  cout << "Visitor1:" << endl;
  for (auto comp : components) {
    comp->accept(visitor1);
  }

  cout << "Visitor2:" << endl;
  for (auto comp : components) {
    comp->accept(visitor2);
  }
  for (auto comp : components) {
    delete comp;
  }
  delete visitor1;
  delete visitor2;
  return 0;
}
