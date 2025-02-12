#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Strategy{
public:
    Strategy(){
        cout << "Strategy ctor" << endl;
    }
    virtual void executeAlgorithm() = 0;
    virtual ~Strategy() {
        cout << "Strategy dtor" << endl;
    }
};

class QuickSort : public Strategy{
public:
    QuickSort(){
        cout << "QuickSort ctor" << endl;
    }
    void executeAlgorithm() override {
        cout << "Performing quick sort" << endl;
    }
    virtual ~QuickSort(){
        cout << "Quick Sort dtor" << endl;
    }
};

class MergeSort : public Strategy{
public:
    MergeSort(){
        cout << "MergeSort ctor" << endl;
    }
    void executeAlgorithm() override {
        cout << "Performing merge sort" << endl;
    }
    
    virtual ~MergeSort(){
        cout << "Merge Sort dtor" << endl;
    }
};

class BubleSort : public Strategy{
public:
    BubleSort(){
        cout << "BubleSort ctor" << endl;
    }
    void executeAlgorithm() override {
        cout << "Performing bubble sort" << endl;
    }
    virtual ~BubleSort(){
        cout << "Buble Sort dtor" << endl;
    }
};

class Context {
    unique_ptr<Strategy> strategy_;
public:
    Context(unique_ptr<Strategy>&& strategy) : strategy_(std::move(strategy)) {}
    
    void setStrategy(unique_ptr<Strategy>&& strategy){
        strategy_ = std::move(strategy);
    }
    
    void performAlgorithm(){
        if(strategy_){
            strategy_->executeAlgorithm();
        }
    }
};

int main() {

    unique_ptr<Context> context = std::make_unique<Context>(std::make_unique<BubleSort>());
    context->performAlgorithm();
    context->setStrategy(std::make_unique<MergeSort>());
    context->performAlgorithm();
    return 0;
}
