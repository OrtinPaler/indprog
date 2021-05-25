#include <map>
#include <string>
#include <tuple>
using namespace std;

constexpr auto SIZE = 16;

class Singleton {
private:
    static Singleton *var;

    string points_[SIZE] = { "msk_AP", "msk_TS", "msk_WH", "mzh_TS",
                           "mzh_WH", "zvn_WH", "NN_AP", "NN_TS",
                           "NN_WH", "dzr_TS", "dzr_WH", "vlg_AP",
                           "vlg_TS", "vlg_WH", "kam_TS", "kam_WH" };

    map<string, int> towns_ = { {"Moscow", 2},
                                {"Mozhaisk", 4},
                                {"Zvenigorod", 5},
                                {"Nizhniy Novgorod", 8},
                                {"Dzerzhinsk", 10},
                                {"Volgograd", 13},
                                {"Kamishin", 15} };

    map<string, int> table_ = { {"msk", 0},
                                {"mzh", 1},
                                {"zvn", 2},
                                {"NN", 3},
                                {"dzr", 4},
                                {"vlg", 5},
                                {"kam", 6} };

    tuple<int, int, double> tableCost_[21] = { {500, 300, 100},
                                               {200, 100, 500},
                                               {100, 60, 50},
                                               {0, 0, 0},
                                               {200, 100, 500},
                                               {100, 60, 50},
                                               {0, 0, 0},
                                               {0, 0, 0},
                                               {100, 60, 50},
                                               {500, 300, 100},
                                               {200, 100, 500},
                                               {100, 60, 50},
                                               {0, 0, 0},
                                               {200, 100, 500},
                                               {100, 60, 50},
                                               {500, 300, 100},
                                               {200, 100, 500},
                                               {100, 60, 50},
                                               {0, 0, 0},
                                               {200, 100, 500},
                                               {100, 60, 50} };

    int matrixDist_[SIZE][SIZE] = { {0, 20, 30, 108, 110, 65, 398, 0, 0, 0, 0, 926, 0, 0, 0, 0},
                                    {20, 0, 10, 98, 100, 55, 0, 415, 0, 483, 0, 0, 937, 0, 1204, 0},
                                    {30, 10, 0, 108, 110, 65, 0, 0, 430, 0, 390, 0, 0, 652, 0, 1234},
                                    {108, 98, 108, 0, 5, 0, 0, 0, 0, 581, 0, 0, 1035, 0, 1302, 0},
                                    {110, 100, 110, 5, 0, 78, 0, 0, 540, 0, 500, 0, 0 ,1062, 0, 1344},
                                    {65, 55, 65, 0, 78, 0, 0, 0, 495, 0, 455, 0, 0, 1017, 0, 1299},
                                    {398, 0, 0, 0, 0, 0, 0, 19, 23, 0, 26, 828, 0, 0, 0, 0},
                                    {0, 415, 0, 0, 0, 0 ,19, 0, 4, 32, 0, 0, 840, 0, 919, 0},
                                    {0, 0, 430, 0, 540, 495, 23, 4, 0, 0, 40, 0, 0, 849, 0, 1010},
                                    {0, 483, 0, 581, 0, 0, 0, 32, 0, 0, 4, 0, 872, 0, 951, 0},
                                    {0, 0, 390, 0, 500, 455, 26, 0, 40, 4, 0, 0, 0, 889, 0, 1050},
                                    {926, 0, 0, 0, 0 ,0 ,828, 0, 0 ,0 ,0, 0, 15, 16, 0, 285},
                                    {0, 937, 0, 1035, 0, 0, 0, 840, 0, 872, 0, 15, 0, 2, 257, 281},
                                    {0, 0, 952, 0, 1062, 1017, 0, 0, 849, 0, 889, 16, 2, 0, 0 ,282},
                                    {0, 1204, 0, 1302, 0, 0, 0, 919, 0, 951, 0, 0, 257, 0, 0, 2},
                                    {0, 0, 1234, 0, 1344, 1299, 0, 0, 1010, 0, 1050, 285, 281, 282, 2, 0} };
public:
    static Singleton *returnVar() {
        (var == nullptr) ? new Singleton() : var;
        return var;
    }
    
    int matrixDist(int m, int n) {
        return matrixDist_[m][n];
    }

    string points(int i) {
        return points_[i];
    }

    map<string, int> table() {
        return table_;
    }

    tuple<int, int, double> tableCost(int i) {
        return tableCost_[i];
    }
    
    map<string, int> towns() {
        return towns_;
    }
};
