/*
 * c++练习-1
 * 大整数类
 * 重载 +、-、*、<、>、<=、>=、==、>>(输入)、<<(输出)
 * created by Yang Liu
 * 2016.02.03
 * version: 1.0
 */

#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BigInt
{
public:
    BigInt():sign{1},is_zero{true}{};
    BigInt(long long num);
    BigInt(const string& str) { FromString(str); };
    BigInt(const BigInt& bi):data(bi.data),sign(bi.sign),is_zero(bi.is_zero){};

    BigInt& operator=(const BigInt &bi);
    BigInt& operator+=(const BigInt &rhs);
    BigInt& operator-=(const BigInt &rhs);
    BigInt& operator*=(const BigInt &rhs);
    const BigInt operator-(void) const; //取负

    const string ToString(void) const;
    
private:
    vector<unsigned int> data;
    int sign;
    bool is_zero;
    const long long I64_MIN = -9223372036854775807ll - 1;
    
    void FromString(const string& str);
    void ClearZeroLeft(void);
    BigInt& Neg(void);
    BigInt& Add(const BigInt &rhs, const unsigned int pos);
    BigInt& Sub(const BigInt &rhs);
    BigInt Mul(const BigInt &rhs) const;
    
    friend std::istream& operator>>(istream& in, BigInt& bi);
    friend std::ostream& operator<<(ostream& out, const BigInt& bi);
    
    friend const BigInt operator+(const BigInt &lhs, const BigInt &rhs);
    friend const BigInt operator-(const BigInt &lhs, const BigInt &rhs); //减法
    friend const BigInt operator*(const BigInt &lhs, const BigInt &rhs);
  
    friend bool operator<(const BigInt &lhs, const BigInt &rhs);
    friend bool operator<=(const BigInt &lhs, const BigInt &rhs);
    friend bool operator>(const BigInt &lhs, const BigInt &rhs);
    friend bool operator>=(const BigInt &lhs, const BigInt &rhs);
    friend bool operator==(const BigInt &lhs, const BigInt &rhs);
    friend bool operator!=(const BigInt &lhs, const BigInt &rhs);
};

#endif
