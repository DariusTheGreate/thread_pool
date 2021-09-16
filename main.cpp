#include "UnboundedBlockingMPMCQueue.h"
#include "ThreadPool.h"
#include <iostream>
#include <thread>

#include <functional>

static int state = 0;

int main()
{
	ThreadPool tp(6);
	for(int i = 0; i < 1000000; ++i){
		tp.Submit([&]{
			state++;
		});
	}
	std::cout << state;	
	tp.Join();
	return 0;
}