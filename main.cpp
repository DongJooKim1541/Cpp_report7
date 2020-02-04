#include <iostream>
using namespace std;

class BaseArray {
protected:
	int capacity; // ���� �Ҵ�� �޸� �뷮
	int *mem;
public:
	BaseArray(int capacity = 100) {
		cout << "Basearray �����ִ� ������" << endl;
		this->capacity = capacity; mem = new int[capacity];
	}
	BaseArray(const BaseArray& b) {
		cout << "Basearray ���� ������" << endl;
		capacity = b.capacity;
		mem = new int[b.capacity];
		for (int i = 0; i< capacity; i++)
		{
			mem[i] = b.mem[i];
		}
	}
	BaseArray& operator=(const BaseArray& other) {
		cout << "BaseArray ���Կ����� �����ε�" << endl;
		if (this != &other) {
			delete[] mem;
			mem = new int[other.capacity];
			capacity = other.capacity;
			for (int i = 0; i < other.capacity; i++) {
				mem[i] = other.mem[i];
			}
		}
		return *this;
	}
	~BaseArray() {
		cout << "BaseArray �Ҹ���" << endl;
		if (mem) {
			delete[] mem;
		}
	}
	void put(int index, int val) { mem[index] = val; }
	int get(int index) { return mem[index]; }
	int getCapacity() { return capacity; }
};
class MyQueue : public BaseArray {
	int head, tail;
	int size; // ���� ť �ȿ� �ִ� �������� ����
public:
	MyQueue(int capacity);
	MyQueue(const MyQueue& m);
	~MyQueue();
	MyQueue& operator=(const MyQueue& other);
	void enqueue(int n);
	int dequeue();
	int length();
};
MyQueue::MyQueue(int capacity)
	: BaseArray(capacity)
{
	cout << "Queue �����ִ� ������" << endl;
	head = 0; // ������ ��ġ�� head
	tail = -1;  // tail+1 ��ġ���� ������
	size = 0; // �ʱ� ������ 0
}
MyQueue::MyQueue(const MyQueue& m)
	: BaseArray(m) {
	cout << "Queue ���������" << endl;
	head = m.head;
	tail = m.tail;
	size = m.size;
}
MyQueue::~MyQueue()
{
	cout << "Queue �Ҹ���" << endl;
}
MyQueue& MyQueue::operator=(const MyQueue& other) {
	if (this != &other) {
		delete[] mem;
		mem = new int[other.capacity];
		this->capacity = other.capacity;
		for (int i = 0; i < other.capacity; i++) {
			mem[i] = other.mem[i];
		}
		head = other.head;
		tail = other.tail;
		size = other.size;
	}
	return *this;
}
void MyQueue::enqueue(int n) {
	if (size == capacity)
		return; // queue full error
	put(head, n);
	head++;
	//head = head % capacity;
	size++;
}

int MyQueue::dequeue() {
	if (size == 0)
		return -1; // queue empty error
	size--;
	tail++;
	//tail = tail % capacity;
	return get(tail);
}

int MyQueue::length() {
	return size;
}
class MyStack : public BaseArray {
	int tos; // ������ push �� ��ġ. ���ÿ� ����ִ� ������ ����
public:
	MyStack(int capacity);
	MyStack(const MyStack& m);
	~MyStack();
	MyStack& operator=(const MyStack& other);
	void push(int n);
	int pop();
	int length() { return tos; }
};

MyStack::MyStack(int capacity)
	: BaseArray(capacity)
{
	cout << "Stack �����ִ� ������" << endl;
	tos = 0; // tos�� ���� ���ÿ� ��� �ִ� ������ �ٷ������ �ȴ�.
}
MyStack::MyStack(const MyStack& m)
	: BaseArray(m)
{
	cout << "Stack ���� ������" << endl;
	tos = m.tos;
}
MyStack::~MyStack() {
	cout << "Stack �Ҹ���" << endl;
}
MyStack& MyStack::operator=(const MyStack& other) {
	if (this != &other) {
		delete[] mem;
		mem = new int[other.capacity];
		this->capacity = other.capacity;
		for (int i = 0; i < other.capacity; i++) {
			mem[i] = other.mem[i];
		}
		tos = other.tos;
	}
	return *this;
}
void MyStack::push(int n) {
	if (tos == capacity)
		return; // stack full error
	put(tos, n);
	tos++;
}

int MyStack::pop() {
	if (tos == 0)
		return -1; // stack empty error
	tos--;
	return get(tos);
}

int main() {
	//Queue
	MyQueue mQ(100);
	int n;
	cout << "ť�� ������ 5���� ������ �Է��϶�>> ";
	for (int i = 0; i<5; i++) {
		cin >> n;
		mQ.enqueue(n); // ť�� ����
	}
	cout << "ť�� �뷮:" << mQ.getCapacity() << ", ť�� ũ��:" << mQ.length() << endl;
	cout << "ť�� ���Ҹ� ������� �����Ͽ� ����Ѵ�>> ";
	while (mQ.length() != 0) {
		cout << mQ.dequeue() << ' '; // ť���� �����Ͽ� ���
	}
	cout << endl << "ť�� ���� ũ�� : " << mQ.length() << endl;
	MyQueue q2(mQ);
	cout << "ť�� ������ 3���� ������ �Է��϶�>> ";
	for (int i = 0; i<3; i++) {
		cin >> n;
		q2.enqueue(n); // ť�� ����
	}
	cout << "ť�� �뷮:" << q2.getCapacity() << ", ť�� ũ��:" << mQ.length() << endl;
	cout << "ť�� ���Ҹ� ������� �����Ͽ� ����Ѵ�>> ";
	while (q2.length() != 0) {
		cout << q2.dequeue() << ' '; // ť���� �����Ͽ� ���
	}
	cout << endl << "ť�� ���� ũ�� : " << q2.length() << endl;
	//Stack
	MyStack mStack(100);
	cout << "���ÿ� ������ 5���� ������ �Է��϶�>> ";
	for (int i = 0; i<5; i++) {
		cin >> n;
		mStack.push(n); // ���ÿ� Ǫ��
	}
	cout << "���� �뷮:" << mStack.getCapacity() << ", ���� ũ��:" << mStack.length() << endl;
	cout << "������ ��� ���Ҹ� ���Ͽ� ����Ѵ�>> ";
	while (mStack.length() != 0) {
		cout << mStack.pop() << ' '; // ���ÿ��� ��
	}
	cout << endl << "������ ���� ũ�� : " << mStack.length() << endl;

	MyStack s2(mStack);
	MyStack s3(10);
	cout << "s3 ���ÿ� ������ 3���� ������ �Է��϶�>> ";
	for (int i = 0; i<3; i++) {
		cin >> n;
		s3.push(n); // ���ÿ� Ǫ��
	}
	s2 = s3;
	cout << "s2������ ��� ���Ҹ� ���Ͽ� ����Ѵ�>> ";
	while (s2.length() != 0) {
		cout << s2.pop() << ' '; // ���ÿ��� ��
	}
	return 0;
}