#include <any>
#include <iostream>
#include <memory>
#include <mutex>
#include <typeindex>
#include <unordered_map>

class Light {
  int unique_id{};

 public:
  Light(int id = 0) : unique_id(id) {}
  void print() const { std::cout << unique_id << std::endl; }
};
class Server {
  std::string message;
  bool printable;

 public:
  Server(std::string msg, bool print = true) : message(msg), printable(print) {}
  void print() const {
    if (printable) {
      std::cout << message << std::endl;
    }
  }
};
class SimManager {
  unsigned long number;

 public:
  SimManager(unsigned long number) : number(number) {}
  void print() const { std::cout << number << std::endl; }
};

class GlobalParameters final {
  static std::unordered_map<std::type_index, std::any> objects;
  static std::mutex mtx;
  GlobalParameters() = delete;
  GlobalParameters(const GlobalParameters& other) = delete;
  GlobalParameters& operator=(const GlobalParameters& other) = delete;
  GlobalParameters(GlobalParameters&& other) = delete;
  GlobalParameters& operator=(GlobalParameters&& other) = delete;

 public:
  template <typename T, typename... Args>
  static std::shared_ptr<T> GetOrCreate(Args&&... args) {
    std::type_index typeId(typeid(T));
    std::lock_guard<std::mutex> lock(mtx);
    auto it = objects.find(typeId);
    if (it != objects.end()) {
      return std::any_cast<std::shared_ptr<T>>(it->second);
    }
    auto obj = std::make_shared<T>(std::forward<Args>(args)...);
    objects[typeId] = obj;
    return obj;
  }
};

std::unordered_map<std::type_index, std::any> GlobalParameters::objects;
std::mutex GlobalParameters::mtx;

void PrintServer() {
  auto server = GlobalParameters::GetOrCreate<Server>("");
  server->print();
}

int main() {
  GlobalParameters::GetOrCreate<Light>(25);
  GlobalParameters::GetOrCreate<Server>("Hello World", true);

  PrintServer();
  auto light = GlobalParameters::GetOrCreate<Light>(0);
  light->print();
  return 0;
}
