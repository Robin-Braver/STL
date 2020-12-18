#pragma once
#include"stdafx.h"


/*随机访问迭代器*/
template<typename T>
struct RA_iterator
{
	T* _ptr;//指向容器中元素的指针
	RA_iterator() :_ptr(NULL) {}//构造函数
	RA_iterator(T* ptr) :_ptr(ptr) {}//构造函数
	RA_iterator(const RA_iterator& obj)//拷贝构造
	{
		_ptr = obj._ptr;
	}
	~RA_iterator()//析构函数
	{
		if (_ptr)
			_ptr = NULL;
	}
	/*操作符重载*/
	RA_iterator& operator++();//重载前置++操作运算符
	RA_iterator& operator++(int);//重载后置++操作运算符
	RA_iterator& operator--();//重载--操作运算符
	RA_iterator& operator--(int);//重载后置--操作运算符
	RA_iterator& operator=(RA_iterator obj1);//重载=运算符
	RA_iterator& operator+=(size_t i);//重载+=运算符
	RA_iterator& operator-=(size_t i);//重载-=运算符
	RA_iterator operator+(size_t i);//重载+运算符
	RA_iterator operator-(size_t i);//重载-运算符

	size_t operator-(RA_iterator& obj1) { return (_ptr - obj1._ptr); }//重载-运算符,两迭代器相减

	T& operator[](size_t i)const { return _ptr[i]; };//重载[]运算符
	T& operator*() { return *_ptr; }//重载*运算符

	bool operator==(RA_iterator& obj1) { return _ptr == obj1._ptr; }//重载==运算符
	bool operator!=(RA_iterator obj1) { return _ptr != obj1._ptr; }//重载!=运算符
	bool operator<=(RA_iterator& obj1) { return _ptr <= obj1._ptr; }//重载<=运算符
	bool operator>=(RA_iterator& obj1) { return _ptr >= obj1._ptr; }//重载>=运算符
	bool operator>(RA_iterator& obj1) { return _ptr > obj1._ptr; }//重载>运算符
	bool operator<(RA_iterator& obj1) { return _ptr < obj1._ptr; }//重载<运算符
};

template<typename T>//重载++操作运算符
inline RA_iterator<T>& RA_iterator<T>::operator++()
{
	_ptr++;
	return *this;
}

template<typename T>
inline RA_iterator<T>& RA_iterator<T>::operator++(int)
{
	RA_iterator *temp = new RA_iterator(this->_ptr);
	_ptr++;
	return *temp;
}

template<typename T>//重载--操作运算符
inline RA_iterator<T>& RA_iterator<T>::operator--()
{
	_ptr--;
	return *this;
}

template<typename T>
inline RA_iterator<T>& RA_iterator<T>::operator--(int)
{
	RA_iterator* temp = new RA_iterator(this->_ptr);
	_ptr--;
	return *temp;
}

template<typename T>//重载=运算符
inline RA_iterator<T>& RA_iterator<T>::operator=(RA_iterator obj1)
{
	_ptr = obj1._ptr;
	return *this;
}


template<typename T>//重载+=运算符
inline RA_iterator<T>& RA_iterator<T>::operator+=(size_t i)
{
	_ptr = _ptr + i;
	return *this;
}

template<typename T>//重载-=运算符
inline RA_iterator<T>& RA_iterator<T>::operator-=(size_t i)
{
	_ptr = _ptr - i;
	return *this;
}

template<typename T>//重载+运算符
inline RA_iterator<T> RA_iterator<T>::operator+(size_t i)
{
	RA_iterator* temp = new RA_iterator(this->_ptr);
	temp->_ptr = _ptr + i;
	return *temp;
}

template<typename T>//重载-运算符
inline RA_iterator<T> RA_iterator<T>::operator-(size_t i)
{
	RA_iterator* temp = new RA_iterator(this->_ptr);
	temp->_ptr = _ptr - i;
	return *temp;
}


