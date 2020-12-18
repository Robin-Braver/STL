#pragma once
#include"HashTable.h"

template<typename T>
class HS_iterator
{
private:
	HashTable<T>* t_ptr;//指向表的指针
	ChainNode<T>* n_ptr;//指向元素指针
public:
	HS_iterator() :t_ptr(NULL), n_ptr(NULL) {}//构造函数
	HS_iterator(HashTable<T>* T_ptr, ChainNode<T>* N_ptr) :t_ptr(T_ptr), n_ptr(N_ptr) {}//构造函数
	HS_iterator(const HS_iterator& obj)//拷贝构造
	{
		t_ptr = obj.t_ptr;
		n_ptr = obj.n_ptr;
	}
	~HS_iterator()//析构函数
	{
		if (t_ptr)
			t_ptr = NULL;
		if (n_ptr)
			n_ptr = NULL;
	}
	/*操作符重载*/
	HS_iterator<T>& operator++();//重载前置++操作运算符
	HS_iterator<T>& operator++(int);//重载后置++操作运算符
	HS_iterator<T>& operator--();//重载--操作运算符
	HS_iterator<T>& operator--(int);//重载后置--操作运算符
	HS_iterator<T>& operator=(HS_iterator<T> obj1);//重载=运算符

	const T& operator*() { return n_ptr->data; }//重载*运算符,返回值为常量，禁止对集合内修改

	bool operator==(HS_iterator obj1) { return n_ptr == obj1.n_ptr; };//重载==运算符
	bool operator!=(HS_iterator obj1) { return n_ptr != obj1.n_ptr; };//重载!=运算符

};

template<typename T>
inline HS_iterator<T>& HS_iterator<T>::operator++()
{
	if (n_ptr->link != NULL)//当前指向元素的后继不空，直接返回后继
	{
		n_ptr = n_ptr->link;
		return *this;
	}
	int key = t_ptr->Cal_Hash(n_ptr->data,t_ptr->divisor);//否则获取插入位置，找到下一个位置
	for (int i = key + 1; i < t_ptr->divisor; i++)//找到下一个桶非空元素
		if (t_ptr->ht[i] != NULL)
		{
			n_ptr = t_ptr->ht[i];
			return *this;
		}
	n_ptr = NULL;
	return *this;//当前已是最后一个元素
};

template<typename T>
inline HS_iterator<T>& HS_iterator<T>::operator++(int)
{
	HS_iterator* temp = new HS_iterator(*this);
	++(*this);
	return *temp;
}

template<typename T>
inline HS_iterator<T>& HS_iterator<T>::operator--()
{
	int key = t_ptr->Cal_Hash(n_ptr->data, t_ptr->divisor);//获取位置
	if (t_ptr->ht[key] != n_ptr)//不是这个桶第一个元素
	{
		ChainNode<T>*pre = t_ptr->ht[key];
		while (pre->link != n_ptr)//找直接前驱
			pre = pre->link;
		n_ptr = pre;
		return *this;
	}

	for(int i=key-1;i>=0;i--)//找前桶非空元素
		if (t_ptr->ht[i] != n_ptr)
		{
			ChainNode<T>*pre = t_ptr->ht[i];
			while (pre->link!=NULL)//找最后一个元素
				pre = pre->link;
			n_ptr = pre;
			return *this;
		}
	n_ptr = NULL;
	return *this;//当前已是第一个元素
}

template<typename T>
inline HS_iterator<T>& HS_iterator<T>::operator--(int)
{
	HS_iterator* temp = new HS_iterator(*this);
	--(*this);
	return *temp;
}

template<typename T>
inline HS_iterator<T>& HS_iterator<T>::operator=(HS_iterator obj1)
{
	t_ptr = obj1.t_ptr;
	n_ptr = obj1.n_ptr;
	return *this;
}
