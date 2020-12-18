#pragma once
#include"DB_Iterator.h"
#include"DB_Iterator_reverse.h"


/*有头尾两个空节点不存信息，目的在于统一操作，不同区分真的头结点和尾结点*/
template <class T>
class List { //链表类定义
public:
	List();//默认构造
	List(size_t size, const T val);//使用size个T初始化链表
	List(const List&Ln);//拷贝构造函数
	~List();//析构函数

	
	bool IsEmpty() { return (length==0); }//判双链表空否
	int getLength() { return length; }//获取表长
	void setLength(int l) { length = l; }//设置表长
	ListNode<T>* getHead() { return head; }//获取头结点指针
	ListNode<T>* getTail() { return tail; }//获取尾结点指针
	DB_Iterator<T> begin();//获取头迭代器
	DB_Iterator<T> end();//获取尾迭代器
	rDB_Iterator<T> rbegin();//获取头迭代器
	rDB_Iterator<T> rend();//获取尾迭代器

	void Sort();//升序排序
	T find(int index);//查找第index个元素
	int find_index(const T& val);//查找值并返回其位置
	void push_front(const T& val);//将 val 插入链表最前面
	void insert(const T& val);//尾插，插在末端
	void splice(DB_Iterator<T> i, List <T>& x, DB_Iterator<T> first, DB_Iterator<T> last);
	//在位置 i 前面插入链表 x 中的区间 [first, last)，并在链表 x 中删除该区间。链表自身和链表 x 可以是同一个链表，只要 i 不在 [first, last) 中即可
	void merge(List<T>& x);//将链表 x 合并进来并清空 x。要求链表自身和 x 都是有序的	
	void pop_front(); //删除链表最前面的元素
	void unique();//删除所有和前一个元素等值元素
	void Remove(const T& val); //删除和val等值元素
	void clear();//删除所有结点

	void showList(string s = "list");//输出链表的值

private:
	ListNode<T>* head; //表头指针
	ListNode<T>* tail;//表尾指针
	int length;//表长
};

template<class T>
inline List<T>::List()
{
	head = new ListNode<T>;
	tail = new ListNode<T>;
	head->next = tail;//将头尾连接
	head->prev = NULL;//前指针前为空
	tail->next = NULL;//尾指针后面为空
	tail->prev = head;//头尾连接
	length = 0;
}

template<class T>
List<T>::List(size_t size, const T val)
{
	head = new ListNode<T>;
	tail = new ListNode<T>;
	head->next = tail;//将头尾连接
	head->prev = NULL;//前指针前为空
	tail->next = NULL;//尾指针后面为空
	tail->prev = head;//头尾连接
	length = 0;
	while (length < size)//循环插入
		this->insert(val);
}

template<class T>
List<T>::List(const List& Ln)
{
	head = new ListNode<T>;
	head->prev = NULL;
	tail = new ListNode<T>;
	head->next = tail;
	tail->prev = head;
	length = 0;
	ListNode<T>* temp = Ln.head;
	while (temp->next != Ln.tail)//遍历原链表
	{
		temp = temp->next;
		tail->data = temp->data;
		ListNode<T>* p = new ListNode<T>;//生成新结点
		p->prev = tail;//新节点和原来的尾部连接；
		tail->next = p;
		tail = p;//将尾部指针指向新结点
		length++;
	}
	tail->next = NULL;
}

template<class T>
List<T>::~List()
{
	if (length == 0)
	{
		delete head, tail;
		head = tail = NULL;
		return;
	}
	while (head->next!=NULL)
	{
		ListNode<T>* temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
	head = NULL;
}

template<class T>
inline DB_Iterator<T> List<T>::begin()
{
	DB_Iterator<T>* result = new DB_Iterator<T>(head->next);//由于头结点没有使用，故需要后移一个结点
	return (*result);
}

template<class T>
inline DB_Iterator<T> List<T>::end()
{
	DB_Iterator<T>* result = new DB_Iterator<T>(tail);
	return *result;
}

template<class T>
inline rDB_Iterator<T> List<T>::rbegin()
{
	rDB_Iterator<T>* result = new rDB_Iterator<T>(tail->prev);//尾结点没用，前移一个
	return (*result);
}

template<class T>
inline rDB_Iterator<T> List<T>::rend()
{
	rDB_Iterator<T>* result = new rDB_Iterator<T>(head);
	return *result;
}

template<class T>
void List<T>::Sort()
{
	if (length <= 1)return;
	ListNode<T>* current = head->next;
	for (int i = 0; i < length - 1; ++i)//两重循环排序
	{
		ListNode<T>* q = current->next;
		for (int j = i + 1; j < length; ++j)
		{
			if (current->data > q->data)//当前大于后一个
			{
				T temp = q->data;
				q->data = current->data;
				current->data = temp;
			}
			q = q->next;
		}
		current = current->next;
	}
}

template<class T>
T List<T>::find(int index)
{
	if (length == 0)return NULL;//为空
	if (index > length&&index<0)return NULL;//下标不符合
	
	T data;
	ListNode<T>* p;
	int x;
	if (index < length / 2);//下标小于一半则从前查找
	{
		x = 0;
		p = head->next;
		while (p->next!=NULL&&(x++!=index))
			p = p->next;
	}
	if(index>=length/2)//大于一半就从后
	{
		x = length-1;
		p = tail->prev;
		while (p->prev != NULL && x-- != index)
			p = p->prev;
	}
	return p->data;
}

template<class T>
int List<T>::find_index(const T& val)
{
	int index = 0;
	ListNode<T>* current = head->next;//遍历指针
	while (current->next != NULL && current->data != val)
	{
		index++;
		current = current->next;
	}
	return index;//如果返回的长度的下标，则代表不存在
}

template<class T>
void List<T>::push_front(const T& val)
{
	ListNode<T>* new_Node = new ListNode<T>;//新的插入结点
	new_Node->data = val;
	new_Node->next = head->next;
	head->next = new_Node;
	new_Node->prev = head;
	new_Node->next->prev = new_Node;
	length++;
}

template<class T>
inline void List<T>::insert(const T& val)
{
	ListNode<T>* temp = this->tail;//记录下原尾结点
	tail->data = val;
	tail->next = new ListNode<T>;//尾结点连接新的尾结点
	tail = tail->next;//更新尾结点
	tail->prev = temp;
	tail->next = NULL;
	length++;
}

template<class T>
void List<T>::splice(DB_Iterator<T> i, List<T>& x, DB_Iterator<T> first, DB_Iterator<T> last)
{
	//基本思想：将目的链表那一段截取下来插入到当前链表中
	//获取新增个数
	int l = 0;
	for (auto i = first; i != last; ++i)
		++l;

	ListNode<T>* current = i.getPtr();//获取插入位置指针
	ListNode<T>* pre = current->prev;//获取前驱
	//截取目的链表，
	ListNode<T>* start = first.getPtr();//截取起点
	ListNode<T>* end = last.getPtr()->prev;//截取终点
	ListNode<T>* x_pre =start->prev;//起点前驱
	//从原始链表摘下链表段
	x_pre->next = end->next;
	end->next->prev = x_pre;
	//摘下的表段插入到当前链表中
	pre->next = start;
	start->prev = pre;
	end->next = current;
	current->prev = end;
	length += l;
	x.setLength(x.getLength() - l);
}

template<class T>
void List<T>::merge(List<T>& x)
{
	if (x.getLength() == 0)return;
	ListNode<T>* current1 = head->next;//指向当前表的第一个节点
	ListNode<T>* current2 = x.getHead()->next;//指向被合并表的第一个元素
	while (current2!=x.getTail()&&current1!=tail)//遍历被合并的链表,或者当前表
	{
		if (current1->data > current2->data)//被合并表元素更小，故插入进来
		{
			ListNode<T>* p = current1->prev;
			ListNode<T>* NewNode = new ListNode<T>;
			NewNode->data = current2->data;
			p->next = NewNode;
			NewNode->prev = p;
			NewNode->next = current1;
			current1->prev = NewNode;
			length++;
			current2 = current2->next;//被合并表指针后移
		}
		else
			current1 = current1->next;
	}
	if (current1 == tail)//被合并表剩余元素均大于链表元素
	{
		while (current2!=x.getTail())
		{
			this->insert(current2->data);//依次插入就可以
			current2 = current2->next;
		}
	}
	x.clear();
}

template<class T>
void List<T>::pop_front()
{
	if (length < 1)return;
	ListNode<T>* del_Node = head->next;//找到被删结点
	head->next = del_Node->next;
	del_Node->next->prev = head;
	length--;
	delete del_Node;

}

template<class T>
void List<T>::unique()
{
	if (length <= 1)return;
	ListNode<T>* p = head->next;//前驱结点
	ListNode<T>* current = p->next;//当前结点
	while (current != tail)
	{
		if (p->data == current->data)
		{
			ListNode<T>* temp = current;//记录被删除的当前结点
			p->next = current->next;
			current->next->prev = p;
			delete temp;
			current = p->next;
			length--;
		}
		else 
		{
			current = current->next;
			p = p->next;
		}
	}
}

template<class T>
void List<T>::Remove(const T& val)
{
	if (length == 0)return;
	ListNode<T>* current = head;
	while (current->next!=NULL)
	{
		current = current->next;
		if (current->data == val)//找到与之相等的值
		{
			ListNode<T>* temp = current->prev;//获取当前删除节点的前驱
			temp->next = current->next;
			current->next->prev = temp;
			delete current;
			length--;
			return;		
		}
	}
}

template<class T>
void List<T>::clear()
{
	if (length == 0)return;
	ListNode<T>* current = head->next;
	while (current!=tail)
	{
		ListNode<T>* temp = current;
		current = current->next;
		delete temp;
	}
	head->next = tail;
	tail->prev = head;
	length = 0;
}

template<class T>
void List<T>::showList(string s)
{
	if (length == 0)
	{
		cout <<s<< "为空" << endl;
		return;
	}
	ListNode<T>* current = head->next;
	cout <<s<< "长度为:" << length << ",其数值如下：" << endl;
	while (current!=tail)
	{
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}
