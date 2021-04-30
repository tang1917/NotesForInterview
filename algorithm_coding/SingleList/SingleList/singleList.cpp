#include<iostream>
using namespace std;

//节点结构
struct Node
{
	int data;
	Node* next;
	Node(const int& d) :data(d), next(nullptr) {}
	Node() :data(0), next(nullptr){}
};
class  List
{
public:
	 List();
	~ List();
	//头插法创建链表
	void createListFromHead(int n);
	//尾插法创建链表
	void createListFromTail(int n);
	//头部插入
	void pushFront(int n);
	//尾部插入
	void pushBack(int n);
	//头部删除
	void popFront();
	//尾部删除
	void popBack();
	//删除第一个出现的指定的元素
	void removeNode(int n);
	//删除出现的所有指定元素
	void removeAllNode(int n);
	//查找元素的位置
	Node* find(int n);
	//计算单链表的长度
	int getLength();
	//反转链表
	Node* reverse();
	//打印链表
	void print();


private:

	//头节点
	Node* head;
	
	void clear()
	{
		Node* p = head;
		//从头节点开始循环删除
		while (p)
		{
			Node* q = p->next;
			delete p;
			p = q;
		}
	}
};

 List:: List()
{
	 //创建一个头节点
	 head = new Node(0);
}

 List::~ List()
{
	 clear();
}
 void List::createListFromHead(int n)
 {
	 cout << "输入按照头插法构造链表的"<< n<<"个值：";
	 for (int i = 0; i < n; ++i)
	 {
		 Node* temp = new Node;
		 cin >> temp->data;
		 temp->next = head->next;
		 head->next = temp;
	 }
 }
 void List::createListFromTail(int n)
 {
	cout << "输入按照尾插法构造链表的"<<n<<"个值：";
	Node* cur = head;
	for (int i = 0; i < n; ++i)
	{
		Node* temp = new Node;
		cin >> temp->data;
		cur->next = temp;
		cur = temp;
	}
 }

 //从头部插入一个值
 void List::pushFront(int n)
 {
	 Node* temp = new Node(n);
	 temp->next = head->next;
	 head->next = temp;
 }
 //从尾部插入一个节点
 void List::pushBack(int n)
 {
	 Node* temp = new Node(n);
	 Node* cur = head;
	 if (cur == nullptr)
		 head = temp;
	 while (cur->next != nullptr)
	 {
		 cur = cur->next;
	 }
	 cur->next = temp;
 }
 //从头部删除一个节点
 void List::popFront()
 {
	 if (head->next == nullptr)
	 {
		 cout << "已经是空链表\n";
		return;
	 }
		 
	 Node* temp = head->next;
	 head->next = head->next->next;
	 delete temp;
 }
 //从尾部删除一个节点
 void List::popBack()
 {
	 Node* cur = head;
	 Node* delNode = cur->next;
	 if (delNode == nullptr)
	 {
		 cout << "已经是空链表\n";
		 return;
	 }
	 while (delNode->next != nullptr)
	 {
		 cur = delNode;
		 delNode = delNode->next;
	 }
	 cur->next = nullptr;
	 delete delNode;
 }

 void List::removeNode(int n)
 {
	 Node* cur = head->next;
	 Node* pre = head;
	 while (cur != nullptr && cur->data!=n)
	 {
		 pre = cur;
		 cur = cur->next;
	 }
	 if (cur == nullptr)
	 {
		 cout << "链表中不存在值为" << n << "的节点\n";
		 return;
	 }
	 else
	 {
		 pre->next = cur->next;
		 delete cur;
	 }
 }
 void List::removeAllNode(int n)
 {
	 Node* cur = head->next;
	 Node* pre = head;
	 while (cur != nullptr)
	 {
		 if (cur->data == n)
		 {
			 pre->next = cur->next;
			 Node* temp = cur;
			 delete temp;
			 cur = pre->next;
		 }
		 else
		 {
			 pre = cur;
			 cur = cur->next;
		 }
	 }
 }

 Node* List::find(int n)
 {
	 Node* cur = head->next;
	 while (cur != nullptr&&cur->data != n)
	 {
		 cur = cur->next;
	 }
	 return cur;
 }
 int List::getLength()
 {
	 int len = 0;
	 Node* cur = head->next;
	 while (cur != nullptr)
	 {
		 ++len;
		 cur = cur->next;
	 }
	 return len;
 }
 Node* List::reverse()
 {
	 Node* cur = head->next;
	 Node* pre = nullptr;
	 while (cur != nullptr)
	 {
		 Node* nextNode = cur->next;
		 if (nextNode == nullptr)
			 head->next = cur;
		 cur->next = pre;
		 pre = cur;
		 cur = nextNode;

	 }
	 return head;
 }
 void List::print()
 {
	Node* cur = head->next;
	while(cur != nullptr)
	{
		if (cur->next != nullptr)
		{
			cout << cur->data << "->";
		}
		else
		{
			cout << cur->data;
		}
		
		cur = cur->next;
	 }
	cout << endl;
 }
 //测试
 int main()
 {
	 List list1;
	 int num=4;
	 //list1.createListFromHead(num);
	 list1.createListFromTail(num);
	 list1.print();
	 list1.reverse();
	 list1.print();
	 int l = list1.getLength();
	 cout << "len = " << l<<endl;
	 list1.popBack();
	 list1.print();
	 list1.pushBack(4);
	 list1.print();
	 list1.popFront();
	 list1.print();
	 list1.pushFront(9);
	 list1.pushFront(9);
	 list1.print();
	 list1.removeAllNode(9);
	 list1.print();
	 system("pause");
	 return 0;
 }
