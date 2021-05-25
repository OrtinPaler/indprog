#include "Singleton.cpp"

// abstract class
class Transport {
public:
    int speed;
    int volume;
    double price;
    int distance;
    
    Transport() {}
    
    Transport(tuple<int, int, double> _tuple, int _distance) {
        this->speed = get<0>(_tuple);
        this->volume = get<1>(_tuple);
        this->price = get<2>(_tuple);
        this->distance = _distance;
    }
    
    double sumTime(int _distance) {
        return _distance / speed;
    }
    
    double sumCost(int _mass, int _distance) {
        return (_mass / volume) * sumTime(_distance) * price;
    }
};

class Car : public Transport {
public:
    Car() : Transport() {
        this->speed = 60;
        this->volume = 50;
        this->price = 100;
        this->distance = 0;
    }
    
    Car(tuple<int, int, double>, int);
};

class Plane : public Transport {
public:
    Plane() : Transport() {
        this->speed = 300;
        this->volume = 100;
        this->price = 500;
        this->distance = 0;
    }
    
    Plane(tuple<int, int, double> _tuple, int _distance) : Transport(_tuple, _distance) {}
};

class Train : public Transport {
public:
    Train() : Transport() {
        this->speed = 100;
        this->volume = 500;
        this->price = 200;
        this->distance = 0;
    }
    
    Train(tuple<int, int, double> _tuple, int _distance) : Transport(_tuple, _distance) {}
};
