#include <iostream>
using namespace std;

class BaseArray {
protected:
	int capacity; // 동적 할당된 메모리 용량
	int *mem;
public:
	BaseArray(int capacity = 100) {
		cout << "Basearray 인자있는 생성자" << endl;
		this->capacity = capacity; mem = new int[capacity];
	}
	BaseArray(const BaseArray& b) {
		cout << "Basearray 복사 생성자" << endl;
		capacity = b.capacity;
		mem = new int[b.capacity];
		for (int i = 0; i< capacity; i++)
		{
			mem[i] = b.mem[i];
		}
	}
	BaseArray& operator=(const BaseArray& other) {
		cout << "BaseArray 대입연산자 오버로딩" << endl;
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
		cout << "BaseArray 소멸자" << endl;
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
	int size; // 현재 큐 안에 있는 데이터의 개수
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
	cout << "Queue 인자있는 생성자" << endl;
	head = 0; // 삽입할 위치는 head
	tail = -1;  // tail+1 위치에서 꺼내기
	size = 0; // 초기 개수는 0
}
MyQueue::MyQueue(const MyQueue& m)
	: BaseArray(m) {
	cout << "Queue 복사생성자" << endl;
	head = m.head;
	tail = m.tail;
	size = m.size;
}
MyQueue::~MyQueue()
{
	cout << "Queue 소멸자" << endl;
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
	int tos; // 다음에 push 할 위치. 스택에 들어있는 개수와 동일
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
	cout << "Stack 인자있는 생성자" << endl;
	tos = 0; // tos는 현재 스택에 들어 있는 개수로 다루어져도 된다.
}
MyStack::MyStack(const MyStack& m)
	: BaseArray(m)
{
	cout << "Stack 복사 생성자" << endl;
	tos = m.tos;
}
MyStack::~MyStack() {
	cout << "Stack 소멸자" << endl;
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
	cout << "큐에 삽입할 5개의 정수를 입력하라>> ";
	for (int i = 0; i<5; i++) {
		cin >> n;
		mQ.enqueue(n); // 큐에 삽입
	}
	cout << "큐의 용량:" << mQ.getCapacity() << ", 큐의 크기:" << mQ.length() << endl;
	cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
	while (mQ.length() != 0) {
		cout << mQ.dequeue() << ' '; // 큐에서 제거하여 출력
	}
	cout << endl << "큐의 현재 크기 : " << mQ.length() << endl;
	MyQueue q2(mQ);
	cout << "큐에 삽입할 3개의 정수를 입력하라>> ";
	for (int i = 0; i<3; i++) {
		cin >> n;
		q2.enqueue(n); // 큐에 삽입
	}
	cout << "큐의 용량:" << q2.getCapacity() << ", 큐의 크기:" << mQ.length() << endl;
	cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
	while (q2.length() != 0) {
		cout << q2.dequeue() << ' '; // 큐에서 제거하여 출력
	}
	cout << endl << "큐의 현재 크기 : " << q2.length() << endl;
	//Stack
	MyStack mStack(100);
	cout << "스택에 삽입할 5개의 정수를 입력하라>> ";
	for (int i = 0; i<5; i++) {
		cin >> n;
		mStack.push(n); // 스택에 푸시
	}
	cout << "스택 용량:" << mStack.getCapacity() << ", 스택 크기:" << mStack.length() << endl;
	cout << "스택의 모든 원소를 팝하여 출력한다>> ";
	while (mStack.length() != 0) {
		cout << mStack.pop() << ' '; // 스택에서 팝
	}
	cout << endl << "스택의 현재 크기 : " << mStack.length() << endl;

	MyStack s2(mStack);
	MyStack s3(10);
	cout << "s3 스택에 삽입할 3개의 정수를 입력하라>> ";
	for (int i = 0; i<3; i++) {
		cin >> n;
		s3.push(n); // 스택에 푸시
	}
	s2 = s3;
	cout << "s2스택의 모든 원소를 팝하여 출력한다>> ";
	while (s2.length() != 0) {
		cout << s2.pop() << ' '; // 스택에서 팝
	}
	return 0;
}