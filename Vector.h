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
    Vector() : begin(nullptr), end(nullptr), size(0) {} //���캯��
    Vector(size_t nsize);//����Ԫ�ظ�����������
    Vector(size_t nsize, T obj); //����Ԫ�صĸ�����Ԫ�صĳ�ʼֵ��������
    Vector(const Vector& obj); //��������
    Vector(RA_iterator<T>star, RA_iterator<T>finish);//ͨ������������
    ~Vector(); //��������

    RA_iterator<T> Begin() { return begin; }//��ȡͷ������
    RA_iterator<T> End() { return end; }//��ȡβ������
    rRA_iterator<T> rBegin() { return *(new rRA_iterator<T>(end._ptr-1)); }//��ȡ����ͷ������
    rRA_iterator<T> rEnd() { return *(new rRA_iterator<T>(begin._ptr-1)); }//��ȡ����β������
    size_t getsize() const { return size; }//����������Ԫ�صĸ���
    T& front() { return *begin; }//��ȡ��Ԫ������
    T& back() { auto temp = end ; return *(temp-1); }//��ȡβԪ������
    bool empty() { return size == 0 ? true : false; }//�ж������Ƿ�Ϊ��

    T& operator [](size_t i) const; //���������[],����ֵΪ��ֵ����
    Vector& operator = (Vector& obj);//��ֵ����
    T At(size_t i) const;//��ȡ�����е�N��Ԫ�ص�ֵ
    bool Find(T x);//����ĳ��Ԫ��

    void push_back(const T& elem);//��ĩβ����һ��Ԫ��
    RA_iterator<T> insert(RA_iterator<T> i, const T& val);//�� val ��������� i ָ���λ�ã����� i
    RA_iterator<T> insert(RA_iterator<T> i, RA_iterator<T> first, RA_iterator<T> last); //�����������ϵ�����[first, last) �е�Ԫ�ز�������� i ָ���λ��
    RA_iterator<T> erase(RA_iterator<T> i);//ɾ�������� i ָ���Ԫ�أ�����ֵ�Ǳ�ɾԪ�غ����Ԫ�صĵ�����
    RA_iterator<T> erase(RA_iterator<T> first, RA_iterator<T> last);//ɾ�������е����� [first, last)

    void pop_back();//ɾ��ĩβԪ��
    void MakeEmpty(); //ɾ������Ԫ��
    void swap(Vector <T>& v);//��������������ݺ���һ��ͬ���͵����� v ����
    bool reset(size_t nsize);//�������أ������������  
    void reset(size_t nsize, T obj);//�������أ����ö������������������Ԫ�صĳ�ʼֵ
    void show(string s="vector");//չʾvector
};

template<typename T>//����Ԫ�ظ�����������
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

template<typename T>//����Ԫ�صĸ�����Ԫ�صĳ�ʼֵ��������
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

template<typename T>//��������
Vector<T>::Vector(const Vector& obj)
{
    //�����µĿռ��������
    T *temp = new T[obj.getsize()];
    //����ԭ�����ݵ��µĿռ�
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
 
template<typename T>//��������
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


template<typename T>//���������[],����ֵΪ��ֵ����
T& Vector<T>::operator [](size_t i) const
{
    if (begin._ptr != nullptr && i >= 0 && i < size)
    {
        return begin[i];
    }
}

template<typename T>//��ֵ����
Vector<T>& Vector<T>::operator= (Vector<T>& obj)
{
    if (begin== obj.begin) { return *this; }
    if (obj.begin._ptr == nullptr)
    {
        if (begin._ptr) { begin = nullptr; size = 0; end = begin; }
        return *this;
    }
    if (begin._ptr) {
        //���ԭ������
        delete[] begin._ptr; begin = nullptr; end = begin;
    }
    T* temp = new T[obj.getsize()];
    //����ԭ�����ݵ��µĿռ�
    for (int i = 0; i < obj.getsize(); ++i)
        temp[i] = obj[i];
    size = obj.getsize();
    T* temp2 = temp + size;
    begin = *(new RA_iterator<T>(temp));
    end = *(new RA_iterator<T>(temp2));
    temp = temp2 = NULL;
    return *this;
}

template<typename T>//��ĩβ����һ��Ԫ��
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
        auto temp = begin;//��ȡͷ������
        ptmp = new T[++size];
        while (temp!=end)
        {
            if (temp == i&&result==-1)//result�ǿ���һ�������ֱ�ӿ���
            {
                ptmp[index++] = val;//�ҵ���ָλ��
                result = index - 1;//�ҵ��±�λ��
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
    size_t add_size = last - first;//��ȡ�������
    size = add_size + size;
    T* ptmp = nullptr;
    int result = -1;
    if (begin._ptr)
    {
        int index = 0;
        auto temp = begin;//��ȡͷ������
        auto intemp = first;
        ptmp = new T[size];
        while (temp != end+1)
        {
            if (temp == i && (intemp!=last))//�ҵ�������ʼλ��
            {
                ptmp[index++] =*intemp;
                intemp++;
                if(result==-1)//ֻ���¼��ʼ����λ��
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
        cerr << "����������С,ɾ��ʧ�ܣ�����ͷ������" << endl;
        return begin;
    }
    auto temp = i;
    if (end == i)//ɾ�����һ��Ԫ��
    {
        *(end-1)=*end;
        size--;
        return end;
    }
    while (temp != end - 1)
    {
        RA_iterator<T> after = temp + 1;
        *(temp++) = *after;//Ԫ��������ǰ�ƶ����������µĿռ�
    }
    size--;
    end--;
    return i;
}

template<typename T>
RA_iterator<T> Vector<T>::erase(RA_iterator<T> first, RA_iterator<T> last)//ʵ��ɾ��
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
    if (size < 1)//����С��1
        return;
    end--;//����������ɾ�������ǲ�ȡ������������ʽɾ��
    size--;
}

template<typename T>//ɾ������Ԫ��
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

template<typename T>//�������أ������������
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

template<typename T>//�������أ����ö������������������Ԫ�صĳ�ʼֵ
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
    cout << s<<"�Ĵ�СΪ��" << size << ",�������£�" << endl;
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

 


