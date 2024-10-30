#include <iostream>
#include <string>

// Product class
class House {
private:
    int windows;
    int doors;
    std::string roofType;
    bool hasGarage;
    bool hasGarden;

public:
    // Setters for each component of the house
    void setWindows(int windows) { this->windows = windows; }
    void setDoors(int doors) { this->doors = doors; }
    void setRoofType(const std::string& roofType) { this->roofType = roofType; }
    void setGarage(bool hasGarage) { this->hasGarage = hasGarage; }
    void setGarden(bool hasGarden) { this->hasGarden = hasGarden; }

    // Display function to showcase the house's configuration
    void showHouse() const {
        std::cout << "House with " << windows << " windows, " 
                  << doors << " doors, " 
                  << "roof type: " << roofType << ", "
                  << (hasGarage ? "has a garage, " : "no garage, ")
                  << (hasGarden ? "has a garden." : "no garden.") << std::endl;
    }
};

// Builder Interface
class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    virtual void buildWindows() = 0;
    virtual void buildDoors() = 0;
    virtual void buildRoof() = 0;
    virtual void buildGarage() = 0;
    virtual void buildGarden() = 0;
    virtual House* getHouse() = 0;
};

// Concrete Builder
class ConcreteHouseBuilder : public HouseBuilder {
private:
    House* house;

public:
    ConcreteHouseBuilder() { reset(); }

    ~ConcreteHouseBuilder() { delete house; }

    void reset() {
        house = new House();
    }

    void buildWindows() override {
        house->setWindows(4);
    }

    void buildDoors() override {
        house->setDoors(2);
    }

    void buildRoof() override {
        house->setRoofType("Gabled Roof");
    }

    void buildGarage() override {
        house->setGarage(true);
    }

    void buildGarden() override {
        house->setGarden(true);
    }

    House* getHouse() override {
        House* builtHouse = house;
        reset();  // Prepare for the next house build
        return builtHouse;
    }
};

// Director class to manage the building steps
class Director {
private:
    HouseBuilder* builder;

public:
    void setBuilder(HouseBuilder* builder) {
        this->builder = builder;
    }

    void buildMinimalHouse() {
        builder->buildWindows();
        builder->buildDoors();
    }

    void buildLuxuryHouse() {
        builder->buildWindows();
        builder->buildDoors();
        builder->buildRoof();
        builder->buildGarage();
        builder->buildGarden();
    }
};

int main() {
    Director director;
    ConcreteHouseBuilder builder;

    director.setBuilder(&builder);

    // Build a minimal house
    director.buildMinimalHouse();
    House* minimalHouse = builder.getHouse();
    minimalHouse->showHouse();
    delete minimalHouse;

    // Build a luxury house
    director.buildLuxuryHouse();
    House* luxuryHouse = builder.getHouse();
    luxuryHouse->showHouse();
    delete luxuryHouse;

    return 0;
}
