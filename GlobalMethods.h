#pragma once
#include"stdafx.h"
#include"Vector.h"

template<typename T>//ð������,Ĭ�� ����Ҫ�Լ�����ȽϺ���
void bubble_sort(T first, T last)
{
	auto end = --last;
	for(T cursor = first;cursor!=end;cursor++)
		for (T current = first; current != end; current++)
		{
			T temp = current;
			T temp_pre = temp++;//temp_pre��temp��temp��temp_pre��һ��
			if ((*temp_pre) > (*(temp)))//ǰһ����ָ�������
			{
				auto t = (*temp_pre);
				(*temp_pre) = (*temp);
				(*temp) = t;
			}
		}
}



template<typename T,class Compare>//ð������,Ĭ�� ����Ҫ�Լ�����ȽϺ���
void bubble_sort(T first, T last,Compare cmp)
{
	auto end = --last;
	for (T cursor = first; cursor != end; cursor++)
		for (T current = first; current != end; current++)
		{
			T temp = current;
			T temp_pre = temp++;//temp_pre��temp��temp��temp_pre��һ��
			if (cmp((*temp_pre),(*(temp))))//ǰһ����ָ�������
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


bool self_compare1(int x, int y)//С��
{
	return (x < y);
}

template<typename T>//�ж��Ƿ�Ϊż��
bool Condition1(T x)
{
	if (x % 2 == 0)
		return true;
	else
		return false;
}

