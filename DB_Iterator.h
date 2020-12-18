#pragma once
#include"stdafx.h"
#include"List.h"



template <typename T>
struct ListNode  //链表结点类定义
{
	T data; //链表结点数据
	ListNode<T>* next;
	ListNode<T>*prev; //前驱、后继指针
};


template<typename T>//List的双向访问迭代器
class DB_Iterator
{
private:
	ListNode<T>*  _ptr;//成员，一个指向链表的指针
public:
	DB_Iterator() :_ptr(NULL) {}
	DB_Iterator(ListNode<T>* obj):_ptr(obj) {}//构造函数
	DB_Iterator<T>(const DB_Iterator<T>& obj) { _ptr = obj._ptr; }//拷贝构造
	~DB_Iterator() { _ptr = NULL; }//析构函数
	

	ListNode<T>* getPtr() { return _ptr; }
	/*运算符重载*/
	DB_Iterator<T>& operator++();//重载前置++操作运算符
	DB_Iterator<T>& operator++(int);//重载后置++操作运算符
	DB_Iterator<T>& operator--(); //重载--操作运算符
	DB_Iterator<T>& operator--(int);//重载后置--操作运算符
	DB_Iterator<T>& operator=(const DB_Iterator<T>& obj1);//重载=运算符

	T& operator*() { return _ptr->data; }//重载*运算符,返回值为常量，禁止对集合内修改

	bool operator==(DB_Iterator obj1) { return _ptr == obj1._ptr; };//重载==运算符
	bool operator!=(DB_Iterator obj1) { return _ptr != obj1._ptr; };//重载!=运算符
};

template<typename T>
inline DB_Iterator<T>& DB_Iterator<T>::operator++()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename T>
inline DB_Iterator<T>& DB_Iterator<T>::operator++(int)
{
	DB_Iterator<T>* temp = new DB_Iterator<T>(*this);
	++(*this);
	return *temp;
}

template<typename T>
inline DB_Iterator<T>& DB_Iterator<T>::operator--()
{
	_ptr = _ptr->prev;
	return *this;
}

template<typename T>
inline DB_Iterator<T>& DB_Iterator<T>::operator--(int)
{
	DB_Iterator<T>* temp = new DB_Iterator<T>(*this);
	--(*this);
	return *temp;
}

template<typename T>
inline DB_Iterator<T>& DB_Iterator<T>::operator=(const DB_Iterator<T>& obj1)
{
	_ptr = obj1._ptr;
	return *this;
}
