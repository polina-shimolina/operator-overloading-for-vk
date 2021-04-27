#pragma once
#include <iostream>
class F
{
public:
    mutable int n, d, a;
    F(int A, int N, int D);
    F(int N, int D);
    F(int A);
    F(double A);
    F operator=(F& i);
    F operator++(int);
    F operator--(int);
    F& operator= (const F& f);
};
