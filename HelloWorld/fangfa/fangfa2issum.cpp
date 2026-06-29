#include <iostream>
#include "fangfa2sum.h"
using namespace std;
double sum(double a, double b) {
    return a + b;
}
double sub(double a, double b) {
    return a - b;
}
double mul(double a, double b) {
    return a * b;
}
double chu(double a, double b) {
    if (b == 0) {
        cout << "除数不能为0" << endl;
        return 0;
    }
    return a / b;
}