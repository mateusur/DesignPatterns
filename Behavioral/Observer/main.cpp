#include <iostream>
#include <vector>
#include <array>

class AlarmListener{ // Observer
public:
    virtual void notify() = 0;
};

class SensorSystem{ // Subject
    std::vector<AlarmListener*> listeners;
    public:
    void addListener(AlarmListener* listener){
        listeners.push_back(listener);
    }
    void notifyListeners() const {
        for(auto listener : listeners){
            listener->notify();
        }
    }
};

class Firefighers : public AlarmListener {
    public:
    void notify() override {
        std::cout << "Dispatching a firefighter unit to fire" << std::endl;
    }
    
};

class Police : public AlarmListener {
    public:
    void notify() override {
        std::cout << "Dispatching a police unit to crime" << std::endl;
    }
    
};

int main() {
    SensorSystem fire_sensor;
    SensorSystem crime_sensor;
    
    Firefighers funit1;
    Firefighers funit2;

    Police punit1;
    Police punit2;
    Police punit3;

    fire_sensor.addListener(&funit1);
    fire_sensor.addListener(&funit2);

    crime_sensor.addListener(&punit1);
    crime_sensor.addListener(&punit2);
    crime_sensor.addListener(&punit3);

    fire_sensor.notifyListeners();
    crime_sensor.notifyListeners();
    return 0;
}
