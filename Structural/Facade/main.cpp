#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

enum class Medium {USB,BLE};

class Usb {
    public:
        bool isAvailable() {
            return true;
        }
        void connect() {
            cout << "Connecting via USB" << endl;
        }

        void send(const string& file) {
            cout << file << " sent." << endl;
        }
};

class Bluetooth {
    public:
        bool isAvailable() {
            return true;
        }
        void connect() {
            cout << "Connecting via BT" << endl;
        }
        void authenticate() {
            cout << "Authenticating BT" << endl;
        }
        void send(const string& file){
            cout << file << " sent." << endl;
        }   
};

// Facade - simple interface for client. 
// e.g. secretary can point to where you need to go -
//  accounting, boss, HR
class FileTransfer{
public:
    void transfer(const string& filename, Medium medium){
        switch (medium)
        {
        case Medium::USB:
            Usb usb;
            if(usb.isAvailable()){
                usb.connect();
                usb.send(filename);
            }
            break;
        case Medium::BLE:
            Bluetooth ble;
            if(ble.isAvailable()){
                ble.authenticate();
                ble.connect();
                ble.send(filename);
            }
            break;
        default:
            break;
        }
        
    }
};


int main(){
    FileTransfer facade;
    facade.transfer("Ebook.pdf",Medium::USB);
}