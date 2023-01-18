#pragma once

template<class T>
struct Node
{
	T data;
	Node<T>* next;

	Node(T value, Node* nextptr = NULL) :data(value), next(nextptr) {}
};

template<class T>
class Queue
{
private:
	Node<T>* head;
	Node<T>* top;
	int length;
public:
	Queue() :head(NULL), top(NULL), length(0) {}
	void enqueue(T value);
	T dequeue();
	int GetLength() { return length; }
	~Queue();
};

template<class T>
void Queue<T>::enqueue(T value)
{
	Node<T>* current = new Node<T>(value);
	if (length == 0)
		head = top = current;
	else
	{
		top->next = current;
		top = top->next;
	}
	length++;
}

template<class T>
T Queue<T>::dequeue()
{
	T value = head->data;
	Node<T>* current = head;
	head = head->next;
	delete current;
	this->length--;
	return value;
}

template<class T>
Queue<T>::~Queue()
{
	while (this->length != 0) this->dequeue();
	head = top = NULL;
}

template<class T>
struct PQNode
{
	T data;
	int priority;
	PQNode<T>* next;

	PQNode(T value, int priorityValue, PQNode<T>* nextptr = NULL) :data(value), priority(priorityValue), next(nextptr) {}
};

template<class T>
class PriorityQueue
{
private:
	PQNode<T>* top;
	int length;
public:
	PriorityQueue() : top(NULL), length(0) {}
	void push(T value, int priority);
	T pop();
	int GetLength() { return this->length; }
	~PriorityQueue();
};

template<class T>
void PriorityQueue<T>::push(T value, int priority)
{
	if (this->top == NULL)
	{
		this->top = new PQNode<T>(value, priority);
	}
	else
	{
		PQNode<T>* newNode = new PQNode<T>(value, priority);
		PQNode<T>* previous = NULL;
		PQNode<T>* current = this->top;
		while (current && newNode->priority >= current->priority)
		{
			previous = current;
			current = current->next;
		}
		if (previous == NULL)
		{
			newNode->next = this->top;
			this->top = newNode;
		}
		else
		{
			newNode->next = current;
			previous->next = newNode;
		}
	}
	this->length++;
}

template<class T>
T PriorityQueue<T>::pop()
{
	if (this->length == 0) std::cout << "Queue is empty!" << std::endl;
	else
	{
		T value = this->top->data;
		PQNode<T>* current = this->top;
		this->top = this->top->next;
		delete current;
		this->length--;
		return value;
	}
}

template<class T>
PriorityQueue<T>::~PriorityQueue()
{
	while (this->length > 0) this->pop();
}