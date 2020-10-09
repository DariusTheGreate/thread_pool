#ifndef thread_queue_
#define thread_queue_

#include <mutex>
#include <queue>

template <typename T> 
class thread_queue
{
private:
  std::queue<T> t_queue;
  std::mutex t_mutex;
public:
  bool empty() {
    std::unique_lock<std::mutex> lock(t_mutex);
    return t_queue.empty();
  }
  
  int size() {
    std::unique_lock<std::mutex> lock(t_mutex);
    return t_queue.size();
  }

  void enqueue(T& t) {
    std::unique_lock<std::mutex> lock(t_mutex);
    t_queue.push(t);
  }
  
  T& dequeue() {
    std::unique_lock<std::mutex> lock(t_mutex);
    return t_queue.front();
    
  }
};

#endif