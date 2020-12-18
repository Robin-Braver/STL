#pragma once
#include"RA_iterator.h"
#include"RA_iterator_reverse.h"


template <typename T>
class Vector
{
private:
    RA_iterator<T> begin;
    RA_iterator<T> end;
    size_t size = 0;
public:
    Vector() : begin(nullptr), end(nullptr), size(0) {} //构造函数
    Vector(size_t nsize);//给定元素个数创建数组
    Vector(size_t nsize, T obj); //给定元素的个数和元素的初始值创建数组
    Vector(const Vector& obj); //拷贝构造
    Vector(RA_iterator<T>star, RA_iterator<T>finish);//通过迭代器构造
    ~Vector(); //析构函数

    RA_iterator<T> Begin() { return begin; }//获取头迭代器
    RA_iterator<T> End() { return end; }//获取尾迭代器
    rRA_iterator<T> rBegin() { return *(new rRA_iterator<T>(end._ptr-1)); }//获取反向头迭代器
    rRA_iterator<T> rEnd() { return *(new rRA_iterator<T>(begin._ptr-1)); }//获取反向尾迭代器
    size_t getsize() const { return size; }//返回数组中元素的个数
    T& front() { return *begin; }//获取首元素引用
    T& back() { auto temp = end ; return *(temp-1); }//获取尾元素引用
    bool empty() { return size == 0 ? true : false; }//判断数组是否为空

    T& operator [](size_t i) const; //重载运算符[],返回值为左值引用
    Vector& operator = (Vector& obj);//赋值拷贝
    T At(size_t i) const;//获取数组中第N个元素的值
    bool Find(T x);//查找某个元素

    void push_back(const T& elem);//在末尾增加一个元素
    RA_iterator<T> insert(RA_iterator<T> i, const T& val);//将 val 插入迭代器 i 指向的位置，返回 i
    RA_iterator<T> insert(RA_iterator<T> i, RA_iterator<T> first, RA_iterator<T> last); //将其他容器上的区间[first, last) 中的元素插入迭代器 i 指向的位置
    RA_iterator<T> erase(RA_iterator<T> i);//删除迭代器 i 指向的元素，返回值是被删元素后面的元素的迭代器
    RA_iterator<T> erase(RA_iterator<T> first, RA_iterator<T> last);//删除容器中的区间 [first, last)

    void pop_back();//删除末尾元素
    void MakeEmpty(); //删除所有元素
    void swap(Vector <T>& v);//将容器自身的内容和另一个同类型的容器 v 互换
    bool reset(size_t nsize);//函数重载：重置数组个数  
    void reset(size_t nsize, T obj);//函数重载：重置对象个数，并给定所有元素的初始值
    void show(string s="vector");//展示vector
};

template<typename T>//给定元素个数创建数组
Vector<T>::Vector(size_t nsize)
{
    if (nsize > 0)
    {
        T *temp = new T[nsize]; 
        size = nsize;
        T * temp2 =temp + size;
        begin = *(new RA_iterator<T>(temp));
        end = *(new RA_iterator<T>(temp2));
        temp = temp2 = NULL;
    }
}

template<typename T>//给定元素的个数和元素的初始值创建数组
Vector<T>::Vector(size_t nsize, T obj)
{
    if (nsize > 0)
    {
        T* temp = new T[nsize];
        size = nsize;
        T* temp2 = temp + size;
        begin = *(new RA_iterator<T>(temp));
        end = *(new RA_iterator<T>(temp2));
        for (size_t i = 0; i < nsize; ++i) { temp[i] = obj; }
        temp = temp2 = NULL;
    }
}

template<typename T>//拷贝构造
Vector<T>::Vector(const Vector& obj)
{
    //开辟新的空间用来存放
    T *temp = new T[obj.getsize()];
    //拷贝原有数据到新的空间
    for (int i = 0; i < obj.getsize(); ++i)
        temp[i] = obj[i];
    size = obj.getsize();
    T* temp2 = temp + size;
    begin = *(new RA_iterator<T>(temp));
    end = *(new RA_iterator<T>(temp2));
    temp = temp2 = NULL;
}

template<typename T>
Vector<T>::Vector(RA_iterator<T> star, RA_iterator<T> finish)
{
    size = finish-star;
    if (begin._ptr)
        delete []begin._ptr;
    T* temp = new T[size];
    for (size_t i = 0; i < size; i++)
        temp[i] =star[i];
    T* temp2 = temp + size;
    begin = *(new RA_iterator<T>(temp));
    end = *(new RA_iterator<T>(temp2));
    temp = temp2 = NULL;
}
 
template<typename T>//析构函数
Vector<T>::~Vector()
{
    if (begin._ptr)
    {
        delete []begin._ptr;
        begin._ptr = nullptr;
        size = 0;
        end = begin;
    }
}


template<typename T>
T Vector<T>::At(size_t i) const
{
    if (begin._ptr != nullptr && i >= 0 && i < size)
    {
        return begin[i];
    }
}


template<typename T>//重载运算符[],返回值为左值引用
T& Vector<T>::operator [](size_t i) const
{
    if (begin._ptr != nullptr && i >= 0 && i < size)
    {
        return begin[i];
    }
}

template<typename T>//赋值拷贝
Vector<T>& Vector<T>::operator= (Vector<T>& obj)
{
    if (begin== obj.begin) { return *this; }
    if (obj.begin._ptr == nullptr)
    {
        if (begin._ptr) { begin = nullptr; size = 0; end = begin; }
        return *this;
    }
    if (begin._ptr) {
        //清除原有数组
        delete[] begin._ptr; begin = nullptr; end = begin;
    }
    T* temp = new T[obj.getsize()];
    //拷贝原有数据到新的空间
    for (int i = 0; i < obj.getsize(); ++i)
        temp[i] = obj[i];
    size = obj.getsize();
    T* temp2 = temp + size;
    begin = *(new RA_iterator<T>(temp));
    end = *(new RA_iterator<T>(temp2));
    temp = temp2 = NULL;
    return *this;
}

template<typename T>//在末尾增加一个元素
void Vector<T>::push_back(const T& elem)
{
    T* ptmp = nullptr;
    if (begin._ptr)
    {
        ptmp = new T[size + 1];
        for (size_t i = 0; i < size; i++)
        {
            ptmp[i] = begin[i];
        }
        delete[] begin._ptr; 
    }
    else
    {
        ptmp = new T[1];
    }
    ptmp[size] = elem;
    ++size;
    T *ptmp2 = ptmp + size;
    begin = *(new RA_iterator<T>(ptmp));
    end = *(new RA_iterator<T>(ptmp2));
}

template<typename T>
RA_iterator<T> Vector<T>::insert(RA_iterator<T> i, const T& val)
{
    T* ptmp = nullptr; 
    int result=-1;
    if (begin._ptr)
    {
        int index = 0;
        auto temp = begin;//获取头迭代器
        ptmp = new T[++size];
        while (temp!=end)
        {
            if (temp == i&&result==-1)//result是控制一旦插入就直接拷贝
            {
                ptmp[index++] = val;//找到所指位置
                result = index - 1;//找到下标位置
            }
            else
            {
                ptmp[index++] = *temp;
                temp++;
            }
        }   
    }
    else
    {
        ptmp = new T[1];
        size = 1;
        ptmp[0] = val;
        result = 0;
    }
    T* ptmp2 = ptmp + size;
    begin = *(new RA_iterator<T>(ptmp));
    end = *(new RA_iterator<T>(ptmp2));
    return (begin + result);
}

template<typename T>
RA_iterator<T> Vector<T>::insert(RA_iterator<T> i, RA_iterator<T> first, RA_iterator<T> last)
{
    size_t add_size = last - first;//获取插入个数
    size = add_size + size;
    T* ptmp = nullptr;
    int result = -1;
    if (begin._ptr)
    {
        int index = 0;
        auto temp = begin;//获取头迭代器
        auto intemp = first;
        ptmp = new T[size];
        while (temp != end+1)
        {
            if (temp == i && (intemp!=last))//找到插入起始位置
            {
                ptmp[index++] =*intemp;
                intemp++;
                if(result==-1)//只需记录起始插入位置
                     result = index - 1;
            }
            else
            {
                ptmp[index++] = *temp;
                temp++;
            }
        }
    }
    else
    {
        ptmp = new T[size];
        auto intemp = first;
        result = 0;
        for (int i = 0; i < size; ++i)
        {
            ptmp[i] = *intemp;
            intemp++;  
        }
        
    }
    T* ptmp2 = ptmp + size;
    begin = *(new RA_iterator<T>(ptmp));
    end = *(new RA_iterator<T>(ptmp2));
    return (begin + result);
}

template<typename T>
RA_iterator<T> Vector<T>::erase(RA_iterator<T> i)
{
    if (size < 1)
    {
        cerr << "容器个数过小,删除失败，返回头迭代器" << endl;
        return begin;
    }
    auto temp = i;
    if (end == i)//删除最后一个元素
    {
        *(end-1)=*end;
        size--;
        return end;
    }
    while (temp != end - 1)
    {
        RA_iterator<T> after = temp + 1;
        *(temp++) = *after;//元素依次向前移动，不申请新的空间
    }
    size--;
    end--;
    return i;
}

template<typename T>
RA_iterator<T> Vector<T>::erase(RA_iterator<T> first, RA_iterator<T> last)//实际删除
{
    size_t size_del = last - first;
    int result = first - begin;
    size -= size_del;
    T* temp = new T[size];
    int index = 0;
    for (auto i = begin; i !=end; ++i)
    {
        if (i >= first && i < last)
            continue;
        temp[index++] = *i;
    }
    T* temp2 = temp + size;
    begin = *(new RA_iterator<T>(temp));
    end = *(new RA_iterator<T>(temp2));
    return (begin + result);
}


template<typename T>
inline void Vector<T>::pop_back()
{
    if (size < 1)//个数小于1
        return;
    end--;//并不是真正删除，而是采取不访问这种形式删除
    size--;
}

template<typename T>//删除所有元素
void Vector<T>::MakeEmpty()
{
    if (begin._ptr)
    {
        delete[] begin._ptr;
        begin._ptr = nullptr;
        size = 0;
        end = begin;
    }
}

template<typename T>
void Vector<T>::swap(Vector<T>& v)
{
    auto temp = *this;
    *this = v;
    v = temp;
}

template<typename T>//函数重载：重置数组个数
bool Vector<T>::reset(size_t nsize)
{
    if (nsize < 1) { return false; }
    if (begin._ptr) { delete[] begin._ptr; begin._ptr = nullptr; }
    T* temp = new T[nsize];
    size = nsize;
    T* temp2 = temp + size;
    begin = *(new RA_iterator<T>(temp));
    end = *(new RA_iterator<T>(temp2));
    temp = temp2 = NULL;
    return true;
}

template<typename T>//函数重载：重置对象个数，并给定所有元素的初始值
void Vector<T>::reset(size_t nsize, T obj)
{
    bool isset = reset(nsize);
    if (isset)
    {
        for (size_t i = 0; i < nsize; ++i)
        {
            begin[i] = obj;
        }
    }
}

template<typename T>
void Vector<T>::show(string s)
{
    cout << s<<"的大小为：" << size << ",数据如下：" << endl;
    for (auto i = begin; i != end; ++i)
        cout << *i << " ";
    cout << endl;
}

template<typename T>
inline bool Vector<T>::Find(T x)
{
    for (auto i = begin; i != end; ++i)
        if (*i == x)
            return true;
    return false;
}

 


