#pragma once
#include"HashSet_Iterator.h"

template<typename K>//针对float、double、int型
int Cal_Hash_int(K num, int divisor)
{

	int hash = int(num) % divisor;
	return hash;
}


template<typename E>
class Hash_Set
{
public:
	Hash_Set(int div, int sz, int (*hash) (E elem,int d)= Cal_Hash_int);
	
	HS_iterator<E> Begin();
	HS_iterator<E> End();

	int GetNum() { return ht->GetNum(); }//获取集合元素个数
	bool Find(E elem) { return ht->Search(elem); }//查找元素
	bool Insert(E elem) {return ht->Insert(elem);}//插入元素
	void Insert(HS_iterator<E> first, HS_iterator<E> last);//将区间 [first, last) 中的元素插人容器
	bool Remove(E elem) { return ht->Remove(elem); }//删除元素
	HS_iterator<E> erase(HS_iterator<E> it);//删除 it 指向的元素，返回其后面的元素的迭代器
	HS_iterator<E> erase(HS_iterator<E> first, HS_iterator<E> last); //删除区间[first, last)，返回 last
	
	HS_iterator<E> lower_bound(const E& val);//查找一个最大的位置 it，使得 [begin(), it) 中所有的元素者比 val 小
	HS_iterator<E> upper_bound(const E& val); //查找一个最小的位置 it，使得[it, end()] 中所有的元素都比 val 大
	pair <HS_iterator<E>, HS_iterator<E> >equal_range(const E& val); //同时求得 lower_bound 和 upper_bound

	void show();//输出集合
private:
	HashTable<E>*ht;//指向底层存储的hash表
};

template<typename E>
inline Hash_Set<E>::Hash_Set(int div, int sz, int (*hash) (E elem, int d))
{	
	ht = new HashTable<E>(div, sz, (*hash));//创建一个hash表
}

template<typename E>
inline HS_iterator<E> Hash_Set<E>::Begin()
{
	HS_iterator<E> *result = new HS_iterator<E>(ht, ht->getfont());
	return *result;
}

template<typename E>
inline HS_iterator<E> Hash_Set<E>::End()
{
	HS_iterator<E>* result = new HS_iterator<E>(ht, ht->getend());
	return *result;
}

template<typename E>
void Hash_Set<E>::Insert(HS_iterator<E> first, HS_iterator<E> last)
{
	for (auto temp = first; temp != last; ++temp)
	{
		E value = *temp;
		ht->Insert(value);
	}
}

template<typename E>
HS_iterator<E> Hash_Set<E>::erase(HS_iterator<E> it)
{
	auto result = ++it;
	E val = *it;
	ht->Remove(val);
	return result;
}

template<typename E>
HS_iterator<E> Hash_Set<E>::erase(HS_iterator<E> first, HS_iterator<E> last)
{
	auto temp = first;
	while (temp != last)
	{
		E val = *temp;
		ht->Remove(val);
		temp++;
	}
	return last;
}

template<typename E>
HS_iterator<E> Hash_Set<E>::lower_bound(const E& val)
{
	auto result = this->Begin();
	while (result != this->End())
	{
		if (*result < val)
			result++;
		else
			break;
	}
	return result;
}

template<typename E>
HS_iterator<E> Hash_Set<E>::upper_bound(const E& val)
{
	auto result = this->End();
	while (result != this->Begin())
	{
		if (*result >val)
			result--;
		else
			break;
	}
	return ++result;
}

template<typename E>
inline pair<HS_iterator<E>, HS_iterator<E>> Hash_Set<E>::equal_range(const E& val)
{
	auto result1 = this->lower_bound(val);
	auto result2 = this->upper_bound(val);
	pair< HS_iterator<E>, HS_iterator<E>>result(result1, result2);
	return result;
}

template<typename E>
void Hash_Set<E>::show()
{
	cout << "Set最大桶数：" << ht->TableSize << ",除数：" << ht->divisor << ",当前实际数目：" << ht->CurrentSize << ",具体数据：" << endl;
	for (int i = 0; i < ht->TableSize; ++i)
	{
		cout<< "桶" << left << setw(2) << i << "：  ";
		ChainNode<E>* j = ht->ht[i];
		while (j != NULL)
		{
			cout << setw(2) << j->data << "  ";
			j = j->link;
		}
		cout << endl;
	}
	
}
