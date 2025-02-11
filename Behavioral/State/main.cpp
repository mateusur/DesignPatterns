#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
class Context;

class State {
protected:
    Context* context;
public:
    State(){
        cout << "State ctor" << endl;
    }
    void set_context(Context* context) { this->context = context; } 
    virtual void handle_simple_request() = 0;
    virtual void handle_complex_request() = 0;
    virtual ~State() {
        cout << "State dtor" << endl;
    }
};

class Context{
    unique_ptr<State> current_state;
public:
    Context(unique_ptr<State> initial_state) : current_state (std::move(initial_state)) {
        cout << "Context ctor" << endl;
        current_state->set_context(this);
    }
    void transition_to(unique_ptr<State> new_state){
            current_state = std::move(new_state);
            current_state->set_context(this);
    
    }
    void simple_request(){
        current_state->handle_simple_request();
    }
    void complex_request(){
        current_state->handle_complex_request();
    }
    ~Context() {
        cout << "Context dtor" << endl;
    }
};

class StateA : public State{
public:
    StateA(){
        cout << "StateA ctor" << endl;
    }
    void handle_simple_request() override {
        cout << "State A handling simple request" << endl;
    };
    void handle_complex_request() override;
    ~StateA() {
        cout << "StateA dtor" << endl;
    }
};

class StateB : public State{
public:
    StateB(){
        cout << "StateB ctor" << endl;
    }
    void handle_simple_request() override {
        cout << "State B handling simple request" << endl;
    };
    void handle_complex_request() override {
        cout << "State B handling Complex request" << endl;
        context->transition_to(std::make_unique<StateA>());
    };
    ~StateB() {
        cout << "StateB dtor" << endl;
    }
};

void StateA::handle_complex_request() {
        cout << "State A handling Complex request" << endl;
        context->transition_to(std::make_unique<StateB>());
};

void execute(){
  Context* context = new Context(std::make_unique<StateA>());
  context->simple_request();
  context->complex_request();
  context->simple_request();

  delete context;
}
int main() {
execute();
    return 0;
}
