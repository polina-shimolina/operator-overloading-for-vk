
#include <iostream>
using namespace std;
class F
{
private:
    
public:
    mutable int n, d, a;
    F(int A, int N, int D) {
        n = N + A * D;
        d = D;
        
    }
    F(int N, int D) {
        n = N; 
        d = D;
    }
    F(double A) {
        n = A;
        d = 1;
    }
    F(){}
    F operator=(F& i);
    F operator++(int);
    F operator--(int);

    
};
int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    a = a > 0 ? a : -a;
    b = b > 0 ? b : -b;
    while (a != b) {
        if (a > b)a -= b;
        else b -= a;
    }
    return a;
}
void norm(F* f) {
    int d = gcd(f->n, f->d);
    f->n /= d;
    f->d /= d;
    if (f->d < 0) {
        f->d *= -1;
        f->n *= -1;
    }
}

void normres(F* f) {
    if (f->n > 0) { // дробь > 0
        if (f->n / f->d >= 1) { // неправильная
            if (f->n % f->d == 0) { // целое число
                f->a = f->n / f->d;
                f->n = 0;
            }
            else { // 
                f->a = f->n / f->d;
                f->n -= f->d * f->a;
            }
        }
        else { f->a = 0; f->n = f->n; f->d = f->d; } // правильная
    }
    else { // дробь < 0
        f->n = -f->n;
        if (f->n / f->d >= 1) { // неправильная
            if (f->n % f->d == 0) { // целое число
                f->a = -(f->n / f->d);
                f->n = 0;
            }
            else { // 
                f->a = -(f->n / f->d);
                f->n -= f->d * f->a;
            }
        }
        else { f->a = 0; f->n = -f->n; } // правильная
    }
}

F F::operator = (F& i)
{
    F res = F(this->n = i.n, this->d = i.d);
    norm(&res);
    return res;
}

F operator + (const F& i1, const F& i2)
{
    F res = F(i1.n * i2.d + i2.n * i1.d, i1.d * i2.d);
    norm(&res);
    return res;
}

F operator - (const F& i)
{
    F res = F(i.n * -1, i.d);
    norm(&res);
    return res;
}

F operator - (const F& i1, const F& i2) {
    F res = F(i1.n * i2.d - i2.n * i1.d, i1.d * i2.d);
    norm(&res);
    return res;
}

F operator * (const F& i1, const F& i2)
{
    F res = F(i1.n * i2.n, i1.d * i2.d);
    norm(&res);
    return res;
}

F operator / (const F& i1, const F& i2)
{
    F i = F(i2.d, i2.n);
    F res = i1 * i;
    norm(&res);
    return res;
}

F operator + (const F& i)
{
    F res = i;
    norm(&res);
    return res;
}



F F::operator ++ (int)
{
    F res = F(this->n+=d, d);
    norm(&res);
    return res;
}

F F::operator -- (int)
{
    F res = F(this->n -= d, d);
    norm(&res);
    return res;
}


F operator += (const F& i1, const F& i2)
{
    F i = i1 + i2;
    norm(&i);
    i1.d = i.d;
    i1.n = i.n;
    return i1;
}

F operator -= (const F& i1, const F& i2)
{
    F i = i1 - i2;
    norm(&i);
    i1.d = i.d;
    i1.n = i.n;
    return i1;
}

F operator *= (const F& i1, const F& i2)
{
    F i = i1 * i2;
    norm(&i);
    i1.d = i.d;
    i1.n = i.n;
    return i1;
}

F operator /= (const F& i1, const F& i2)
{
    F i = i1 / i2;
    norm(&i);
    i1.d = i.d;
    i1.n = i.n;
    return i1;
}

const bool operator < (const F& i1, const F& i2)
{
    return i1.n*i2.d < i2.n*i1.d;
}

const bool operator <= (const F& i1, const F& i2)
{
    return i1.n * i2.d <= i2.n* i1.d;
}

const bool operator > (const F& i1, const F& i2)
{
    return i1.n * i2.d > i2.n* i1.d;
}

const bool operator >= (const F& i1, const F& i2)
{
    return i1.n * i2.d >= i2.n* i1.d;
}

const bool operator == (const F& i1, const F& i2)
{
    if (i1.n*i2.d == i2.n*i1.d)
        return true;
    return false;
}

const bool operator != (const F& i1, const F& i2)
{
    return !(i1 == i2);
}
 
const bool operator && (F& i1, F& i2)
{
    if (i1 != F(0) && i2 != F(0))
        return true;
    else return false;
}

const bool operator || (F& i1, F& i2)
{
    if (i1 == F(0) || i2 == F(0))
        return false;
    else return true;
}

const bool operator !(F& i) 
{
    if (i == F(0)) return true;
    else return false;
}

ostream& operator << (ostream& s, const F& i)
{
    F k = i;
    normres(&k);
    if (k.a == 0) {
        if (k.n == 0) {
            s << 0;
        }
        else {
            s << k.n << "/" << k.d;
        }
    }
    else {
        if (k.n == 0) {
            s << k.a;
        }
        else {
            s << k.a << " " << k.n << "/" << k.d;
        }
    }
    return s;
}

istream& operator >> (istream& s, F& i)
{
    cin >> i.n >> i.d;
    return s;
}

const F operator & (const F& i1, const F& i2)
{
    return F(i1.n & i2.n, i1.d & i2.d);
}

const F operator | (const F& i1, const F& i2)
{
    return F(i1.n | i2.n, i1.d | i2.d);
}


//

F operator + (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 + i2;
}

F operator - (const F& i1, const double a) {
    F i2 = F(a);
    return i1 - i2;
}

F operator * (const F& i1, const double a)
{
    F i2 = F(a);
    return i1*i2;
}

F operator / (const F& i1, const double a)
{
    F i2 = F(a);
    return i1/i2;
}

F operator += (const F& i1, const double a)
{
    F i2 = F(a);
    return i1+=i2;
}

F operator -= (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 -= i2;
}

F operator *= (const F& i1, const double a)
{
    F i2 = F(a);
    return i1*=i2;
}

F operator /= (const F& i1, const double a)
{
    F i2 = F(a);
    return i1/=i2;
}

const bool operator < (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 < i2;
}

const bool operator <= (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 <= i2;
}

const bool operator > (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 > i2;
}

const bool operator >= (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 >= i2;
}

const bool operator == (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 == i2;
}

const bool operator != (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 != i2;
}

const bool operator && (F& i1, double a)
{
    F i2 = F(a);
    return i1 && i2;
}

const bool operator || (F& i1, double a)
{
    F i2 = F(a);
    return i1 || i2;
}

const F operator & (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 & i2;
}

const F operator | (const F& i1, const double a)
{
    F i2 = F(a);
    return i1 | i2;
}



int main()
{
    F A(1, 2), B(1, 3, 3);
    F G = A / B;
    cout << G;
}
















// ^ % ~ &=, |=, ^=, <<=, >>= [], (), ((у:)*, &, ->, ->*) new delete