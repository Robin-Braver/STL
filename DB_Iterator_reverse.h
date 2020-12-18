#pragma once
#include"DB_Iterator.h"


template<typename T>//List��˫����ʵ�����
class rDB_Iterator
{
private:
	ListNode<T>* _ptr;//��Ա��һ��ָ�������ָ��
public:
	rDB_Iterator() :_ptr(NULL) {}
	rDB_Iterator(ListNode<T>* obj) :_ptr(obj) {}//���캯��
	rDB_Iterator<T>(const rDB_Iterator<T>& obj) { _ptr = obj._ptr; }//��������
	~rDB_Iterator() { _ptr = NULL; }//��������


	ListNode<T>* getPtr() { return _ptr; }
	/*���������*/
	rDB_Iterator<T>& operator++();//����ǰ��++���������
	rDB_Iterator<T>& operator++(int);//���غ���++���������
	rDB_Iterator<T>& operator--(); //����--���������
	rDB_Iterator<T>& operator--(int);//���غ���--���������
	rDB_Iterator<T>& operator=(const rDB_Iterator<T>& obj1);//����=�����

	T& operator*() { return _ptr->data; }//����*�����,����ֵΪ��������ֹ�Լ������޸�

	bool operator==(rDB_Iterator obj1) { return _ptr == obj1._ptr; };//����==�����
	bool operator!=(rDB_Iterator obj1) { return _ptr != obj1._ptr; };//����!=�����
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