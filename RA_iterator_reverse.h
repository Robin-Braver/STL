#pragma once
#include"stdafx.h"

/*反向随机访问迭代器*/
template<typename T>
struct rRA_iterator
{
	T* _ptr;//指向容器中元素的指针
	rRA_iterator() :_ptr(NULL) {}//构造函数
	rRA_iterator(T* ptr) :_ptr(ptr) {}//构造函数
	rRA_iterator(const rRA_iterator& obj)//拷贝构造
	{
		_ptr = obj._ptr;
	}
	~rRA_iterator()//析构函数
	{
		if (_ptr)
			_ptr = NULL;
	}
	/*操作符重载*/
	rRA_iterator& operator++();//重载前置++操作运算符
	rRA_iterator& operator++(int);//重载后置++操作运算符
	rRA_iterator& operator--();//重载--操作运算符
	rRA_iterator& operator--(int);//重载后置--操作运算符
	rRA_iterator& operator=(rRA_iterator obj1);//重载=运算符
	rRA_iterator& operator+=(size_t i);//重载+=运算符
	rRA_iterator& operator-=(size_t i);//重载-=运算符
	rRA_iterator operator+(size_t i);//重载+运算符
	rRA_iterator operator-(size_t i);//重载-运算符

	size_t operator-(rRA_iterator& obj1) { return (_ptr - obj1._ptr); }//重载-运算符,两迭代器相减

	T& operator[](size_t i)const { return *(_ptr-i); };//重载[]运算符
	T& operator*() { return *_ptr; }//重载*运算符

	bool operator==(rRA_iterator& obj1) { return _ptr == obj1._ptr; }//重载==运算符
	bool operator!=(rRA_iterator obj1) { return _ptr != obj1._ptr; }//重载!=运算符
	bool operator<=(rRA_iterator& obj1) { return !(_ptr < obj1._ptr); }//重载<=运算符
	bool operator>=(rRA_iterator& obj1) { return !(_ptr > obj1._ptr); }//重载>=运算符
	bool operator>(rRA_iterator& obj1) { return !(_ptr >= obj1._ptr); }//重载>运算符
	bool operator<(rRA_iterator& obj1) { return !(_ptr <= obj1._ptr); }//重载<运算符
};

template<typename T>//重载++操作运算符
inline rRA_iterator<T>& rRA_iterator<T>::operator++()
{
	_ptr--;
	return *this;
}

template<typename T>
inline rRA_iterator<T>& rRA_iterator<T>::operator++(int)
{
	rRA_iterator* temp = new rRA_iterator(this->_ptr);
	_ptr--;
	return *temp;
}

template<typename T>//重载--操作运算符
inline rRA_iterator<T>& rRA_iterator<T>::operator--()
{
	_ptr++;
	return *this;
}

template<typename T>
inline rRA_iterator<T>& rRA_iterator<T>::operator--(int)
{
	rRA_iterator* temp = new rRA_iterator(this->_ptr);
	_ptr++;
	return *temp;
}

template<typename T>//重载=运算符
inline rRA_iterator<T>& rRA_iterator<T>::operator=(rRA_iterator obj1)
{
	_ptr = obj1._ptr;
	return *this;
}


template<typename T>//重载+=运算符
inline rRA_iterator<T>& rRA_iterator<T>::operator+=(size_t i)
{
	_ptr = _ptr - i;
	return *this;
}

template<typename T>//重载-=运算符
inline rRA_iterator<T>& rRA_iterator<T>::operator-=(size_t i)
{
	_ptr = _ptr + i;
	return *this;
}

template<typename T>//重载+运算符
inline rRA_iterator<T> rRA_iterator<T>::operator+(size_t i)
{
	rRA_iterator* temp = new rRA_iterator(this->_ptr);
	temp->_ptr = _ptr - i;
	return *temp;
}

template<typename T>//重载-运算符
inline rRA_iterator<T> rRA_iterator<T>::operator-(size_t i)
{
	rRA_iterator* temp = new rRA_iterator(this->_ptr);
	temp->_ptr = _ptr + i;
	return *temp;
}
