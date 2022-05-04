#include "UnboundedBlockingMPMCQueue.h"
#include "ThreadPool.h"
#include <iostream>
#include <thread>

#include <functional>

static int state = 0;

int main()
{
    ThreadPool tp(6); 
    tp.Submit([](){std::cout << "ima hui\n"; });
    
    int as = 125;
    int bs = 6;
    auto res_future = tp.Submit([](int a, int b){ return a - b; }, as, bs);
    std::cout << res_future.get();

	return 0;
}
