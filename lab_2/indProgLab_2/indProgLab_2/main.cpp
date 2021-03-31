#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

std::string system(double a, double b, double c, double d, double e, double f) {
    if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0))
        return "5";
    else if ((a * d - c * b != 0) && ((e * d - b * f != 0) || (a * f - c * e != 0))) {
        double y = (a * f - c * e) / (a * d - c * b);
        double x = (d * e - b * f) / (d * a - b * c);
        return "2 " + std::to_string(x) + ' ' + std::to_string(y);
    } else if (((a * d - c * b == 0) && ((e * d - b * f != 0) || (a * f - c * e != 0))) ||
               (a == 0 && c == 0 && e / b != f / d) ||
               (b == 0 && d == 0 && e / a != f / c) ||
               (a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0))) {
        if (((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
            (c == 0 && d == 0 && f == 0 && b != 0 && a == 0))) {
            double y = 0.0;
            if (b == 0)
                y = f / d;
            else if (d == 0)
                y = e / b;
            else if (e == 0 || f == 0)
                y = 0;
            return "4 " + std::to_string(y);
        } else if (((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
                    (c == 0 && d == 0 && f == 0 && a != 0 && b == 0))) {
            double x = 0.0;
            if (a == 0)
                x = f / c;
            else if (c == 0)
                x = e / a;
            else if (e == 0 || f == 0)
                x = 0;
            return "3 " + std::to_string(x);
        } else
            return "0";
    } else if (a == 0 && c == 0) {
        double y;
        if (e == 0)
            y = f / d;
        else if (f == 0)
            y = e / b;
        else
            y = e / b;
        return "4 " + std::to_string(y);
    } else if (b == 0 && d == 0) {
        double x;
        if (e == 0)
            x = f / c;
        else if (f == 0)
            x = e / a;
        else
            x = e / a;
        return "3 " + std::to_string(x);
    } else if (b == 0 && e == 0) {
        double k, n;
        k = -c / d;
        n = f / d;
        return "1 " + std::to_string(k) + ' ' + std::to_string(n);
    } else if (d == 0 && f == 0) {
        double k, n;
        k = -a / b;
        n = e / b;
        return "1 " + std::to_string(k) + ' ' + std::to_string(n);
    } else if (a == 0 && e == 0) {
        double k, n;
        k = -d / c;
        n = f / c;
        return "1 " + std::to_string(k) + ' ' + std::to_string(n);
    } else if (c == 0 && f == 0) {
        double k, n;
        k = -b / a;
        n = e / a;
        return "1 " + std::to_string(k) + ' ' + std::to_string(n);
    } else if ((a / b == c / d)) {
        double k, n;
        k = -c / d;
        n = f / d;
        return "1 " + std::to_string(k) + ' ' + std::to_string(n);
    }
    else
        return "Are you kidding me?";
}

void TestSystem(void) {
    assert(system(0, 0, 0, 0, 0, 0) == "5");
    assert(system(1, 2, 3, 4, 5, 6) == "2 -4.000000 4.500000");
    assert(system(0, 0, 0, 1, 0, 2) == "4 2.000000");
    assert(system(1, 0, 0, 0, 2, 0) == "3 2.000000");
    assert(system(0, 0, 0, 0, 1, 2) == "0");
    assert(system(0, 2, 0, 3, 4, 6) == "4 2.000000");
    assert(system(2, 0, 3, 0, 4, 6) == "3 2.000000");
    assert(system(1, 0, 3, 2, 0, 0) == "1 -1.500000 0.000000");
    assert(system(3, 1, 2, 0, 0, 0) == "1 -3.000000 0.000000");
    assert(system(0, 1, 2, 3, 0, 0) == "1 -1.500000 0.000000");
    assert(system(1, 3, 0, 2, 0, 0) == "1 -3.000000 0.000000");
    assert(system(1, 2, 4, 8, 1, 4) == "1 -0.500000 0.500000");
    std::cout << "Test OK" << std::endl;
}

int main(void) {
    TestSystem();
    return 0;
}
