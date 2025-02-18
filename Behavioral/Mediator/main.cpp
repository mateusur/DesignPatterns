#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Mediator;

class Person {
 public:
  virtual void SetMediator(Mediator* mediator) = 0;
  virtual void SendMessage(string&& message) = 0;
  virtual void GetMessage(string& message) = 0;

 protected:
  Mediator* mediator;
};

class Mediator {
 public:
  virtual void Send(string& message, Person* person) = 0;
  virtual void SetRenter(Person* renter) = 0;
  virtual void SetLandlord(Person* landlord) = 0;
};

class Landlord : public Person {
 public:
  void SetMediator(Mediator* mediator) override {
    this->mediator = mediator;
    this->mediator->SetLandlord(this);
  }

  void SendMessage(string&& message) override {
    this->mediator->Send(message, this);
  }

  void GetMessage(string& message) override {
    std::cout << "Landlord gets the message from Renter: " << message << endl;
  }
};

class Renter : public Person {
 public:
  void SetMediator(Mediator* mediator) override {
    this->mediator = mediator;
    this->mediator->SetRenter(this);
  }

  void SendMessage(string&& message) override {
    this->mediator->Send(message, this);
  }

  void GetMessage(string& message) override {
    std::cout << "Renter gets the message from Landlord: " << message << endl;
  }
};

class HouseMediator : public Mediator {
  Person* renter_;
  Person* landlord_;

 public:
  HouseMediator(Person* renter = nullptr, Person* landlord = nullptr)
      : renter_(renter), landlord_(landlord) {}

  void Send(string& message, Person* person) override {
    if (person == renter_) {
      landlord_->GetMessage(message);
    } else if (person == landlord_) {
      renter_->GetMessage(message);
    }
  }
  void SetRenter(Person* renter) override { renter_ = renter; }
  void SetLandlord(Person* landlord) override { landlord_ = landlord; }
};

int main() {
  Mediator* mediator = new HouseMediator();
  Person* renter = new Renter();
  Person* landlord = new Landlord();

  renter->SetMediator(mediator);
  landlord->SetMediator(mediator);

  renter->SendMessage("I want to rent a house in ShenZhen.\n");
  landlord->SendMessage("I have a house in ShenZhen.\n");

  delete renter;
  delete landlord;
  delete mediator;
  return 0;
}
