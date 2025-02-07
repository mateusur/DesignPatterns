#include <iostream>
#include <vector>
#include <typeinfo>

using std::cout;
using std::endl;

enum class Vehicles {
    Bike,
    Truck,
    Plane
};

class Handler {
    Handler* next_;
public:
    explicit Handler(Handler* next) : next_(next) {}
    explicit Handler() : Handler(nullptr) {};
    virtual void addHandler(Handler* h){
        if(next_){
            next_->addHandler(h);
        } else {
            next_ = h;
        }
    }
    virtual void handleRequest(const Vehicles& vehicle){
        if(next_){
            next_->handleRequest(vehicle);
        }
    }
    virtual ~Handler() = default;
};

class BikeHandler : public Handler{
    bool canHandleMyslef(const Vehicles& vehicle){
        return vehicle == Vehicles::Bike;
    }
public:
    void handleRequest(const Vehicles& vehicle) override {
        if(canHandleMyslef(vehicle)){
            cout << "Handled in: "<< typeid(*this).name() << endl;
        }{
            Handler::handleRequest(vehicle);
        }   
    }
};

class TruckHandler : public Handler{
    bool canHandleMyslef(const Vehicles& vehicle){
        return vehicle == Vehicles::Truck;
    }
public:
    void handleRequest(const Vehicles& vehicle) override {
        if(canHandleMyslef(vehicle)){
            cout << "Handled in: "<< typeid(*this).name() << endl;
        }{
            Handler::handleRequest(vehicle);
        }   
    }
};

class PlaneHandler : public Handler{
    bool canHandleMyslef(const Vehicles& vehicle){
        return vehicle == Vehicles::Plane;
    }
public:
    void handleRequest(const Vehicles& vehicle) override {
        if(canHandleMyslef(vehicle)){
            cout << "Handled in: "<< typeid(*this).name() << endl;
        }{
            Handler::handleRequest(vehicle);
        }   
    }
};

int main() {
    
    BikeHandler bikeHandler;
    TruckHandler truckHandler;
    PlaneHandler planeHandler;
    Handler handlers(&planeHandler);
    handlers.addHandler(&truckHandler);
    handlers.addHandler(&bikeHandler);
    
    std::vector<Vehicles> vehicles{Vehicles::Plane,Vehicles::Plane,Vehicles::Bike};
    for(auto v : vehicles){
        handlers.handleRequest(v);
    }
    
    return 0;
}
