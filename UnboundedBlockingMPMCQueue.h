#ifndef thread_queue_
#define thread_queue_

#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>
#include <iostream>

template <typename T> 
class UnboundedBlockingMPMCQueue
{
private:
  std::vector<T> buffer;
  std::mutex buffer_mutex;
  std::condition_variable buffer_size_condition;
public:

  void Push(T value){
    std::unique_lock<std::mutex> lock(buffer_mutex);
    buffer.push_back(std::move(value));
    buffer_size_condition.notify_one();
  }

  T Take(){
    std::unique_lock<std::mutex> lock(buffer_mutex);
    while(buffer.empty()){
      buffer_size_condition.wait(lock);
    }

    T result = std::move(buffer.back());
    buffer.pop_back();
    return result;
  }

};

#endif