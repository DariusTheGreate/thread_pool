#include <stdio.h>

#include <pthread.h>

#include <stdlib.h>
#include <unistd.h>
#include <vector>

typedef void* (*fptr)(void*);

typedef struct Queue_r{
	std::vector<fptr> work;
	pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cv;
} Queue;

Queue* construct_queue(){
	Queue* res = (Queue*)malloc(sizeof(Queue));
	return res;
}

void queue_push(Queue* q, fptr work_in){
	pthread_mutex_lock(&(q -> queue_mutex));
	q->work.push_back(work_in);
	printf("added");
	pthread_cond_signal(&(q->cv));
	pthread_mutex_unlock(&(q -> queue_mutex));
}

fptr queue_get(Queue* q){
	pthread_mutex_lock(&(q -> queue_mutex));
	while(q -> work.size() == 0)
		pthread_cond_wait(&(q->cv), &(q -> queue_mutex));
	auto ret = q->work.back();
	q->work.pop_back();
	pthread_mutex_unlock(&(q -> queue_mutex));
	return ret;
}


typedef struct ThreadPool_r{
	//func pointers queue
	//thread array
	
	std::vector<pthread_t*> workers;
	Queue* q;
} ThreadPool;


fptr get_task(Queue* q){
	//while(true){
		//printf("%d \n", q -> work.size());
		fptr task = queue_get(q);
		//if(!task)
		//	break;
		return task;
	//}	
	//abort();
}


ThreadPool* pool_construct(size_t count, Queue* q){
	ThreadPool* res = (ThreadPool*)malloc(sizeof(ThreadPool));
	res -> q = construct_queue();
	for(size_t i = 0; i < count; ++i){
		pthread_t* thread = (pthread_t*)malloc(sizeof(thread));
		int res_t = pthread_create(thread, NULL, get_task(q), NULL);
		res -> workers.emplace_back(thread);
		//pthread_join(*thread, NULL);
	}
	return res;
}

void pool_join(ThreadPool* p){
	for(size_t i = 0; i < p->workers.size(); ++i){
		pthread_join(*(p->workers[i]), NULL);
	}
}

void pool_submit(ThreadPool* pool, fptr work){
	queue_push(pool->q, work);
}

static int state = 0;

void* worker(void*){
	for(size_t i = 0; i < 1000000000; ++i){
		//printf("%d\n", i);
		state++;
		//sleep(1000);
	}
	return NULL;
}



int main(){
	printf("start\n");
	Queue* que = construct_queue();
	printf("push\n");
	queue_push(que, &worker);
	queue_push(que, &worker);
	queue_push(que, &worker);
	ThreadPool* pool = pool_construct(3, que);
	pool_submit(pool, &worker);
	
	pool_join(pool);	
	printf("\n%d", state);
	return 0;
}
