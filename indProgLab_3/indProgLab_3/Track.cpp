#include "Transport.cpp"

class Track {
public:
    double cost;
    double time;
    int volume;
    
    Track() : cost(0), time(0), volume(0) {}
    
    Track(Transport _transport, int _volume) {
        this->time = _transport.sumTime(_transport.distance);
        this->cost = _transport.sumCost(_volume, _transport.distance);
    }
    
    Track(Transport _transport1, Transport _transport2, Transport _transport3, int _volume) {
        this->cost = _transport1.sumCost(_volume, _transport1.distance) + _transport2.sumCost(_volume, _transport2.distance);
        this->time = _transport1.sumTime(_transport1.distance) + _transport2.sumTime(_transport2.distance);
        this->cost += _transport3.sumCost(_volume, _transport3.distance);
        this->time += _transport3.sumTime(_transport3.distance);
    }
    
    Track(Transport _transport1, Transport _transport2, Transport _transport3, Transport _transport4,
          Transport _transport5, int _volume) {
        this->cost = _transport1.sumCost(_volume, _transport1.distance) + _transport2.sumCost(_volume, _transport2.distance) + _transport3.sumCost(_volume, _transport3.distance);
        this->time = _transport1.sumTime(_transport1.distance) + _transport2.sumTime(_transport2.distance) + _transport3.sumTime(_transport3.distance);
        this->cost += _transport4.sumCost(_volume, _transport4.distance);
        this->time += _transport4.sumTime(_transport4.distance);
        this->cost += _transport5.sumCost(_volume, _transport5.distance);
        this->time += _transport5.sumTime(_transport5.distance);
    }
    
    Track(Transport _transport1, Transport _transport2, Transport _transport3, Transport _transport4,
          Transport _transport5, Transport _transport6, Transport _transport7, int _volume) {
        this->cost = _transport1.sumCost(_volume, _transport1.distance) + _transport2.sumCost(_volume, _transport2.distance) + _transport3.sumCost(_volume, _transport3.distance) + _transport4.sumCost(_volume, _transport4.distance);
        this->time = _transport1.sumTime(_transport1.distance) + _transport2.sumTime(_transport2.distance) + _transport3.sumTime(_transport3.distance) + _transport4.sumTime(_transport4.distance);
        this->cost += _transport5.sumCost(_volume, _transport5.distance) + _transport6.sumCost(_volume, _transport6.distance);
        this->time += _transport5.sumTime(_transport5.distance) + _transport6.sumTime(_transport6.distance);
        this->cost += _transport7.sumCost(_volume, _transport7.distance);
        this->time += _transport7.sumTime(_transport7.distance);
    }
};
