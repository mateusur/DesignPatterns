#include <iostream>

template <typename T>
struct Property {
  T value;
  Property(T value) { this->value = value; }
  T operator()() { return value; }
  T operator=(T new_value) { return value = new_value; }
};

struct Monster {
  int strength{25};
  int size{15};
  void setStrength(int new_strength) { strength = new_strength; }
  int getStrength() { return strength; }
};

struct PMonster {
  Property<int> strength{20};
  Property<int> size{20};
  friend Property<int>;
};

int main() {
  Monster monster;
  monster.setStrength(30);
  std::cout << "Strength: " << monster.getStrength() << std::endl;

  PMonster pmonster;
  pmonster.size = 20;
  std::cout << "Strength: " << pmonster.size() << std::endl;
  return 0;
}
