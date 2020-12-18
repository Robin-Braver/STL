#pragma once
#include"stdafx.h"


/*������ʵ�����*/
template<typename T>
struct RA_iterator
{
	T* _ptr;//ָ��������Ԫ�ص�ָ��
	RA_iterator() :_ptr(NULL) {}//���캯��
	RA_iterator(T* ptr) :_ptr(ptr) {}//���캯��
	RA_iterator(const RA_iterator& obj)//��������
	{
		_ptr = obj._ptr;
	}
	~RA_iterator()//��������
	{
		if (_ptr)
			_ptr = NULL;
	}
	/*����������*/
	RA_iterator& operator++();//����ǰ��++���������
	RA_iterator& operator++(int);//���غ���++���������
	RA_iterator& operator--();//����--���������
	RA_iterator& operator--(int);//���غ���--���������
	RA_iterator& operator=(RA_iterator obj1);//����=�����
	RA_iterator& operator+=(size_t i);//����+=�����
	RA_iterator& operator-=(size_t i);//����-=�����
	RA_iterator operator+(size_t i);//����+�����
	RA_iterator operator-(size_t i);//����-�����

	size_t operator-(RA_iterator& obj1) { return (_ptr - obj1._ptr); }//����-�����,�����������

	T& operator[](size_t i)const { return _ptr[i]; };//����[]�����
	T& operator*() { return *_ptr; }//����*�����

	bool operator==(RA_iterator& obj1) { return _ptr == obj1._ptr; }//����==�����
	bool operator!=(RA_iterator obj1) { return _ptr != obj1._ptr; }//����!=�����
	bool operator<=(RA_iterator& obj1) { return _ptr <= obj1._ptr; }//����<=�����
	bool operator>=(RA_iterator& obj1) { return _ptr >= obj1._ptr; }//����>=�����
	bool operator>(RA_iterator& obj1) { return _ptr > obj1._ptr; }//����>�����
	bool operator<(RA_iterator& obj1) { return _ptr < obj1._ptr; }//����<�����
};

template<typename T>//����++���������
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

template<typename T>//����--���������
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

template<typename T>//����=�����
inline RA_iterator<T>& RA_iterator<T>::operator=(RA_iterator obj1)
{
	_ptr = obj1._ptr;
	return *this;
}


template<typename T>//����+=�����
inline RA_iterator<T>& RA_iterator<T>::operator+=(size_t i)
{
	_ptr = _ptr + i;
	return *this;
}

template<typename T>//����-=�����
inline RA_iterator<T>& RA_iterator<T>::operator-=(size_t i)
{
	_ptr = _ptr - i;
	return *this;
}

template<typename T>//����+�����
inline RA_iterator<T> RA_iterator<T>::operator+(size_t i)
{
	RA_iterator* temp = new RA_iterator(this->_ptr);
	temp->_ptr = _ptr + i;
	return *temp;
}

template<typename T>//����-�����
inline RA_iterator<T> RA_iterator<T>::operator-(size_t i)
{
	RA_iterator* temp = new RA_iterator(this->_ptr);
	temp->_ptr = _ptr - i;
	return *temp;
}


