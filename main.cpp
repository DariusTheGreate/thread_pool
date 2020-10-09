#include "thread_queue.h"
#include <iostream>

void main()
{
	thread_queue<int> q;
	int item = 5;
	q.enqueue(item);
	q.enqueue(item);
	q.enqueue(item);
	q.enqueue(item);
	std:: cout << q.dequeue(); 
}