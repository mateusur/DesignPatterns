#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::string;

class SharedState {
 public:
  string brand;
  string model;
  string color;

  SharedState(const string& brand, const string& model, const string& color)
      : brand(brand), model(model), color(color) {}

  friend std::ostream& operator<<(std::ostream& os,
                                  const SharedState& sharedState) {
    return os << "[" << sharedState.brand << ", " << sharedState.model << ", "
              << sharedState.color << "]";
  }
};

class UniqueState {
  string owner;
  string plates;

 public:
  UniqueState(const string& owner, const string& plates)
      : owner(owner), plates(plates) {}

  friend std::ostream& operator<<(std::ostream& os,
                                  const UniqueState& uniqueState) {
    return os << "[" << uniqueState.owner << ", " << uniqueState.plates << "]";
  }
};

class Flyweight {
  shared_ptr<SharedState> sharedState_;

 public:
  Flyweight(shared_ptr<SharedState> sharedState)
      : sharedState_(std::move(sharedState)) {}

  shared_ptr<SharedState> shared_state() const { return sharedState_; }

  void operation(const UniqueState& unique_state) const {
    std::cout << "Flyweight: Displaying shared (" << *sharedState_
              << ") and unique (" << unique_state << ") state.\n";
  }
};

class FlyweightFactory {
  std::unordered_map<string, Flyweight> flyweights;

  string getKey(const SharedState& sharedState) const {
    return sharedState.brand + "_" + sharedState.model + "_" +
           sharedState.color;
  }

 public:
  FlyweightFactory(std::initializer_list<SharedState> sharedStates) {
    for (const SharedState& shared : sharedStates) {
      flyweights.emplace(getKey(shared),
                         Flyweight(make_shared<SharedState>(shared)));
    }
  }

  Flyweight getFlyweight(const SharedState& sharedState) {
    string key = getKey(sharedState);
    if (flyweights.find(key) == flyweights.end()) {
      cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
      flyweights.emplace(key, Flyweight(make_shared<SharedState>(sharedState)));
    } else {
      cout << "FlyweightFactory: Reusing existing flyweight.\n";
    }
    return flyweights.at(key);
  }

  void listFlyweights() const {
    for (const auto& obj : flyweights) {
      cout << obj.first << "\n";
    }
  }
};

int main() {
  FlyweightFactory* factory =
      new FlyweightFactory({{"Chevrolet", "Camaro2018", "pink"},
                            {"Mercedes Benz", "C300", "black"},
                            {"Mercedes Benz", "C500", "red"},
                            {"BMW", "M5", "red"},
                            {"BMW", "X6", "white"}});
  factory->listFlyweights();
  {
    cout << "\nClient: Adding a car to database.\n";
    const Flyweight& flyweight = factory->getFlyweight({"BMW", "M5", "red"});
    flyweight.operation({"James Doe", "CL234IR"});
  }
  {
    cout << "\nClient: Adding a car to database.\n";
    const Flyweight& flyweight = factory->getFlyweight({"BMW", "X1", "red"});
    flyweight.operation({"James Doe", "CL234IR"});
  }
  factory->listFlyweights();

  delete factory;
}