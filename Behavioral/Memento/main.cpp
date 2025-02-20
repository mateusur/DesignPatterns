#include <iostream>
#include <vector>
#include <memory>
#include <ostream>

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

class BankAccount {
    struct Memento
    {
        Memento() = delete;
        explicit Memento(int32_t p_balance) : m_balance(p_balance) {}
        int32_t m_balance;
    };
    int balance_;
    int current_;
    std::vector<std::shared_ptr<const Memento> > history_;

public:
    BankAccount(int balance) : balance_(balance), current_(0) {
        history_.emplace_back(make_shared<const Memento>(balance));
    }

    const shared_ptr<const Memento> deposit(int amount){
        balance_+=amount;
        history_.emplace_back(make_shared<const Memento>(balance_));
        return history_[current_++];
    }
    void restore(const std::shared_ptr<const Memento>& memento){
        if(memento){
            balance_ = memento->m_balance;
            history_.push_back(memento);
            current_ = history_.size()-1;
        }
    }
    const shared_ptr<const Memento> undo(){
        if(current_>0){
            balance_ = history_[--current_]->m_balance;
            return history_[current_];
        }
        return nullptr;
    }
    const shared_ptr<const Memento> redo(){
        if((current_+1 ) < history_.size()){
            balance_ = history_[++current_]->m_balance;
            return history_[current_];
        }
        return nullptr;
    }
    friend std::ostream& operator<<(std::ostream& os,const BankAccount& account){
        return os << "Balance: " << account.balance_;
    }
};

int main() {
    BankAccount account(1000);
    account.deposit(250);
    account.deposit(50);
    auto history_snap = account.deposit(1000);

    cout << account << endl;
    account.undo();
    cout <<"After 1 undo: " << account << endl;
    account.undo();
    cout <<"After 2 undo: " << account << endl;
    account.redo();
    cout <<"After 1 redo: " << account << endl;
    account.restore(history_snap);
    account.undo();
    cout <<"After 3 undo: " << account << endl;
    account.undo();
    cout <<"After 4 undo: " << account << endl;
    cout << "After restoring: " << account << endl;

  return 0;
}
