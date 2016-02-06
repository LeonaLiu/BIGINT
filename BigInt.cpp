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
#include <cctype>
#include <algorithm>
#include <vector>
#include <iterator>
#include <stdexcept>
#include "BigInt.h"

using namespace std;

//从数字初始化
void BigInt::TransferFromNumber(long long num)
{
	sign = 1;
	if(0 == num) 
	{
		is_zero = true;
	}
	else
	{
		is_zero = false;
		bool out_of_range = false;
		if (num<0) //小于0，取负
		{
			if (I64_MIN  ==  num)//最小的负数
			{
				++num;  //+1防止取负时溢出
				out_of_range = true; //溢出标志
			}
			sign = -1;
			num = -num;
		}

		while (num)
		{
			data.push_back(num % 10);
			num /= 10;
		}

		if (out_of_range)//将多加的1减掉
		{
			++data[0];
		}
	}
}

//分析字符串，转换成大整数
void BigInt::TransferFromString(const string& str)
{
	sign = 1;
	if (str.empty())
	{
		is_zero = true;//空字符串返回0
	}
	else
	{
		is_zero = false;
		int end = 0;
		if (str[0] == '-' || str[0] == '+')
		{
			end = 1; //可能存在符号位
		}
		if (str[0] == '-')
		{
			sign = -1; //负数
		}
		try
		{
			for (int i = str.length() - 1;i >= end;i--)
			{
				if (isdigit(str[i]))
				{
					data.push_back(str[i] - '0');
				}
				else //非数字字符
				{
					throw runtime_error("BigInt:Initial has ilegal char: ");
				}
			}
		}
		catch (runtime_error &err)
		{
			cout << err.what() << str << endl << "Plz try again." << endl;
			data.clear();
			is_zero = true;
			sign = 1;
			return;
		}
		ClearZeroLeft();
	}
}

//赋值
BigInt& BigInt::operator=(const BigInt &bi)
{
	this->data = bi.data;
	this->is_zero = bi.is_zero;
	this->sign = bi.sign;
	return *this;
}

//加等
BigInt& BigInt::operator+=(const BigInt &rhs)
{
	*this = *this + rhs;
	return *this;
}

//减等
BigInt& BigInt::operator-=(const BigInt &rhs)
{
	*this = *this - rhs;
	return *this;
}

//乘等
BigInt& BigInt::operator*=(const BigInt &rhs)
{
	*this = *this * rhs;
	return *this;
}

//取负，返回原数取负的副本
const BigInt BigInt::operator-(void) const
{
	if (this->is_zero)
	{
		return *this;
	}
	BigInt re_bi(*this);
	re_bi.sign *= -1;
	return re_bi;
}

//将大整数转为字符串
const string BigInt::GetStr(void) const
{
	if(is_zero)
	{
		return string("0");
	}
	string str;
	if(-1==sign) str = "-";
	std::transform(data.crbegin(),data.crend(),back_inserter(str)
		,[](const unsigned int i){return i+'0';});
	return str;
}

//加法
const BigInt operator+(const BigInt &lhs, const BigInt &rhs)
{
	if(lhs.is_zero) //0+？
	{
		return rhs;
	}
	if(rhs.is_zero) //?+0
	{
		return lhs;
	}
	
	if(lhs.sign*rhs.sign<0) //异号转减法
	{
		return (lhs.sign>0? lhs-(-rhs):rhs-(-lhs));
	}
	
	//同号加法
	BigInt re_bi = lhs.Add(rhs, 0);
	re_bi.sign = lhs.sign;//符号
	return re_bi;
}

//带偏移的正数加法
const BigInt BigInt::Add(const BigInt &rhs, const unsigned int pos) const
{
	BigInt re_bi;
	re_bi.is_zero = false;//结果=0的情况已经在调用此函数前排除
	auto it_l=this->data.cbegin()+pos;
	auto it_r=rhs.data.cbegin();
	std::copy(this->data.cbegin(),it_l,back_inserter(re_bi.data)); //copy偏移的部分
	
	unsigned int carry = 0; //进位
	while(it_l!= this->data.cend()||it_r!=rhs.data.cend())
	{
		auto lnum = (it_l!= this->data.cend())? *it_l++:0;
		auto rnum = (it_r!=rhs.data.cend())? *it_r++:0;
		auto tmp_add = lnum + rnum + carry;
		carry = tmp_add / 10;
		re_bi.data.push_back(tmp_add % 10);
	}
	if(carry)
	{
		re_bi.data.push_back(carry);
	}
	return re_bi;
}

//减法
const BigInt operator-(const BigInt &lhs, const BigInt &rhs)
{
	if(lhs.is_zero)//0-?
	{
		return -rhs;
	}
	if(rhs.is_zero)//?-0
	{
		return lhs;
	}
	
	if(lhs.sign*rhs.sign<0)//异号
	{
		if(lhs.sign>0)//正-负 转加法
		{
			return	lhs + (-rhs);
		}
		else		//负-正 转加法取负
		{
			return -((-lhs) + rhs);
		}
	}
	if(lhs.sign<0) return (-rhs)-(-lhs);//负-负 换位置减法

	//正-正
	if(lhs<rhs)
	{
		//小-大 交换被减数与减数 结果取负
		//避免最高位出现借位的繁琐处理
		return -(rhs-lhs);
	}
	BigInt re_bi;
	re_bi.is_zero = false;
	unsigned int carry = 0; //借位
	for(auto it_l=lhs.data.cbegin(),it_r=rhs.data.cbegin()
		;it_l!=lhs.data.cend()||it_r!=rhs.data.cend();)
	{
		auto lnum = (it_l!=lhs.data.cend())? *it_l++:0;
		auto rnum = (it_r!=rhs.data.cend())? *it_r++:0;
		int tmp_minus = lnum - rnum - carry; //结果可能是负数，不能用auto
		if(tmp_minus<0)
		{
			carry = 1;
			tmp_minus +=10;
		}
		else
		{
			carry = 0;
		}
		re_bi.data.push_back(tmp_minus);
	}
	re_bi.ClearZeroLeft();
	return re_bi;
}

//去除计算后高位可能存在的0
void BigInt::ClearZeroLeft(void)
{
	while(!data.empty() && 0==data.back())
	{
		//除去高位0
		data.pop_back();
	}
	if(data.empty())//结果=0
	{
		is_zero = true;
	}
}

//乘法
const BigInt operator*(const BigInt &lhs, const BigInt &rhs)
{
	if(lhs.is_zero || rhs.is_zero)//任一乘数=0
	{
		return BigInt();
	}
	
	//非0两数相乘
	const BigInt &min_hs = lhs.data.size()<=rhs.data.size()? lhs:rhs;
	const BigInt &max_hs = lhs.data.size()<=rhs.data.size()? rhs:lhs;
	BigInt re_bi;
	int i = 0;
	for(auto it_min=min_hs.data.cbegin();it_min!=min_hs.data.cend();it_min++,i++)
	{
		//乘数是个位数
		if(0 == *it_min)//某数位=0 跳过
		{
			re_bi.data.push_back(0); //占位
			continue;
		}
		BigInt t_bi;
		unsigned int carry = 0;
		for(auto it_max=max_hs.data.cbegin();it_max!=max_hs.data.cend();it_max++)
		{
			auto tmp_multi = *it_min * *it_max + carry;
			carry = tmp_multi / 10;
			t_bi.data.push_back(tmp_multi % 10);
		}
		if(carry)
		{
			t_bi.data.push_back(carry);
		}
		//将结果累加
		re_bi = re_bi.Add(t_bi, i);
	}
	//符号
	re_bi.sign = lhs.sign*rhs.sign;
	return re_bi;
}

//输入
std::istream& operator>>(istream& in, BigInt& bi)
{
	string str;
	in>>str;
	bi.TransferFromString(str);
	return in;
}

//输出
std::ostream& operator<<(ostream& out, const BigInt& bi)
{
	if(bi.is_zero)
	{
		return out<<"0";
	}
	else
	{
		return out << bi.GetStr();
	}
}

//小于
bool operator<(const BigInt &lhs, const BigInt &rhs)
{
	if(lhs.is_zero && rhs.is_zero) //0<0
	{
		return false;
	}
	if(lhs.is_zero)  //0<?
	{
		return (rhs.sign>0? true:false);
	}
	if(rhs.is_zero)  //?<0
	{
		return (lhs.sign>0? false:true);
	}
	if(lhs.sign*rhs.sign<0)  //异号
	{
		return (lhs.sign>0? false:true);
	}
	if(lhs.sign<0)  //同负
	{
		return (-rhs)<(-lhs); //取负交换位置
	}
	
	if(lhs.data.size() != rhs.data.size())//同正位数不同
	{
		return (lhs.sign>0? 
			lhs.data.size()<rhs.data.size():lhs.data.size()>rhs.data.size());
	}
	
	for(int i=lhs.data.size()-1;i>=0;i--)//同正位数相同
	{
		if(lhs.data[i]<rhs.data[i]) return true;
	}
	return false;
}

//小于等于
bool operator<=(const BigInt &lhs, const BigInt &rhs)
{
	return (lhs < rhs) || (lhs == rhs);
}

//大于
bool operator>(const BigInt &lhs, const BigInt &rhs)
{
	return rhs < lhs;
}

//大于等于
bool operator>=(const BigInt &lhs, const BigInt &rhs)
{
	return (lhs > rhs) || (lhs == rhs);
}

//相等
bool operator==(const BigInt &lhs, const BigInt &rhs)
{
	if(lhs.is_zero||rhs.is_zero)  //0=?
	{
		return lhs.is_zero==rhs.is_zero;
	}
	if(lhs.sign*rhs.sign<0) 	//异号
	{
		return false;
	}
	if(lhs.data.size() != rhs.data.size())  //位数不同
	{
		return false;
	}
	//位数相同，比较各位数字
	return std::equal(lhs.data.cbegin(),lhs.data.cend(),rhs.data.cbegin());
}

//不等
bool operator!=(const BigInt &lhs, const BigInt &rhs)
{
	return !(lhs == rhs);
}


