#include <iostream>
#include <memory>

class GasolineSource {
 public:
  virtual void FuelUp() const = 0;
  virtual ~GasolineSource() = default;
};

class GasStation final : public GasolineSource {
 public:
  void FuelUp() const override {
    std::cout << "Pumping gas at gas station" << std::endl;
  }
};

class FuelCan final : public GasolineSource {
 public:
  void FuelUp() const override {
    std::cout << "Pumping gas from fuel can" << std::endl;
  }
};

class Car final {
  std::shared_ptr<GasolineSource> gasolineSource;

 public:
  explicit Car(std::shared_ptr<GasolineSource> service)
      : gasolineSource(service) {
    if (!gasolineSource) {
      throw std::invalid_argument("Service must not be null!");
    }
  }

  void GetGasoline() const { gasolineSource->FuelUp(); }
};

int main() {
  std::shared_ptr<GasolineSource> station = std::make_shared<GasStation>();
  Car racecar(station);
  racecar.GetGasoline();

  std::shared_ptr<GasolineSource> can = std::make_shared<FuelCan>();
  Car duneBuggy(can);
  duneBuggy.GetGasoline();

  return 0;
}
