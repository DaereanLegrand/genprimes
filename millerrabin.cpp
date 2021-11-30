#include <iostream>
#include <vector>
#include <NTL/ZZ.h>

using NTL::ZZ;

bool witness(ZZ, ZZ);
bool miller(ZZ, ZZ);
bool invector(std::vector<ZZ>, ZZ);
ZZ moduloZZ(ZZ, ZZ);
ZZ powmod(ZZ, ZZ, ZZ);
inline ZZ base(ZZ);
ZZ genprimecandidate(int);
ZZ generateprime(int);

int
main()
{
    std::cout << "1. Encontrar todos los primos de 100 cifras:\n";
    for (ZZ i = NTL::conv<ZZ>("101"); i < 1000; i += 2)
        if (!miller(i, ZZ(3))) {
            std::cout << i << std::endl;
        }
    
    std::cout << "2. Encontrar los primos diferentes de 10 bits:\n";
    std::vector<ZZ> res;
    for (int i = 0; i < 100; i++) {
        ZZ t = generateprime(10);
        while (invector(res, t) == true)
            t = generateprime(10);
        res.push_back(t);
    }
    for (ZZ i: res)
        std::cout << i << std::endl;
}

bool 
witness(ZZ u, ZZ n)
{
    ZZ x = powmod(1 + NTL::RandomBnd(n - 2), u, n);
    if (x == 1 || x == n - 1)
        return false;
    else {
        for (ZZ i = u; i < n; i *= 2) {
            x = powmod(x, ZZ(2), n);
            if (x == n - 1)
                return false;
        }
        return true;
    }
}

bool
miller(ZZ n, ZZ s)
{
    ZZ u = base(n);
    if (u % 2 == false)
        return false;
    for (ZZ i = NTL::conv<ZZ>("0"); i < s; i++) {
        if (witness(u, n))
            return true;
    }
    return false;
}

bool
invector(std::vector<ZZ> v, ZZ a)
{
    for (ZZ i: v)
        if (i == a)
            return true;
    return false;
}

ZZ
moduloZZ(ZZ a, ZZ b) 
{
    ZZ res = a - ((a / b) * b);
    return res + (res < 0) * b;
}

ZZ 
powmod(ZZ a, ZZ b, ZZ N)
{
    ZZ cumulativeExponent, newB, nMod, lastSquare, lastExponent, otherSquare, two;
    cumulativeExponent = 1;
    newB = b;
    lastSquare = a;
    lastExponent = 0;
    otherSquare = 1;
    two = 2;
    do
    {
        nMod = moduloZZ(newB, two);
        if (cumulativeExponent != 1) lastSquare = moduloZZ(lastSquare * lastSquare, N);
        if (nMod == 1)
        {
            lastExponent = lastExponent + cumulativeExponent;
            otherSquare = moduloZZ(lastSquare * otherSquare, N);
        }
        newB = newB / 2;
        cumulativeExponent = cumulativeExponent * 2;
    }
    while (newB > 0);
    return otherSquare;
}

inline ZZ
base (ZZ n)
{
    ZZ u = n - 1;
    while (u % 2 == 0)
        u /= 2;
    return u;
}

ZZ 
genprimecandidate (int b)
{
    ZZ m = ZZ(2);
    for (int i = 0; i < b - 1; i++)
        m *= 2;
    ZZ r = NTL::RandomBnd(m);
    return r | (m + 1);
}

ZZ
generateprime(int b)
{
    ZZ r = genprimecandidate(b);
    while (miller(r, ZZ(4)))
        r += 2;
    return r;
}
