#pragma once
#include"stdafx.h"

/*����������ʵ�����*/
template<typename T>
struct rRA_iterator
{
	T* _ptr;//ָ��������Ԫ�ص�ָ��
	rRA_iterator() :_ptr(NULL) {}//���캯��
	rRA_iterator(T* ptr) :_ptr(ptr) {}//���캯��
	rRA_iterator(const rRA_iterator& obj)//��������
	{
		_ptr = obj._ptr;
	}
	~rRA_iterator()//��������
	{
		if (_ptr)
			_ptr = NULL;
	}
	/*����������*/
	rRA_iterator& operator++();//����ǰ��++���������
	rRA_iterator& operator++(int);//���غ���++���������
	rRA_iterator& operator--();//����--���������
	rRA_iterator& operator--(int);//���غ���--���������
	rRA_iterator& operator=(rRA_iterator obj1);//����=�����
	rRA_iterator& operator+=(size_t i);//����+=�����
	rRA_iterator& operator-=(size_t i);//����-=�����
	rRA_iterator operator+(size_t i);//����+�����
	rRA_iterator operator-(size_t i);//����-�����

	size_t operator-(rRA_iterator& obj1) { return (_ptr - obj1._ptr); }//����-�����,�����������

	T& operator[](size_t i)const { return *(_ptr-i); };//����[]�����
	T& operator*() { return *_ptr; }//����*�����

	bool operator==(rRA_iterator& obj1) { return _ptr == obj1._ptr; }//����==�����
	bool operator!=(rRA_iterator obj1) { return _ptr != obj1._ptr; }//����!=�����
	bool operator<=(rRA_iterator& obj1) { return !(_ptr < obj1._ptr); }//����<=�����
	bool operator>=(rRA_iterator& obj1) { return !(_ptr > obj1._ptr); }//����>=�����
	bool operator>(rRA_iterator& obj1) { return !(_ptr >= obj1._ptr); }//����>�����
	bool operator<(rRA_iterator& obj1) { return !(_ptr <= obj1._ptr); }//����<�����
};

template<typename T>//����++���������
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

template<typename T>//����--���������
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

template<typename T>//����=�����
inline rRA_iterator<T>& rRA_iterator<T>::operator=(rRA_iterator obj1)
{
	_ptr = obj1._ptr;
	return *this;
}


template<typename T>//����+=�����
inline rRA_iterator<T>& rRA_iterator<T>::operator+=(size_t i)
{
	_ptr = _ptr - i;
	return *this;
}

template<typename T>//����-=�����
inline rRA_iterator<T>& rRA_iterator<T>::operator-=(size_t i)
{
	_ptr = _ptr + i;
	return *this;
}

template<typename T>//����+�����
inline rRA_iterator<T> rRA_iterator<T>::operator+(size_t i)
{
	rRA_iterator* temp = new rRA_iterator(this->_ptr);
	temp->_ptr = _ptr - i;
	return *temp;
}

template<typename T>//����-�����
inline rRA_iterator<T> rRA_iterator<T>::operator-(size_t i)
{
	rRA_iterator* temp = new rRA_iterator(this->_ptr);
	temp->_ptr = _ptr + i;
	return *temp;
}
