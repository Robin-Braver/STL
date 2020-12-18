#pragma once
#include <assert.h>



template <typename K>
struct ChainNode
{ 
	//各桶中同义词子表的链结点定义
	K data;//元素
	ChainNode<K> *link; //链指针
	ChainNode() {}//默认构造函数
	ChainNode(K e) :data(e),link(NULL) {}//构造函数
};

template <typename K>
class HashTable//散列表(表头指针向量)定义
{
	template<typename T>
	friend class HS_iterator;
	template<typename T>
	friend class Hash_Set;
public:
	HashTable(int d, int sz,int (*hash)(K num, int d));//散列表的构造函数
	~HashTable() { delete[] ht; }//析构函数

	bool Search(K e);//搜索
	bool Insert(K e);//插入
	bool Remove(K e);//删除
	
	ChainNode<K>* getfont();//返回第一个元素指针
	ChainNode<K>* getend();//返回最后一个元素指针
	int GetNum() { return CurrentSize; }//获取存放元素数目
private:
	int divisor;//除数（必须是质数）
	int TableSize;//容量(桶的个数)
	int CurrentSize;//实际数量
	ChainNode<K>** ht; //散列表定义
	ChainNode<K>* FindPos(K e);//散列
	//int Cal_Hash(K num);//计算元素的key值
	int (*Cal_Hash)(K num,int d);//计算元素的key值
};

template <typename K>//构造函数
HashTable<K>::HashTable(int d, int sz, int (*hash)(K num, int d))
{
	if (d > sz)//除数不可以大于桶数
		return;
	divisor = d; 
	TableSize= sz;
	CurrentSize = 0;
	Cal_Hash = hash;
	ht=new ChainNode<K>* [sz];//创建头结点
	for (int i = 0; i < sz; i++)
		ht[i] = NULL;
	assert (ht!= NULL);//判断存储分配成功否
}

template<typename K>
bool HashTable<K>::Search(K e)
{
	ChainNode<K>* p = FindPos(e);//查找此元素是否存在
	if (p == NULL)//已经存在
		return false;
	else
		return true;
}

template<typename K>
bool HashTable<K>::Insert(K e)
{
	int j = Cal_Hash(e,divisor);//计算散列地址
	ChainNode<K>* node = new ChainNode<K>(e);//创建结点
	ChainNode<K>* pre_p = ht[j];//辅助插入结点，指向插入结点的直接前驱
	if (pre_p == NULL)//如果这个链直接是空链，则直接插入
	{
		ht[j] = node;
		node = NULL;
		CurrentSize++;
		return true;
	}

	ChainNode<K>* p = FindPos(e);//查找此元素是否存在
	if (p != NULL)//已经存在
		return false;

	while (pre_p->link!=NULL&&e>pre_p->link->data)//通过FindPos已经找到插入位置,然后定位p的直接前驱
		pre_p = pre_p->link;
	if (pre_p == ht[j]&&pre_p->data>e)//该链只有一个元素，且插入的元素小于已经存在的元素
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
	ChainNode<K>* p = FindPos(e);//查找此元素是否存在
	if (p == NULL)//元素不存在
		return false;
	int j = Cal_Hash(e,divisor);//计算散列地址
	ChainNode<K>* pre_p = ht[j];//辅助删除结点，指向删除结点的直接前驱
	if (p == ht[j])//删除的是首结点
	{
		ht[j] = p->link;
		CurrentSize--;
		return true;
	}
	while (pre_p->link != p)//通过FindPos已经找到插入位置,然后定位p的直接前驱
		pre_p = pre_p->link;
	pre_p->link = p->link;//删除结点
	p->link = NULL;
	CurrentSize--;
	return true;
}

template<typename K>
inline ChainNode<K>* HashTable<K>::getfont()
{
	ChainNode<K>* result = new ChainNode<K>();
	int i = 0;
	while (i<TableSize&&ht[i]==NULL)//找非空的元素
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
	while (i >=0 && ht[i] == NULL)//找非空的元素
	{
		i--;
	}
	result = ht[i];
	while (result->link!=NULL)//找最后一个桶最后一条链
	{
		result = result->link;
	}
	return result;
}

template <typename K>
ChainNode<K>* HashTable<K>::FindPos(K e)
{
	//在散列表ht中搜索关键码为k的元素。函数返回一个指向散列表中某位置的指针
	int j = Cal_Hash(e,divisor);//计算散列地址
	ChainNode<K> *p = ht[j];//扫描第j链的同义词子表
	while (p != NULL&& p->data != e) 
		p = p->link;
	return p;//返回
}




