#include <iostream>
#include <vector>

using std::cout;
using std::endl;

template <typename T, typename U>
class Iterator {
    typedef typename std::vector<T>::iterator iter_type;
    U* ptr_data_;
    iter_type it_;
public:
    Iterator(U* data_ptr, bool reverse = false) : ptr_data_(data_ptr) {
        it_ = ptr_data_->data_.begin();
    }
    void first(){
        it_ = ptr_data_->data_.begin();
    }
    void next() {
        it_++;
    }
    bool done(){
        return (it_ == ptr_data_->data_.end());
    }
    iter_type current(){
        return it_;
    }

};

template<typename T>
class Container {
    friend class Iterator<T,Container>;
    std::vector<T> data_;
public:
    void add(T a){
        data_.push_back(a);
    }

    Iterator<T,Container>* createIterator() {
        return new Iterator<T,Container>(this);
    }
};

class Data {
    int data_;
public:
    Data(int data = 0) : data_(data) {}

    void set_data(int data){
        data_ = data;
    }
    
    int data(){
        return data_;
    }
};

int main() {
    Container<int> container;
    for(int i = 0 ; i < 12; ++i){
        container.add(i);
    }

    Iterator<int, Container<int>>* it = container.createIterator();
    for(it->first(); !it->done() ; it->next()){
        cout << *it->current() << endl;
    }
    cout << "*****"<< endl;
    Container<Data> container2;
    for(int i = 100; i < 1'000; i+=123){
        container2.add(Data(i));
    }
    auto iter2 = container2.createIterator();

    for(iter2->first(); !iter2->done() ; iter2->next()){
        cout << iter2->current()->data() << endl;
    }

    delete it;
    delete iter2;
  return 0;
}
