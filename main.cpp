#include"Vector.h"
#include"GlobalMethods.h"
#include"List.h"
#include"Hash_Set.h"

void vector_test();//vector���Ժ���
void list_test();//list���Ժ���
void set_test();//set���Ժ���

int main()
{
	while (true)
	{
		cout << "����ѡ����Ҫ������Ŀ��0��һ����ԡ�1������vector��2������list��3������set��-1���˳���" << endl;
		int choice = -99;
		cin >> choice;
		if (choice == 0)
		{
			system("cls");
			vector_test();
			list_test();
			set_test();
		}
		else if (choice == 1)
		{
			system("cls");
			vector_test();
		}
		else if (choice == 2)
		{
			system("cls");
			list_test();
		}
		else if (choice == 3)
		{
			list_test();
			set_test();
		}
		else if (choice == -1)
			exit(0);
		else
			cout << "��������������������룡" << endl;
	}
}

void vector_test()//vector����
{
	cout << "����vector�Ĳ��Գ���" << endl;
	Vector<int>v0;//����Ĭ�Ϲ���,��ʱv0ȫΪ��
	auto v1 = Vector<int>(5);//���ù��췽��1
	auto v2 = Vector<int>(5, 5);//���ù��췽��2
	//����push_back  show 
	cout << "��ǰ��ʼ������v0Ϊ�գ�v1���Ԫ�أ�v2�����5��" << endl;
	cout << endl;
	cout << "pushback��show:" << endl;
	cout << "v0���á�push_back���������β���0-90,���á�show�������鿴������" << endl;
	for (int i = 0; i < 10; i++)//v0����10-100
		v0.push_back(10 * i);
	v0.show("v0");
	cout << endl;
	//����front back
	cout << "front��back:" << endl;
	cout << "v0���á�front���������κ͵��á�back�������޸���λԪ��" << endl;
	v0.front() = 90;
	v0.back() = 0;
	v0.show("v0");
	cout << endl;
	//����[], At,Find
	cout << "[]��At��Find:" << endl;
	cout << "v0��[]��At��Find����50" << endl;
	cout << "[]:" << v0[5] << ",At:" << v0.At(5) << ",Find:" << v0.Find(50) << endl;
	cout << endl;
	//swap
	cout << "swap:" << endl;
	cout << "v1��v2����swap����:" << endl;
	v1.swap(v2);
	v1.show("v1");
	v2.show("v2");
	cout << endl;
	//reset
	cout << "reset:" << endl;
	cout << "v2����Ϊ��С6" << endl;
	v2.reset(6);
	v2.show("v2");
	cout << "v2����Ϊ8��8" << endl;
	v2.reset(8, 8);
	v2.show("v2");
	cout << endl;
	//popback��MakeEmpty��empty
	cout << "popback��MakeEmpty��empty:" << endl;
	cout << "v1ɾ��βԪ�أ�" << endl;
	v1.pop_back();
	v1.show("v1");
	cout << "v1��գ����ж��Ƿ�Ϊ�գ�" << endl;
	v1.MakeEmpty();
	cout << v1.empty() << endl;
	cout << endl;
	//��ȡv0��v2����������������������
	cout << "Begin��End��rBegin��rEnd:" << endl;
	auto begin0 = v0.Begin();
	auto begin2 = v2.Begin();
	auto end0 = v0.End();
	auto end2 = v2.End();
	auto rbegin0 = v0.rBegin();
	auto rbegin2 = v2.rBegin();
	auto rend0 = v0.rEnd();
	auto rend2 = v2.rEnd();
	cout << "�ֱ�ͨ������ͷ������������v0Ԫ��" << endl;
	cout << "����" << endl;
	for (auto i = begin0; i != end0; ++i)
		cout << *i << "  ";
	cout << endl;
	cout << "����" << endl;
	for (auto i = rbegin0; i != rend0; ++i)
		cout << *i << "  ";
	cout << endl;
	cout << endl;
	//����������
	cout << "ͨ�����������������v4��v4������v0����βԪ��" << endl;
	Vector<int>v4(begin0+1, end0-1);
	v4.show("v4");
	cout << endl;
	//insert
	cout <<"insert:" << endl;
	cout << "������v2ͷָ���һ��λ����ָλ�ò���0" << endl;
	auto r = v2.insert(begin2+1, 0);
	v2.show("v2");
	cout << "��v2����Ԫ�ز��뵽v4ĩβ" << endl;
	v4.insert(v4.End(),v2.Begin(), v2.End());
	v4.show("v4");
	cout << endl;
	//erase
	cout << "erase:" << endl;
	cout << "������v2ͷָ���һ��λ����ָλ��ɾ��0" << endl;
	auto re = v2.erase(v2.Begin() + 1);
	v2.show("v2");
	cout << "v4ɾ����8-16Ԫ�أ����ող����v2����" << endl;
	v4.erase(v4.Begin()+8, v4.Begin()+17);
	v4.show("v4");
	cout << endl;

	//����
	cout << "v0����ȫ�ֵ�bubble_sort:" << endl;
	bubble_sort(v0.Begin(), v0.End(),self_compare1);
	v0.show("v0");
	cout << "v0����ȫ�ֵ�Find_if,���ҵ�һ��ż��:" << endl;
	auto result= Find_if(v0.Begin(), v0.End(), Condition1<int>);
	cout << *result << endl;
}


void list_test()//list���Ժ���
{
	List<int>L0;
	List<int>L1;
	List<int>L2(6, 6);
	for (int i = 0; i < 5; ++i)
	{
		for (auto j = 0; j <= i; j++)
			L0.insert(i);
	}
	cout << "����list�Ĳ��Գ���" << endl;
	cout << "��ǰ��ʼ������L0={0 1 1 2 2 2 3 3 3 3 4 4 4 4 4}��L1Ϊ�գ�L2��6��6��" << endl;
	cout << endl;
	cout << "insert showList��L1���β���10-100" << endl;
	for (auto i = 1; i <= 10; ++i)
		L1.insert(10 * i);
	L1.showList("L1");
	cout << endl;
	//push_front
	cout << "push_front��L1ͷ��2000" << endl;
	L1.push_front(2000);
	L1.showList("L1");
	cout << endl;
	//Sort��find��find_index
	cout << "Sort��find��find_index��L1����������������,�����ҵ�5��Ԫ��,���Ҳ���60���±�" << endl;
	L1.Sort();
	L1.showList("L1");
	cout << "L1�����Ԫ���ǣ�" << L1.find(5) << " " << "60���±�Ϊ��" << L1.find_index(60) << endl;
	cout << endl;
	//pop_front��unique��remove
	cout << "pop_front��unique��remove:L0ɾ����Ԫ�ؼ�0,Ȼ�����unique,���ɾ��4" << endl;
	L0.pop_front();
	L0.showList("L0");
	L0.unique();
	L0.showList("L0");
	L0.Remove(4);
	L0.showList("L0");
	cout << endl;
	//clear isEmpty
	cout << "clear isEmpty:L2����clear������н�㣬�����isEmpty����Ƿ���ճɹ�" << endl;
	L2.clear();
	cout << "L2�Ƿ�Ϊ�գ�" << L2.IsEmpty() << endl;
	cout << endl;
	//merge
	cout << "merge:L3ͨ�����ƹ���L0���ã�Ȼ��ϲ�L1��L3" << endl;
	List<int>L3(L0);
	L3.showList("L3");
	L1.merge(L3);
	L1.showList("L1");
	L3.showList("L3");
	cout << endl;
	//begin��rbegin��end��rend
	cout << "begin��rbegin��end��rend:�ֱ�ͨ������ͷ������������L1��Ԫ��" << endl;
	cout << "����:";
	for (auto i = L1.begin(); i != L1.end(); ++i)
		cout << *i << " ";
	cout << endl<<"����:";
	for (auto i = L1.rbegin(); i != L1.rend(); ++i)
		cout << *i << " ";
	cout << endl << endl;
	//spice
	cout << "spice:��L1��2��Ԫ��ǰ���������100��2000" << endl;
	L1.splice(++L1.begin(), L1, (--(--L1.end())), L1.end());
	L1.showList("L1");
	cout << endl;
	//ȫ�ֵ�����
	cout << "L1����ȫ�ֵ�bubble_sort:" << endl;
	bubble_sort(L1.begin(), L1.end(), self_compare1);
	L1.showList("L1");
	cout << "v0����ȫ�ֵ�Find_if,���ҵ�һ��ż��:" << endl;
	auto result = Find_if(L1.begin(), L1.end(), Condition1<int>);
	cout << *result << endl;
}

void set_test()
{
	cout << "����set�Ĳ��Գ���" << endl;
	//insert
	cout << "insert:set����insert���β���1-60��Ԫ�أ���ʼ�������£�" << endl;
	Hash_Set<int>s(13,13);
	for (int i = 1; i <= 60; ++i)
		s.Insert(i);
	s.show();
	cout << endl;
	//Find remove
	cout << "Find remove:ɾ��30�������β���29,30" << endl;
	s.Remove(30);
	cout << "29�Ƿ���ڣ�" << s.Find(29) << ",30�Ƿ���ڣ�" <<s.Find(30)<< endl;
	cout << endl;
	//begin end
	cout << "begin end:ͨ�����������ʼ���Ԫ��" << endl;
	for (auto i = s.Begin(); i != s.End(); ++i)
		cout << *i << " ";
	cout << *s.End()<<endl << endl;
	//erase
	cout << "erase:ɾ����һ��Ԫ�أ�ͨ�����ص�������������һ��Ԫ��" << endl;
	auto result = s.erase(s.Begin());
	cout << "ɾ����һ��Ԫ�غ�һ��Ԫ��Ϊ��" << *result << endl;
	cout << "erase:ɾ����һ���͵ڶ�����ͨ�����ص�������������һ��Ԫ��" << endl;
	auto result2 = s.erase(s.Begin(),++(++s.Begin()));
	cout << "ɾ����1-2��Ԫ�غ�һ��Ԫ��Ϊ��" << *result2<< endl;
	cout << endl;
	//insert
	cout << "����s0��Ԫ��0-100����s0��[begin,end)���뵽����s" << endl;
	Hash_Set<int>s0(13, 13);
	for (int i = 0; i <= 100; ++i)
		s0.Insert(i);
	//s0.show();
	s.Insert(s0.Begin(), s0.End());
	s.show();
	cout << endl;
	//lower_bound��upper_bound��equal_range
	cout << "lower_bound��upper_bound��equal_range��" << endl;
	auto r1 = s.lower_bound(20);
	auto r2 = s.upper_bound(20);
	cout << *r1 << "֮ǰ��Ԫ�ؾ�С��20��" << *r2 << "֮���Ԫ�ؾ�����20" << endl;
	auto r3 = s.equal_range(40);
	cout << "s����equal_range�Ƚ�40�õ����������Ϊ��" << *(r3.first) << " " << *(r3.second) << endl;
	cout << endl;
	cout << "v0����ȫ�ֵ�Find_if,���ҵ�һ��ż��:" << endl;
	auto a = Find_if(s.Begin(), s.End(), Condition1<int>);
	cout << *a<< endl;
}
