#include"Vector.h"
#include"GlobalMethods.h"
#include"List.h"
#include"Hash_Set.h"

void vector_test();//vector测试函数
void list_test();//list测试函数
void set_test();//set测试函数

int main()
{
	while (true)
	{
		cout << "【请选择需要测试项目：0：一起测试、1：测试vector、2：测试list、3：测试set、-1：退出】" << endl;
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
			cout << "输入有误，请检查后重新输入！" << endl;
	}
}

void vector_test()//vector测试
{
	cout << "这是vector的测试程序" << endl;
	Vector<int>v0;//调用默认构造,此时v0全为空
	auto v1 = Vector<int>(5);//调用构造方法1
	auto v2 = Vector<int>(5, 5);//调用构造方法2
	//测试push_back  show 
	cout << "当前初始条件：v0为空，v1五个元素，v2有五个5。" << endl;
	cout << endl;
	cout << "pushback、show:" << endl;
	cout << "v0调用【push_back】方法依次插入0-90,调用【show】函数查看插入结果" << endl;
	for (int i = 0; i < 10; i++)//v0插入10-100
		v0.push_back(10 * i);
	v0.show("v0");
	cout << endl;
	//测试front back
	cout << "front、back:" << endl;
	cout << "v0调用【front】方法依次和调用【back】函数修改首位元素" << endl;
	v0.front() = 90;
	v0.back() = 0;
	v0.show("v0");
	cout << endl;
	//测试[], At,Find
	cout << "[]、At、Find:" << endl;
	cout << "v0用[]、At、Find访问50" << endl;
	cout << "[]:" << v0[5] << ",At:" << v0.At(5) << ",Find:" << v0.Find(50) << endl;
	cout << endl;
	//swap
	cout << "swap:" << endl;
	cout << "v1和v2调用swap函数:" << endl;
	v1.swap(v2);
	v1.show("v1");
	v2.show("v2");
	cout << endl;
	//reset
	cout << "reset:" << endl;
	cout << "v2重置为大小6" << endl;
	v2.reset(6);
	v2.show("v2");
	cout << "v2重置为8个8" << endl;
	v2.reset(8, 8);
	v2.show("v2");
	cout << endl;
	//popback、MakeEmpty、empty
	cout << "popback、MakeEmpty、empty:" << endl;
	cout << "v1删除尾元素：" << endl;
	v1.pop_back();
	v1.show("v1");
	cout << "v1清空，并判断是否为空：" << endl;
	v1.MakeEmpty();
	cout << v1.empty() << endl;
	cout << endl;
	//获取v0、v2的正向迭代器、反向迭代器
	cout << "Begin、End、rBegin、rEnd:" << endl;
	auto begin0 = v0.Begin();
	auto begin2 = v2.Begin();
	auto end0 = v0.End();
	auto end2 = v2.End();
	auto rbegin0 = v0.rBegin();
	auto rbegin2 = v2.rBegin();
	auto rend0 = v0.rEnd();
	auto rend2 = v2.rEnd();
	cout << "分别通过正向和反向迭代器访问v0元素" << endl;
	cout << "正向：" << endl;
	for (auto i = begin0; i != end0; ++i)
		cout << *i << "  ";
	cout << endl;
	cout << "反向：" << endl;
	for (auto i = rbegin0; i != rend0; ++i)
		cout << *i << "  ";
	cout << endl;
	cout << endl;
	//迭代器构造
	cout << "通过传入迭代器，构造v4，v4不包含v0的首尾元素" << endl;
	Vector<int>v4(begin0+1, end0-1);
	v4.show("v4");
	cout << endl;
	//insert
	cout <<"insert:" << endl;
	cout << "向容器v2头指针后一个位置所指位置插入0" << endl;
	auto r = v2.insert(begin2+1, 0);
	v2.show("v2");
	cout << "将v2所有元素插入到v4末尾" << endl;
	v4.insert(v4.End(),v2.Begin(), v2.End());
	v4.show("v4");
	cout << endl;
	//erase
	cout << "erase:" << endl;
	cout << "向容器v2头指针后一个位置所指位置删除0" << endl;
	auto re = v2.erase(v2.Begin() + 1);
	v2.show("v2");
	cout << "v4删除第8-16元素，即刚刚插入的v2部分" << endl;
	v4.erase(v4.Begin()+8, v4.Begin()+17);
	v4.show("v4");
	cout << endl;

	//排序
	cout << "v0调用全局的bubble_sort:" << endl;
	bubble_sort(v0.Begin(), v0.End(),self_compare1);
	v0.show("v0");
	cout << "v0调用全局的Find_if,查找第一个偶数:" << endl;
	auto result= Find_if(v0.Begin(), v0.End(), Condition1<int>);
	cout << *result << endl;
}


void list_test()//list测试函数
{
	List<int>L0;
	List<int>L1;
	List<int>L2(6, 6);
	for (int i = 0; i < 5; ++i)
	{
		for (auto j = 0; j <= i; j++)
			L0.insert(i);
	}
	cout << "这是list的测试程序" << endl;
	cout << "当前初始条件：L0={0 1 1 2 2 2 3 3 3 3 4 4 4 4 4}、L1为空，L2有6个6。" << endl;
	cout << endl;
	cout << "insert showList：L1依次插入10-100" << endl;
	for (auto i = 1; i <= 10; ++i)
		L1.insert(10 * i);
	L1.showList("L1");
	cout << endl;
	//push_front
	cout << "push_front：L1头插2000" << endl;
	L1.push_front(2000);
	L1.showList("L1");
	cout << endl;
	//Sort、find、find_index
	cout << "Sort、find、find_index：L1调用自身升序排序,并查找第5个元素,并且查找60的下标" << endl;
	L1.Sort();
	L1.showList("L1");
	cout << "L1第五个元素是：" << L1.find(5) << " " << "60的下标为：" << L1.find_index(60) << endl;
	cout << endl;
	//pop_front、unique、remove
	cout << "pop_front、unique、remove:L0删除首元素即0,然后调用unique,最后删除4" << endl;
	L0.pop_front();
	L0.showList("L0");
	L0.unique();
	L0.showList("L0");
	L0.Remove(4);
	L0.showList("L0");
	cout << endl;
	//clear isEmpty
	cout << "clear isEmpty:L2调用clear清空所有结点，最后用isEmpty检查是否清空成功" << endl;
	L2.clear();
	cout << "L2是否为空：" << L2.IsEmpty() << endl;
	cout << endl;
	//merge
	cout << "merge:L3通过复制构造L0所得，然后合并L1和L3" << endl;
	List<int>L3(L0);
	L3.showList("L3");
	L1.merge(L3);
	L1.showList("L1");
	L3.showList("L3");
	cout << endl;
	//begin、rbegin、end、rend
	cout << "begin、rbegin、end、rend:分别通过正向和反向迭代器访问L1的元素" << endl;
	cout << "正向:";
	for (auto i = L1.begin(); i != L1.end(); ++i)
		cout << *i << " ";
	cout << endl<<"反向:";
	for (auto i = L1.rbegin(); i != L1.rend(); ++i)
		cout << *i << " ";
	cout << endl << endl;
	//spice
	cout << "spice:在L1第2个元素前插入自身的100和2000" << endl;
	L1.splice(++L1.begin(), L1, (--(--L1.end())), L1.end());
	L1.showList("L1");
	cout << endl;
	//全局的排序
	cout << "L1调用全局的bubble_sort:" << endl;
	bubble_sort(L1.begin(), L1.end(), self_compare1);
	L1.showList("L1");
	cout << "v0调用全局的Find_if,查找第一个偶数:" << endl;
	auto result = Find_if(L1.begin(), L1.end(), Condition1<int>);
	cout << *result << endl;
}

void set_test()
{
	cout << "这是set的测试程序" << endl;
	//insert
	cout << "insert:set调用insert依次插入1-60的元素，初始化后如下：" << endl;
	Hash_Set<int>s(13,13);
	for (int i = 1; i <= 60; ++i)
		s.Insert(i);
	s.show();
	cout << endl;
	//Find remove
	cout << "Find remove:删除30，再依次查找29,30" << endl;
	s.Remove(30);
	cout << "29是否存在：" << s.Find(29) << ",30是否存在：" <<s.Find(30)<< endl;
	cout << endl;
	//begin end
	cout << "begin end:通过迭代器访问集合元素" << endl;
	for (auto i = s.Begin(); i != s.End(); ++i)
		cout << *i << " ";
	cout << *s.End()<<endl << endl;
	//erase
	cout << "erase:删除第一个元素，通过返回迭代器，输出其后一个元素" << endl;
	auto result = s.erase(s.Begin());
	cout << "删除第一个元素后一个元素为：" << *result << endl;
	cout << "erase:删除第一个和第二个，通过返回迭代器，输出其后一个元素" << endl;
	auto result2 = s.erase(s.Begin(),++(++s.Begin()));
	cout << "删除第1-2个元素后一个元素为：" << *result2<< endl;
	cout << endl;
	//insert
	cout << "集合s0有元素0-100，将s0中[begin,end)插入到集合s" << endl;
	Hash_Set<int>s0(13, 13);
	for (int i = 0; i <= 100; ++i)
		s0.Insert(i);
	//s0.show();
	s.Insert(s0.Begin(), s0.End());
	s.show();
	cout << endl;
	//lower_bound、upper_bound、equal_range
	cout << "lower_bound、upper_bound、equal_range：" << endl;
	auto r1 = s.lower_bound(20);
	auto r2 = s.upper_bound(20);
	cout << *r1 << "之前的元素均小于20，" << *r2 << "之后的元素均大于20" << endl;
	auto r3 = s.equal_range(40);
	cout << "s调用equal_range比较40得到的两个结果为：" << *(r3.first) << " " << *(r3.second) << endl;
	cout << endl;
	cout << "v0调用全局的Find_if,查找第一个偶数:" << endl;
	auto a = Find_if(s.Begin(), s.End(), Condition1<int>);
	cout << *a<< endl;
}
