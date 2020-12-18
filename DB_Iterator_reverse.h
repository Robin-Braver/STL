#pragma once
#include"DB_Iterator.h"


template<typename T>//List的双向访问迭代器
class rDB_Iterator
{
private:
	ListNode<T>* _ptr;//成员，一个指向链表的指针
public:
	rDB_Iterator() :_ptr(NULL) {}
	rDB_Iterator(ListNode<T>* obj) :_ptr(obj) {}//构造函数
	rDB_Iterator<T>(const rDB_Iterator<T>& obj) { _ptr = obj._ptr; }//拷贝构造
	~rDB_Iterator() { _ptr = NULL; }//析构函数


	ListNode<T>* getPtr() { return _ptr; }
	/*运算符重载*/
	rDB_Iterator<T>& operator++();//重载前置++操作运算符
	rDB_Iterator<T>& operator++(int);//重载后置++操作运算符
	rDB_Iterator<T>& operator--(); //重载--操作运算符
	rDB_Iterator<T>& operator--(int);//重载后置--操作运算符
	rDB_Iterator<T>& operator=(const rDB_Iterator<T>& obj1);//重载=运算符

	T& operator*() { return _ptr->data; }//重载*运算符,返回值为常量，禁止对集合内修改

	bool operator==(rDB_Iterator obj1) { return _ptr == obj1._ptr; };//重载==运算符
	bool operator!=(rDB_Iterator obj1) { return _ptr != obj1._ptr; };//重载!=运算符
};

template<typename T>
inline rDB_Iterator<T>& rDB_Iterator<T>::operator++()
{
	_ptr = _ptr->prev;
	return *this;
}

template<typename T>
inline rDB_Iterator<T>& rDB_Iterator<T>::operator++(int)
{
	rDB_Iterator<T>* temp = new rDB_Iterator<T>(*this);
	++(*this);
	return *temp;
}

template<typename T>
inline rDB_Iterator<T>& rDB_Iterator<T>::operator--()
{
	_ptr = _ptr->next;
	return *this;
}

template<typename T>
inline rDB_Iterator<T>& rDB_Iterator<T>::operator--(int)
{
	rDB_Iterator<T>* temp = new rDB_Iterator<T>(*this);
	--(*this);
	return *temp;
}

template<typename T>
inline rDB_Iterator<T>& rDB_Iterator<T>::operator=(const rDB_Iterator<T>& obj1)
{
	_ptr = obj1._ptr;
	return *this;
}