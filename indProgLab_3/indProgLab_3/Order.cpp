#include "AbstractFactory.cpp"

enum Type { Turbo, Standart, Economy };

class Order {
public:
    double cost;
    int volume;
    string startPoint;
    string finishPoint;
    Type type;
    Track track;
    
    Singleton *var = Singleton::returnVar();
    AbstractFactory *carFactory = new CarFactory();
    AbstractFactory *planeFactory = new PlaneFactory();
    AbstractFactory *trainFactory = new TrainFactory();
    
    Order() : cost(0), volume(0), startPoint(""), finishPoint(""), type(Type::Economy), track(Track()) {}
    
    Order(Type _type, string _startPoint, string _finishPoint, int _volume) : volume(_volume), startPoint(_startPoint), finishPoint(_finishPoint), type(_type) {
        this->track = best(_startPoint, _finishPoint, _type, _volume);
        this->cost = track.cost;
    }
    
    int decr(string _string) {
        map<string, int> j = var->towns();
        for (auto i = j.begin(); i != j.end(); i++)
            if (_string == (*i).first)
                return (*i).second;
        return -1;
    }
    
    int **matrixUpd(Type _type) {
        int **matrix = new int *[SIZE];
        
        for (int i = 0; i < SIZE; i++) {
            matrix[i] = new int[SIZE];
            for (int j = 0; j < SIZE; j++)
                matrix[i][j] = var->matrixDist(i, j);
        }
        
        switch (_type) {
            case Economy: {
                for (int i = 0; i < SIZE; i++)
                    if (var->points(i).find("TS"))
                        for (int j = 0; j < SIZE; j++)
                            matrix[i][j] = 99999;
            }
                
            case Standart: {
                for (int i = 0; i < SIZE; i++)
                    if (var->points(i).find("AP"))
                        for (int j = 0; j < SIZE; j++)
                            matrix[i][j] = 99999;
            }
    
            case Turbo: {
                for (int i = 0; i < SIZE; i++)
                    for (int j = 0; j < SIZE; j++)
                        if (matrix[i][j] == 0)
                            matrix[i][j] = 99999;
            }
        }
        
        return matrix;
    }
    
    int *optim(int **array, int _startPoint, int _endPoint) {
        int *d = new int[SIZE];
        int *v = new int[SIZE];
        int temp, minindex, min;
        int begin_index = _startPoint;

        for (int i = 0; i < SIZE; i++) {
            d[i] = 99999;
            v[i] = 1;
        }
        
        d[begin_index] = 0;

        do {
            minindex = 99999;
            min = 99999;
            
            for (int i = 0; i < SIZE; i++)
                if ((v[i] == 1) && (d[i] < min)) {
                    min = d[i];
                    minindex = i;
                }

            if (minindex != 99999) {
                for (int i = 0; i < SIZE; i++)
                    if (array[minindex][i] > 0) {
                        temp = min + array[minindex][i];
                        if (temp < d[i])
                            d[i] = temp;
                    }
                
                v[minindex] = 0;
            }
        } while (minindex < 99999);

        int *ver = new int[SIZE];
        int end_index = _endPoint;
        ver[0] = end_index;
        int k = 1;
        int weight = d[end_index];

        while (end_index != begin_index)
            for (int i = 0; i < SIZE; i++)
                if (array[end_index][i] != 0)
                {
                    int temp = weight - array[end_index][i];
                    if (temp == d[i])
                    {
                        weight = temp;
                        end_index = i;
                        ver[k] = i + 1;
                        k++;
                    }
                }
        
        for (int i = 0; i < k / 2; i++)
            swap(ver[i], ver[k - 1 - i]);
        
        return ver;
    }
    
    Track best(string _startPoint, string _finishPoint, Type _type, int _volume) {
        int start = decr(_startPoint);
        int finish = decr(_finishPoint);
        
        int **mat = new int* [SIZE];
        for (int i = 0; i < SIZE; i++)
            mat[i] = new int[SIZE];
        mat = matrixUpd(_type);
        
        int *path = new int[SIZE];
        for (int i = 0; i < SIZE; i++)
            path[i] = -1;
        path = optim(mat, start, finish);
        
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            if (path[i] != -1)
                count++;
            else
                break;
        }
        
        Track track;
        switch (count) {
            case 1: {
                Transport car = carFactory->createTransport();
                map<string, int> table = var->table();
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[0])))
                        car = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[0], path[1]));
                
                track = Track(car, _volume);
                return track;
            }
            
            case 3: {
                Transport car1 = carFactory->createTransport();
                Transport car2 = carFactory->createTransport();
                Transport train = trainFactory->createTransport();
                Transport plane = planeFactory->createTransport();
                map<string, int> table = var->table();
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[0])))
                        car1 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[0], path[1]));

                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[2])))
                        car2 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[2], path[3]));
                      
                for (auto i = table.begin(); i != table.end(); i++) {
                    if ((*i).first.find(var->points(path[1])) && var->points(path[1]).find("TS")) {
                        train = trainFactory->createTransport(var->tableCost((*i).second * 3 + 1), var->matrixDist(path[1], path[2]));
                        track = Track(car1, car2, train, _volume);
                    }
                    
                    if ((*i).first.find(var->points(path[1])) && var->points(path[1]).find("AP")) {
                        plane = planeFactory->createTransport(var->tableCost((*i).second * 3), var->matrixDist(path[1], path[2]));
                        track = Track(car1, car2, plane, _volume);
                    }
                }
            }
                
            case 5: {
                Transport car1 = carFactory->createTransport();
                Transport car2 = carFactory->createTransport();
                Transport car3 = carFactory->createTransport();
                Transport train = trainFactory->createTransport();
                Transport plane = planeFactory->createTransport();
                map<string, int> table = var->table();
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[0])))
                        car1 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[0], path[1]));

                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[2])))
                        car2 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[2], path[3]));
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[4])))
                        car3 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[4], path[5]));
                
                for (auto i = table.begin(); i != table.end(); i++) {
                    if ((*i).first.find(var->points(path[1])) && var->points(path[1]).find("TS"))
                        train = trainFactory->createTransport(var->tableCost((*i).second * 3 + 1), var->matrixDist(path[1], path[2]));
                    
                    if ((*i).first.find(var->points(path[1])) && var->points(path[1]).find("AP"))
                        plane = planeFactory->createTransport(var->tableCost((*i).second * 3), var->matrixDist(path[1], path[2]));
                }

                for (auto i = table.begin(); i != table.end(); i++) {
                    if ((*i).first.find(var->points(path[3])) && var->points(path[3]).find("TS"))
                        train = trainFactory->createTransport(var->tableCost((*i).second * 3 + 1), var->matrixDist(path[3], path[4]));
                    
                    if ((*i).first.find(var->points(path[3])) && var->points(path[3]).find("AP"))
                        plane = planeFactory->createTransport(var->tableCost((*i).second * 3), var->matrixDist(path[3], path[4]));
                }

                track = Track(car1, car2, car3, train, plane, _volume);
            }

            case 7: {
                Transport car1 = carFactory->createTransport();
                Transport car2 = carFactory->createTransport();
                Transport car3 = carFactory->createTransport();
                Transport car4 = carFactory->createTransport();
                Transport train1 = trainFactory->createTransport();
                Transport train2 = trainFactory->createTransport();
                Transport plane = planeFactory->createTransport();
                map<string, int> table = var->table();
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[0])))
                        car1 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[0], path[1]));

                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[2])))
                        car2 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[2], path[3]));
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[4])))
                        car3 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[4], path[5]));
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[6])))
                        car4 = carFactory->createTransport(var->tableCost((*i).second * 3 + 2), var->matrixDist(path[6], path[7]));

                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[1])))
                        train1 = trainFactory->createTransport(var->tableCost((*i).second * 3 + 1), var->matrixDist(path[1], path[2]));
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[5])))
                        train2 = trainFactory->createTransport(var->tableCost((*i).second * 3 + 1), var->matrixDist(path[5], path[6]));
                
                for (auto i = table.begin(); i != table.end(); i++)
                    if ((*i).first.find(var->points(path[3])))
                        plane = planeFactory->createTransport(var->tableCost((*i).second * 3), var->matrixDist(path[3], path[4]));

                track = Track(car1, car2, car3, car4, train1, train2, plane, _volume);
            }
        }
        
        return track;
    }
};
