#include<iostream>

using namespace std;

struct Node
{
	int data;
	Node* pNext;
	Node* pLast;
	Node(const int d):data(d),pNext(nullptr),pLast(nullptr){}
	Node():data(0),pNext(nullptr),pLast(nullptr){}
};
class DList
{
public:
	DList();
	~DList();
	//头插法创建链表
	void createListByHead();
	//尾插法创建链表
	//void createListByTail();
	//指定位置插入节点
	bool insertNode(int n, int data);
	//查找给定的数字是否存在
	bool findData(int data);
	//删除链表中指定数据第一次出现的节点
	bool eraseNode(int data);
	//删除链表中指定数据出现的所有节点
	bool eraseAllNode(int data);
	//头部插入节点
	void pushFront(int data);
	//头部删除节点
	void popFront();
	//尾部插入节点
	void pushBack(int data);
	//尾部删除节点
	void popBack();
	//返回链表的长度
	int getLength();
	//打印链表；
	void display();

private:
	Node* pHead;
	Node* pTail;
	int length;
	void clear()
	{
		Node* p = pHead;
		while (p != nullptr)
		{
			Node* q = p->pNext;
			delete p;
			p = q;
		}
	}
};

DList::DList()
{
	pHead = new Node();
	pTail = new Node();
	pHead->pNext = pTail;
	pTail->pLast = pHead;
	length = 0;
}

DList::~DList()
{
	clear();
}
void DList::createListByHead()
{
	cout << "按照头插法构造链表\n";
	cout << "输入要构造的链表的大小：";
	int n;
	cin >> n;
	//Node* nextNode = pTail;
	for (int i = 0; i < n; ++i)
	{
		Node* temp = new Node();
		
		cout << "输入链表第" << i + 1 << "个节点的值：";
		cin >> temp->data;
		temp->pLast = pHead;
		temp->pNext = pHead->pNext;
		pHead->pNext->pLast = temp;
		pHead->pNext = temp;
		
		++length;
	}
}
bool DList::insertNode(int n, int data)
{
	if (n < 0 || n > length)
	{
		cout << "插入位置超出链表范围\n";
		return false;
	}
	Node* temp = new Node(data);
	Node* cur = pHead;
	for (int i = 0; i < n; i++)
	{
		cur = cur->pNext;
	}
	temp->pNext = cur->pNext;
	temp->pLast = cur;
	cur->pNext->pLast = temp;
	cur->pNext = temp;
	++length;
}

bool DList::findData(int n)
{
	Node* cur = pHead->pNext;
	while (cur != pTail)
	{
		if (cur->data == n)
			return true;
		cur = cur->pNext;
	}
	return false;
}
bool DList::eraseNode(int n)
{
	Node* cur = pHead->pNext;
	while (cur != pTail)
	{
		if (cur->data == n)
		{
			cur->pLast->pNext = cur->pNext;
			cur->pNext->pLast = cur->pLast;
			--length;
			delete cur;
			return true;
		}
		cur = cur->pNext;
	}
	cout << "链表中没有值为" << n << "的节点\n";
	return false;
}
bool DList::eraseAllNode(int n)
{
	Node* cur = pHead->pNext;
	int flag = false;
	while (cur != pTail)
	{
		if (cur->data == n)
		{
			flag = true;
			cur->pLast->pNext = cur->pNext;
			cur->pNext->pLast = cur->pLast;
			Node* temp = cur->pNext;
			--length;
			delete cur;
			cur = temp;
		}
		else
			cur = cur->pNext;
	}
	if (!flag)
	{
		cout << "没有要删除的节点\n";
	}
	return false;
}

void DList::popFront()
{
	Node* cur = pHead->pNext;
	if (cur != pTail)
	{
		pHead->pNext = cur->pNext;
		cur->pNext->pLast = pHead;
		delete cur;
		--length;
	}
	else
		cout << "链表为空，不能进行此操作\n";
}
void DList::popBack()
{
	Node* cur = pTail->pLast;
	if (cur != pHead)
	{
		cur->pLast->pNext = pTail;
		pTail->pLast = cur->pLast;
		delete cur;
		--length;
	}
}

void DList::pushFront(int n)
{
	Node* temp = new Node(n);
	pHead->pNext->pLast = temp;
	temp->pNext = pHead->pNext;
	pHead->pNext = temp;
	temp->pLast = pHead;
	++length;
}
void DList::pushBack(int n)
{
	Node* temp = new Node(n);
	pTail->pLast->pNext = temp;
	temp->pLast = pTail->pLast;
	temp->pNext = pTail;
	pTail->pLast = temp;
	++length;
}
int DList::getLength()
{
	return length;
}
void DList::display()
{
	Node* cur = pHead->pNext;
	while (cur!=pTail)
	{
		if (cur->pNext != pTail)
			cout << cur->data << "->";
		else
			cout << cur->data;
		cur = cur->pNext;
	}
	cout << endl;
}

//测试
int main()
{
	DList dl;
	dl.createListByHead();
	dl.display();
	cout << "头插法插入一个节点\n";
	dl.pushFront(4);
	dl.display();
	cout << "尾插法插入一个节点\n";
	dl.pushBack(2);
	dl.display();
	cout << "删除头插入节点\n";
	dl.eraseNode(4);
	dl.display();
	cout << "删除所有尾插入节点\n";
	dl.eraseAllNode(2);
	dl.display();
	cout << "在第一个位置插入节点3\n";
	dl.insertNode(1, 3);
	dl.display();

	system("pause");
	return 0;
}