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
	//ͷ�巨��������
	void createListByHead();
	//β�巨��������
	//void createListByTail();
	//ָ��λ�ò���ڵ�
	bool insertNode(int n, int data);
	//���Ҹ����������Ƿ����
	bool findData(int data);
	//ɾ��������ָ�����ݵ�һ�γ��ֵĽڵ�
	bool eraseNode(int data);
	//ɾ��������ָ�����ݳ��ֵ����нڵ�
	bool eraseAllNode(int data);
	//ͷ������ڵ�
	void pushFront(int data);
	//ͷ��ɾ���ڵ�
	void popFront();
	//β������ڵ�
	void pushBack(int data);
	//β��ɾ���ڵ�
	void popBack();
	//��������ĳ���
	int getLength();
	//��ӡ����
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
	cout << "����ͷ�巨��������\n";
	cout << "����Ҫ���������Ĵ�С��";
	int n;
	cin >> n;
	//Node* nextNode = pTail;
	for (int i = 0; i < n; ++i)
	{
		Node* temp = new Node();
		
		cout << "���������" << i + 1 << "���ڵ��ֵ��";
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
		cout << "����λ�ó�������Χ\n";
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
	cout << "������û��ֵΪ" << n << "�Ľڵ�\n";
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
		cout << "û��Ҫɾ���Ľڵ�\n";
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
		cout << "����Ϊ�գ����ܽ��д˲���\n";
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

//����
int main()
{
	DList dl;
	dl.createListByHead();
	dl.display();
	cout << "ͷ�巨����һ���ڵ�\n";
	dl.pushFront(4);
	dl.display();
	cout << "β�巨����һ���ڵ�\n";
	dl.pushBack(2);
	dl.display();
	cout << "ɾ��ͷ����ڵ�\n";
	dl.eraseNode(4);
	dl.display();
	cout << "ɾ������β����ڵ�\n";
	dl.eraseAllNode(2);
	dl.display();
	cout << "�ڵ�һ��λ�ò���ڵ�3\n";
	dl.insertNode(1, 3);
	dl.display();

	system("pause");
	return 0;
}