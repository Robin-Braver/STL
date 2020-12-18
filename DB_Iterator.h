#pragma once
#include"stdafx.h"
#include"List.h"



template <typename T>
struct ListNode  //�������ඨ��
{
	T data; //����������
	ListNode<T>* next;
	ListNode<T>*prev; //ǰ�������ָ��
};


template<typename T>//List��˫����ʵ�����
class DB_Iterator
{
private:
	ListNode<T>*  _ptr;//��Ա��һ��ָ�������ָ��
public:
	DB_Iterator() :_ptr(NULL) {}
	DB_Iterator(ListNode<T>* obj):_ptr(obj) {}//���캯��
	DB_Iterator<T>(const DB_Iterator<T>& obj) { _ptr = obj._ptr; }//��������
	~DB_Iterator() { _ptr = NULL; }//��������
	

	ListNode<T>* getPtr() { return _ptr; }
	/*���������*/
	DB_Iterator<T>& operator++();//����ǰ��++���������
	DB_Iterator<T>& operator++(int);//���غ���++���������
	DB_Iterator<T>& operator--(); //����--���������
	DB_Iterator<T>& operator--(int);//���غ���--���������
	DB_Iterator<T>& operator=(const DB_Iterator<T>& obj1);//����=�����

	T& operator*() { return _ptr->data; }//����*�����,����ֵΪ��������ֹ�Լ������޸�

	bool operator==(DB_Iterator obj1) { return _ptr == obj1._ptr; };//����==�����
	bool operator!=(DB_Iterator obj1) { return _ptr != obj1._ptr; };//����!=�����
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
