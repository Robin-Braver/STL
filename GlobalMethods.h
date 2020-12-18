#pragma once
#include"stdafx.h"
#include"Vector.h"

template<typename T>//冒泡排序,默认 不需要自己传入比较函数
void bubble_sort(T first, T last)
{
	auto end = --last;
	for(T cursor = first;cursor!=end;cursor++)
		for (T current = first; current != end; current++)
		{
			T temp = current;
			T temp_pre = temp++;//temp_pre是temp，temp是temp_pre后一个
			if ((*temp_pre) > (*(temp)))//前一个所指对象更大
			{
				auto t = (*temp_pre);
				(*temp_pre) = (*temp);
				(*temp) = t;
			}
		}
}



template<typename T,class Compare>//冒泡排序,默认 不需要自己传入比较函数
void bubble_sort(T first, T last,Compare cmp)
{
	auto end = --last;
	for (T cursor = first; cursor != end; cursor++)
		for (T current = first; current != end; current++)
		{
			T temp = current;
			T temp_pre = temp++;//temp_pre是temp，temp是temp_pre后一个
			if (cmp((*temp_pre),(*(temp))))//前一个所指对象更大
			{
				auto t = (*temp_pre);
				(*temp_pre) = (*temp);
				(*temp) = t;
			}
		}
}


template<typename T,class Con>
T Find_if(T first, T last,Con* condition) 
{
	while (first != last)
	{
		if (condition(*first))
			return first;
		++first;
	}
	return last;
}


bool self_compare1(int x, int y)//小于
{
	return (x < y);
}

template<typename T>//判断是否为偶数
bool Condition1(T x)
{
	if (x % 2 == 0)
		return true;
	else
		return false;
}

