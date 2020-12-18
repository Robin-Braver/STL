#pragma once
#include <assert.h>



template <typename K>
struct ChainNode
{ 
	//��Ͱ��ͬ����ӱ������㶨��
	K data;//Ԫ��
	ChainNode<K> *link; //��ָ��
	ChainNode() {}//Ĭ�Ϲ��캯��
	ChainNode(K e) :data(e),link(NULL) {}//���캯��
};

template <typename K>
class HashTable//ɢ�б�(��ͷָ������)����
{
	template<typename T>
	friend class HS_iterator;
	template<typename T>
	friend class Hash_Set;
public:
	HashTable(int d, int sz,int (*hash)(K num, int d));//ɢ�б�Ĺ��캯��
	~HashTable() { delete[] ht; }//��������

	bool Search(K e);//����
	bool Insert(K e);//����
	bool Remove(K e);//ɾ��
	
	ChainNode<K>* getfont();//���ص�һ��Ԫ��ָ��
	ChainNode<K>* getend();//�������һ��Ԫ��ָ��
	int GetNum() { return CurrentSize; }//��ȡ���Ԫ����Ŀ
private:
	int divisor;//������������������
	int TableSize;//����(Ͱ�ĸ���)
	int CurrentSize;//ʵ������
	ChainNode<K>** ht; //ɢ�б���
	ChainNode<K>* FindPos(K e);//ɢ��
	//int Cal_Hash(K num);//����Ԫ�ص�keyֵ
	int (*Cal_Hash)(K num,int d);//����Ԫ�ص�keyֵ
};

template <typename K>//���캯��
HashTable<K>::HashTable(int d, int sz, int (*hash)(K num, int d))
{
	if (d > sz)//���������Դ���Ͱ��
		return;
	divisor = d; 
	TableSize= sz;
	CurrentSize = 0;
	Cal_Hash = hash;
	ht=new ChainNode<K>* [sz];//����ͷ���
	for (int i = 0; i < sz; i++)
		ht[i] = NULL;
	assert (ht!= NULL);//�жϴ洢����ɹ���
}

template<typename K>
bool HashTable<K>::Search(K e)
{
	ChainNode<K>* p = FindPos(e);//���Ҵ�Ԫ���Ƿ����
	if (p == NULL)//�Ѿ�����
		return false;
	else
		return true;
}

template<typename K>
bool HashTable<K>::Insert(K e)
{
	int j = Cal_Hash(e,divisor);//����ɢ�е�ַ
	ChainNode<K>* node = new ChainNode<K>(e);//�������
	ChainNode<K>* pre_p = ht[j];//���������㣬ָ��������ֱ��ǰ��
	if (pre_p == NULL)//��������ֱ���ǿ�������ֱ�Ӳ���
	{
		ht[j] = node;
		node = NULL;
		CurrentSize++;
		return true;
	}

	ChainNode<K>* p = FindPos(e);//���Ҵ�Ԫ���Ƿ����
	if (p != NULL)//�Ѿ�����
		return false;

	while (pre_p->link!=NULL&&e>pre_p->link->data)//ͨ��FindPos�Ѿ��ҵ�����λ��,Ȼ��λp��ֱ��ǰ��
		pre_p = pre_p->link;
	if (pre_p == ht[j]&&pre_p->data>e)//����ֻ��һ��Ԫ�أ��Ҳ����Ԫ��С���Ѿ����ڵ�Ԫ��
	{
		node->link = ht[j];
		ht[j] = node;
		CurrentSize++;
		return true;
	}
	ChainNode<K>* temp = pre_p->link;
	pre_p->link = node; 
	node->link = temp;
	CurrentSize++;
	return true;
}

template<typename K>
bool HashTable<K>::Remove(K e)
{
	ChainNode<K>* p = FindPos(e);//���Ҵ�Ԫ���Ƿ����
	if (p == NULL)//Ԫ�ز�����
		return false;
	int j = Cal_Hash(e,divisor);//����ɢ�е�ַ
	ChainNode<K>* pre_p = ht[j];//����ɾ����㣬ָ��ɾ������ֱ��ǰ��
	if (p == ht[j])//ɾ�������׽��
	{
		ht[j] = p->link;
		CurrentSize--;
		return true;
	}
	while (pre_p->link != p)//ͨ��FindPos�Ѿ��ҵ�����λ��,Ȼ��λp��ֱ��ǰ��
		pre_p = pre_p->link;
	pre_p->link = p->link;//ɾ�����
	p->link = NULL;
	CurrentSize--;
	return true;
}

template<typename K>
inline ChainNode<K>* HashTable<K>::getfont()
{
	ChainNode<K>* result = new ChainNode<K>();
	int i = 0;
	while (i<TableSize&&ht[i]==NULL)//�ҷǿյ�Ԫ��
	{
		i++;
	}
	result = ht[i];
	return result;
}

template<typename K>
inline ChainNode<K>* HashTable<K>::getend()
{
	ChainNode<K>* result = new ChainNode<K>();
	int i = TableSize-1;
	while (i >=0 && ht[i] == NULL)//�ҷǿյ�Ԫ��
	{
		i--;
	}
	result = ht[i];
	while (result->link!=NULL)//�����һ��Ͱ���һ����
	{
		result = result->link;
	}
	return result;
}

template <typename K>
ChainNode<K>* HashTable<K>::FindPos(K e)
{
	//��ɢ�б�ht�������ؼ���Ϊk��Ԫ�ء���������һ��ָ��ɢ�б���ĳλ�õ�ָ��
	int j = Cal_Hash(e,divisor);//����ɢ�е�ַ
	ChainNode<K> *p = ht[j];//ɨ���j����ͬ����ӱ�
	while (p != NULL&& p->data != e) 
		p = p->link;
	return p;//����
}




