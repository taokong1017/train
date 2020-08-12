#include <iostream>

class Fraction
{
public:
    Fraction(long n, long d = 1)
    : mN(n/gcd(n, d))
    , mD(d/gcd(n, d))
    {

    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f)
    {
        return out << f.mN << "/" << f.mD;
        
    }

    Fraction operator+ (const Fraction& f)
    {
        long n = mN*f.mD + f.mN*mD;
        long d = mD*f.mD;
        return Fraction(n, d);
    }

    Fraction& operator+= (const Fraction f)
    {
        long n = mN*f.mD + f.mN*mD;
        long d = mD*f.mD;
        std::swap(mN, n);
        std::swap(mD, d);
        return *this;
    }

    Fraction operator- (const Fraction& f)
    {
        long n = mN*f.mD - f.mN*mD;
        long d = mD*f.mD;
        return Fraction(n, d);
    }

    Fraction operator* (const Fraction& f)
    {
        long n = mN*f.mN;
        long d = mD*f.mD;
        return Fraction(n, d);
    }

    Fraction operator/ (const Fraction& f)
    {
        long n = mN*f.mD;
        long d = mD*f.mN;
        return Fraction(n, d);
    }

    Fraction& operator++ ()
    {
        long n = mN+mD;
        std::swap(mN, n);
        return *this;
    }

    Fraction& operator-- ()
    {
        long n = mN-mD;
        std::swap(mN, n);
        return *this;
    }

    Fraction operator++ (int)
    {
        Fraction f(mN, mD);
        long n = mN+mD;
        std::swap(mN, n);
        return f;
    }

    Fraction operator-- (int)
    {
        Fraction f(mN, mD);
        long n = mN-mD;
        std::swap(mN, n);
        return f;
    }

    Fraction& operator= (const Fraction& f)
    {
        mN = f.mN;
        mD = f.mD;
        return *this;
    }
    
private:
    long gcd(long a, long b) { 
        //std::cout << "a=" << a << ", b=" << b <<std::endl;
        return b == 0 ? a : gcd(b, a % b);
    }

private:
    long mN;
    long mD;
};


int main(int argc, char **argv)
{
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    Fraction f3(1, 4);

    std::cout << f1 << " + " << f2 << " + " << f3 << " = " << f1 + f2 + f3 << std::endl;
    std::cout << f1 << " - " << f2 << " - " << f3 << " = " << f1 - f2 - f3 << std::endl;
    std::cout << f1 << " * " << f2 << " * " << f3 << " = " << f1 * f2 * f3 << std::endl;
    std::cout << f1 << " / " << f2 << " / " << f3 << " = " << f1 / f2 / f3 << std::endl;

    std::cout << f1 << " += " << f2 << " = " << (f1 += f2) << std::endl;
    std::cout << "++f1 = " << ++f1 << std::endl;
    std::cout << "--f1 = " << --f1 << std::endl;

    std::cout << "f1++ = " << f1++  << std::endl;
    std::cout << "f1-- = " << f1--  << std::endl;

    std::cout << "f1 = " << f1 << ", f2 = " << f2<< std::endl;
    f2=f1++;
    std::cout << "f2=f1++" << ", f1 = " << f1 << ", f2 = " << f2 << std::endl;
    std::cout << "f1 = " << f1 << ", f2 = " << f2<< std::endl;
    f2=f1--;
    std::cout << "f2=f1--" << ", f1 = " << f1 << ", f2 = " << f2 << std::endl;
    return 0;
}