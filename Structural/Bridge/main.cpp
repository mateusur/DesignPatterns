#include <iostream>

// Bridge pattern is about decoupling an abstraction from its
// implementation, so the two can evolve independently. This pattern is
// particularly useful when both the abstraction (the high-level logic) and the
// implementation (the low-level details) need to change, but you don’t want
// changes in one part to ripple through the other. The result is code that’s
// flexible, extendable, and easy to maintain.

class Implementor {                         
public:
    virtual void implementation() const = 0;

    virtual ~Implementor() = default;
};
 
class ImplementorA: public Implementor {
public:
    ImplementorA() = default;
 
    void implementation() const {
        std::cout << "ImplementatorA::implementation" << '\n';
    }
};
 
class ImplementorB: public Implementor {
public:
    ImplementorB() = default;

    void implementation() const {
        std::cout << "ImplementatorB::implementation" << '\n';
    }
};

class Abstraction {                                 
public:
    virtual void function() const = 0;
    virtual ~Abstraction() = default;
};

class RefinedAbstraction: public Abstraction {
public:
    RefinedAbstraction(Implementor& impl) : 
		implementor(impl) {
    }
 
    void function() const {
        std::cout << "RefinedAbstraction::function\n";
        implementor.implementation();
    }
private:
    Implementor& implementor;
};
 
int main() {

    std::cout << '\n';

    ImplementorA implementorA;
    ImplementorB implementorB;
 
    RefinedAbstraction refinedAbstraction1(implementorA);  
    RefinedAbstraction refinedAbstraction2(implementorB);  

    Abstraction *abstraction1 = &refinedAbstraction1;
    Abstraction *abstraction2 = &refinedAbstraction2;

    abstraction1->function();

    std::cout << '\n';

    abstraction2->function();

    std::cout << '\n';

}
