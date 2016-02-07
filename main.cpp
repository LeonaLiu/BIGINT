/*
 * c++练习-1
 * 大整数类
 * 重载 +、-、*、<、>、<=、>=、==、>>(输入)、<<(输出)
 * created by Yang Liu
 * 2016.02.03
 * version: 1.0
 */
 
#include <iostream>
#include <string>
#include <vector>
#include "BigInt.h"

int test(void);

int main()
{
    std::cout <<"--------This program test BigInt Class--------" << std::endl << std::endl;
    std::cout <<"1: Calculate 200!" << std::endl;
    BigInt re_bi(1);
    const int num = 200;

    for (int i = 1;i <= num;i++)
    {
        re_bi *= i;
    }
    std::cout << num << "! = " << re_bi << std::endl;
    test();
    return 0;
}

 int test(void)
 {
    std::cout << std::endl <<"2: Initialize" << std::endl;
    
    //构造大整数
    BigInt bi_0; //默认初始化
    std::cout << "bi_0 : " << bi_0 << std::endl;
    
    BigInt bi_1("1234");    //c风格字符串
    std::cout<<"bi_1 : "<<bi_1<<std::endl;
    
    std::string str = "12345";
    BigInt bi_2(str);    //string
    std::cout << "bi_2 : " << bi_2 << std::endl;
    
    char c_str[] = "123456";
    BigInt bi_3(c_str);    //字符串数组
    std::cout<<"bi_3 : "<<bi_3<<std::endl;
    
    BigInt bi_4(1234567890123); //数字
    std::cout<<"bi_4 : "<<bi_4<<std::endl;

    const long long LONG_LONG_MIN = -9223372036854775807ll - 1;
    BigInt bi_4_2(LONG_LONG_MIN); //最小负数
    std::cout<<"bi_4_2 : "<<bi_4_2<<std::endl;
    
    std::cout << std::endl <<"3: Get BigInt from standard input" << std::endl;
    //从标准输入取数
    BigInt bi_5, bi_6;
    std::cout << "Plz input 2 number: ";
    std::cin >> bi_5 >> bi_6;
    std::cout << "bi_5 : " << bi_5 << std::endl;
    std::cout << "bi_6 : " << bi_6 << std::endl;
    //加法
    std::cout << "bi_5 + bi_6 : " << bi_5 + bi_6 << std::endl;
    //减法
    std::cout << "bi_5 - bi_6 : " << bi_5 - bi_6 << std::endl;
    //乘法
    std::cout << "bi_5 * bi_6 : " << bi_5*bi_6 << std::endl;

    std::cout << std::endl <<"4: Comparison operations" << std::endl;
    //比较运算
    BigInt bi_7("-1234567890");
    BigInt bi_8("234567890");
    BigInt bi_9("-234567890");
    BigInt bi_10("1234567890");
    std::cout<<bi_10<<(bi_10<=bi_8? "<=":">")<<bi_8<< std::endl; //正正
    std::cout<<bi_7<<(bi_7<=bi_9? "<=":">")<<bi_9<< std::endl; //负负
    std::cout<<bi_10<<(bi_10<=bi_9? "<=":">")<<bi_9<< std::endl; //正负
    std::cout<<bi_10<<(bi_10==bi_8? "=":"<>")<<bi_8<< std::endl; //相等
    std::cout<<bi_10<<(bi_10== -bi_7? "=":"<>")<<-bi_7<< std::endl; //取负
    return 0;
}
