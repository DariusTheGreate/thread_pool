#include "UnboundedBlockingMPMCQueue.h"
#include <functional>
#include <iostream>

class ThreadPool{
public:
	ThreadPool(const size_t& amount){
		initialize_workers(amount);
	}

	void Submit(std::function<void()> func){
		queue.Push(func);// move?
	}

	void Join(){
		for(auto& worker: workers){
			worker.join();
		}
	}

private:
	void initialize_workers(const size_t& amount){
		for(size_t i = 0; i < amount; ++i){
			workers.emplace_back([this]{
				get_task();
			});
		}
	}

	void get_task(){
		while(true){
			auto task = queue.Take();
			if(!task){ 
				break; 
			}
			task();// add exceptions handlers
		}
	}


private:
	UnboundedBlockingMPMCQueue<std::function<void()>> queue;
	std::vector<std::thread> workers;
};