#include "Track.cpp"

class AbstractFactory {
public:
    Transport createTransport();
    Transport createTransport(tuple<int, int, double>, int);
};

class CarFactory : public AbstractFactory {
public:
    Transport createTransport() {
        return Car();
    }
    
    Transport createTransport(tuple<int, int, double> _tuple, int _distance) {
        return Car(_tuple, _distance);
    }
};

class PlaneFactory : public AbstractFactory {
public:
    Transport createTransport() {
        return Plane();
    }
    
    Transport createTransport(tuple<int, int, double> _tuple, int _distance) {
        return Plane(_tuple, _distance);
    }
};

class TrainFactory : public AbstractFactory {
public:
    Transport createTransport() {
        return Train();
    }
    
    Transport createTransport(tuple<int, int, double> _tuple, int _distance) {
        return Train(_tuple, _distance);
    }
};
