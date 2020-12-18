#pragma once
#include"HashTable.h"

template<typename T>
class HS_iterator
{
private:
	HashTable<T>* t_ptr;//ָ����ָ��
	ChainNode<T>* n_ptr;//ָ��Ԫ��ָ��
public:
	HS_iterator() :t_ptr(NULL), n_ptr(NULL) {}//���캯��
	HS_iterator(HashTable<T>* T_ptr, ChainNode<T>* N_ptr) :t_ptr(T_ptr), n_ptr(N_ptr) {}//���캯��
	HS_iterator(const HS_iterator& obj)//��������
	{
		t_ptr = obj.t_ptr;
		n_ptr = obj.n_ptr;
	}
	~HS_iterator()//��������
	{
		if (t_ptr)
			t_ptr = NULL;
		if (n_ptr)
			n_ptr = NULL;
	}
	/*����������*/
	HS_iterator<T>& operator++();//����ǰ��++���������
	HS_iterator<T>& operator++(int);//���غ���++���������
	HS_iterator<T>& operator--();//����--���������
	HS_iterator<T>& operator--(int);//���غ���--���������
	HS_iterator<T>& operator=(HS_iterator<T> obj1);//����=�����

	const T& operator*() { return n_ptr->data; }//����*�����,����ֵΪ��������ֹ�Լ������޸�

	bool operator==(HS_iterator obj1) { return n_ptr == obj1.n_ptr; };//����==�����
	bool operator!=(HS_iterator obj1) { return n_ptr != obj1.n_ptr; };//����!=�����

};

template<typename T>
inline HS_iterator<T>& HS_iterator<T>::operator++()
{
	if (n_ptr->link != NULL)//��ǰָ��Ԫ�صĺ�̲��գ�ֱ�ӷ��غ��
	{
		n_ptr = n_ptr->link;
		return *this;
	}
	int key = t_ptr->Cal_Hash(n_ptr->data,t_ptr->divisor);//�����ȡ����λ�ã��ҵ���һ��λ��
	for (int i = key + 1; i < t_ptr->divisor; i++)//�ҵ���һ��Ͱ�ǿ�Ԫ��
		if (t_ptr->ht[i] != NULL)
		{
			n_ptr = t_ptr->ht[i];
			return *this;
		}
	n_ptr = NULL;
	return *this;//��ǰ�������һ��Ԫ��
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
	int key = t_ptr->Cal_Hash(n_ptr->data, t_ptr->divisor);//��ȡλ��
	if (t_ptr->ht[key] != n_ptr)//�������Ͱ��һ��Ԫ��
	{
		ChainNode<T>*pre = t_ptr->ht[key];
		while (pre->link != n_ptr)//��ֱ��ǰ��
			pre = pre->link;
		n_ptr = pre;
		return *this;
	}

	for(int i=key-1;i>=0;i--)//��ǰͰ�ǿ�Ԫ��
		if (t_ptr->ht[i] != n_ptr)
		{
			ChainNode<T>*pre = t_ptr->ht[i];
			while (pre->link!=NULL)//�����һ��Ԫ��
				pre = pre->link;
			n_ptr = pre;
			return *this;
		}
	n_ptr = NULL;
	return *this;//��ǰ���ǵ�һ��Ԫ��
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
