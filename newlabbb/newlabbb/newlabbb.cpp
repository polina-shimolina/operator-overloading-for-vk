#include <iostream>

using namespace std;

void func(double num, double eps, int& ch, int& zn)
{
    int k = 1;
    if (num < 0) {
        k = -1;
        num = -num;
    }
    int a = 1; int b = 1;
    int mn = 2;
    int iter = 0;
    ch = a; zn = b;
    double c = 1;
    do {
        b++;
        c = (double)a / b;
    } while ((num - c) < 0);
    if ((num - c) < eps)
    {
        ch = k*a; zn = b;
        return;
    }
    b--;
    c = (double)a / b;
    if ((num - c) > -eps)
    {
        ch = k*a; zn = b;
        return;
    }
    while (iter < 20000)
    {
        int cc = a * mn, zz = b * mn;
        iter++;
        do {
            zz++;
            c = (double)cc / zz;
        } while ((num - c) < 0);
        if ((num - c) < eps)
        {
            ch = k*cc; zn = zz;
            return;
        }
        zz--;
        c = (double)cc / zz;
        if ((num - c) > -eps)
        {
            ch = k*cc; zn = zz;
            return;
        }
        mn++;
    }
}

class F
{
public:
    mutable int n, d, a;
    F(int A, int N, int D) {
        int k=1;
        if (A < 0) {
            k *= -1;
            A = -A;
        }
        if (N < 0) {
            k *= -1;
            N = -N;
        }
        if (D < 0) {
            k *= -1;
            D = -D;
        }
            n = k*(N + A * D);
            d = D;
    }
    F(int N, int D) {
        n = N; 
        d = D;
    }
    F(int A) {
        n = A;
        d = 1;
    }
    F(double A) {
        double inp;
        int ch, zn;
        double eps = 0.0000001;
        inp = A;
        func(inp, eps, ch, zn);
        n = ch;
        d = zn;
    }
    F operator=(F& i);
    F operator++(int);
    F operator--(int);
    F& operator= (const F& f) {
        n = f.n;
        d = f.d;
        return *this;
    }
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
    int k = 1;
    if (f->n < 0) { k = -k; f->n = -f->n; }
        if (f->n / f->d >= 1) { // неправильная
            if (f->n % f->d == 0) { // целое число
                
                f->a = k*(f->n / f->d);
                f->n = 0;
            }
            else { //

                f->a = (f->n / f->d);
                f->n -= f->d * f->a;
                f->a = k * f->a;
            }
        }
        else { f->a = 0; f->n = k*f->n; f->d = f->d; } // правильная
    
        
    
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

F operator - (const F& i) //унарный -
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

F operator + (const F& i) // унарный +
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
    F A(1, 3), B(3, 2), C(1, 2, 3), D(-2, 4, 5), E(-7, 3), H(-0.25), I(-2, 7, 3);
    cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << H << "  " << I << endl;
    F G = A + C;
    cout << G << endl;
    F J = A + B;
    cout << J << endl;
    J = C + H;
    cout << J << endl;
    J = I - A;
    cout << J << endl;
    J = B - H;
    cout << J << endl;
    J = A * B;
    cout << J << endl;
    J = C * D;
    cout << J << endl;
    J = H * I;
    cout << J << endl;
    J = E / H;
    cout << J << endl;
    J = A < B;
    cout << J << endl;
    J = D > H;
    cout << J << endl;
    J = B == C;
    cout << J << endl;
    return 0;
}