#include <iostream>
#include <vector>

using std::cout;
using std::endl;

class Command {
    public:
    virtual void execute() = 0;
};

class Device {
public: 
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void up() = 0;
    virtual void down() = 0;
};

class Light : public Device {
public:
    void on() override { cout << "Turn on Light" << endl;};
    void off() override {cout << "Turn off Light" << endl;};
    void up() override {cout << "Increase brightness" << endl;};
    void down() override {cout << "Decrease brightness" << endl;};
};

class Speaker : public Device {
public:
    void on() override {cout << "Turn on Speaker" << endl;};
    void off() override {cout << "Turn off Speaker" << endl;};
    void up() override {cout << "Increase volume" << endl;};
    void down() override {cout << "Decrease volume" << endl;};
};

class OnCommand : public Command{
    Device* device;
public:
    explicit OnCommand(Device* device) : device(device) {}
    void execute() override { device->on(); }
};
class OffCommand : public Command{
    Device* device;
public:
    explicit OffCommand(Device* device) : device(device) {}
    void execute() override { device->off(); }
};
class UpCommand : public Command{
    Device* device;
public:
    explicit UpCommand(Device* device) : device(device) {}
    void execute() override { device->up(); }
};
class DownCommand : public Command{
    Device* device;
public:
    explicit DownCommand(Device* device) : device(device) {}
    void execute() override { device->down(); }
};

class Invoker {
  Command* onCommand;
  Command* offCommand;
  Command* upCommand;
  Command* downCommand;

 public:
  Invoker(Command* onCommand, Command* offCommand, Command* upCommand,
          Command* downCommand)
      : onCommand(onCommand),
        offCommand(offCommand),
        upCommand(upCommand),
        downCommand(downCommand) {}

  void clickOn() { onCommand->execute(); }

  void clickOff() { offCommand->execute(); }

  void clickUp() { upCommand->execute(); }

  void clickDown() { downCommand->execute(); }
};

int main() {
  Light* light = new Light;

  Invoker* invoker = new Invoker(new OnCommand(light), new OffCommand(light),
                                 new UpCommand(light), new DownCommand(light));

  invoker->clickOn();
  invoker->clickOff();
  invoker->clickUp();
  invoker->clickDown();
  return 0;
}
