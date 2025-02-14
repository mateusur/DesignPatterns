#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;

class Widget {
public:
    virtual void draw() const = 0;
};

class TextField : public Widget {
    int width, height;
public:
    TextField(int width, int height) : width(width), height(height) {}
    void draw() const override {
        cout << "Text field: " << width << ", " << height << endl;
    }   
};

class Decorator : public Widget {
    unique_ptr<Widget> widget;
public:
    explicit Decorator(unique_ptr<Widget> widget) :  widget(std::move(widget)) {}
    
    void draw() const override {
        widget->draw();
    }    
};

class BorderDecorator final : public Decorator{
public:
    explicit BorderDecorator(unique_ptr<Widget> widget) : Decorator(std::move(widget)) {}

    void draw() const override {
        Decorator::draw();
        cout << "Doing extra stuff with border" << endl;
    }
};

class ScrollDecorator final : public Decorator {
public:
    explicit ScrollDecorator(unique_ptr<Widget> Widget) : Decorator(std::move(Widget)) {}

    void draw() const override {
        Decorator::draw();
        cout << "Doing extra stuff with scroll" << endl;
    }
};

int main() {
    unique_ptr<Widget> wid = make_unique<BorderDecorator>(make_unique<TextField>(100,200));
    wid->draw();
}