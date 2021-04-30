#include<iostream>
using namespace std;

//�ڵ�ṹ
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
	//ͷ�巨��������
	void createListFromHead(int n);
	//β�巨��������
	void createListFromTail(int n);
	//ͷ������
	void pushFront(int n);
	//β������
	void pushBack(int n);
	//ͷ��ɾ��
	void popFront();
	//β��ɾ��
	void popBack();
	//ɾ����һ�����ֵ�ָ����Ԫ��
	void removeNode(int n);
	//ɾ�����ֵ�����ָ��Ԫ��
	void removeAllNode(int n);
	//����Ԫ�ص�λ��
	Node* find(int n);
	//���㵥����ĳ���
	int getLength();
	//��ת����
	Node* reverse();
	//��ӡ����
	void print();


private:

	//ͷ�ڵ�
	Node* head;
	
	void clear()
	{
		Node* p = head;
		//��ͷ�ڵ㿪ʼѭ��ɾ��
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
	 //����һ��ͷ�ڵ�
	 head = new Node(0);
}

 List::~ List()
{
	 clear();
}
 void List::createListFromHead(int n)
 {
	 cout << "���밴��ͷ�巨���������"<< n<<"��ֵ��";
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
	cout << "���밴��β�巨���������"<<n<<"��ֵ��";
	Node* cur = head;
	for (int i = 0; i < n; ++i)
	{
		Node* temp = new Node;
		cin >> temp->data;
		cur->next = temp;
		cur = temp;
	}
 }

 //��ͷ������һ��ֵ
 void List::pushFront(int n)
 {
	 Node* temp = new Node(n);
	 temp->next = head->next;
	 head->next = temp;
 }
 //��β������һ���ڵ�
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
 //��ͷ��ɾ��һ���ڵ�
 void List::popFront()
 {
	 if (head->next == nullptr)
	 {
		 cout << "�Ѿ��ǿ�����\n";
		return;
	 }
		 
	 Node* temp = head->next;
	 head->next = head->next->next;
	 delete temp;
 }
 //��β��ɾ��һ���ڵ�
 void List::popBack()
 {
	 Node* cur = head;
	 Node* delNode = cur->next;
	 if (delNode == nullptr)
	 {
		 cout << "�Ѿ��ǿ�����\n";
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
		 cout << "�����в�����ֵΪ" << n << "�Ľڵ�\n";
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
 //����
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
