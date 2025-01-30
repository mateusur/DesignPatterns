#include <iostream>
#include <vector>
#include <array>
class Car{
    public:
    virtual Car* clone() = 0;
    virtual std::string getColor() = 0;
    virtual ~Car() = default;
};

class Skoda : public Car {
    std::string color;
    int* id;
    public:
    Skoda(std::string color, int id) : color(color), id(new int(id)) {};
    Skoda(const Skoda& copy){
        color = copy.color;
        id = new int(*copy.id);
    }
    Car* clone() override {
        return new Skoda(*this);
    }
    std::string getColor() override {
        return color;
    }
    ~Skoda() override {
        delete id;
    }
};

class Opel : public Car {
    std::string color;
    int* id;
    bool custom;
    public:
    Opel(std::string color, int id, bool custom) : color(color), id(new int(id)), custom(custom) {};
    Opel(const Opel& copy){
        color = copy.color;
        id = new int(*copy.id);
        custom = copy.custom;
    }
    Car* clone() override {
        return new Opel(*this);
    }
    std::string getColor() override {
        return color;
    }
    ~Opel() override {
        delete id;
    }
};

class Factory {
    static std::array<Car*,2> prototypes;
    public:
    static void init();
    static Car* make_car(int choice);
};

std::array<Car*,2> Factory::prototypes{nullptr,nullptr};

void Factory::init(){
    prototypes[0] = new Skoda("Brown",987);
    prototypes[1] = new Opel("Blue", 312,true);
}
Car* Factory::make_car(int choice){
    if(choice == 0){
        return prototypes[0]->clone();
    } else if(choice == 1){
        return prototypes[1]->clone();
    } else {
        return nullptr;
    }
}
int main() {
    std::vector<Car*> cars;
    Factory::init();
    cars.push_back(Factory::make_car(0));
    cars.push_back(Factory::make_car(1));
    cars.push_back(Factory::make_car(1));
    cars.push_back(Factory::make_car(0));

    for(auto car : cars){
        std::cout << car->getColor() << std::endl;
    }

    for(auto car : cars){
        delete car;
    }
    return 0;
}
