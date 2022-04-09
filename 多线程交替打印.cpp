// #include<iostream>
// #include<thread>
// #include<mutex>
// #include<condition_variable>
// #include<string>
// using namespace std;

// std::mutex mtx;
// std::condition_variable var;
// bool flag = true;
// char arr[] = "HELLO WORLD";

// // 线程交替打印字符串
// void func1(){
// 	unique_lock<mutex> lock(mtx);
// 	for(int i = 0; i<11; i+=2){
// 		var.wait(lock, []{return flag;});
// 		cout<<"thread1 | "<<arr[i]<<endl;
// 		flag = false;
// 		var.notify_one();
// 	}
// }

// void func2(){
// 	unique_lock<mutex> lock(mtx);
// 	for(int i = 1; i<11; i+=2){
// 		var.wait(lock, []{return !flag;});
// 		cout<<"thread2 | "<<arr[i]<<endl;
// 		flag = true;
// 		var.notify_one();
// 	}
// }

// int main(){
// 	thread t1(func1);
// 	thread t2(func2);
// 	t1.join();
// 	t2.join();

// 	cout<<"task finish!"<<endl;
// 	return 0;
// }

#include<iostream>
#include<pthread.h>
#include<stdlib.h>
using namespace std;

pthread_mutex_t lock;
pthread_cond_t cond;
char arr[] = "hello world";
int flag = 1;

void* fun1(void* arg)
{
	for (int i = 0; i < 12; i += 3)
	{
		pthread_mutex_lock(&lock);
		while (flag != 1)
		{
			pthread_cond_wait(&cond, &lock);
		}
		cout << "i am thread1 :" << arr[i] << endl;
		flag = 2;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
}

void* fun2(void* arg)
{
	for (int i = 1; i < 12; i += 3)
	{
		pthread_mutex_lock(&lock);
		while (flag != 2)
		{
			pthread_cond_wait(&cond, &lock);
		}
		cout << "i am thread2 :" << arr[i] << endl;
		flag = 3;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
}

void* fun3(void* arg)
{
	for (int i = 2; i < 12; i += 3)
	{
		pthread_mutex_lock(&lock);
		while (flag != 3)
		{
			pthread_cond_wait(&cond, &lock);
		}
		cout << "i am thread3 :" << arr[i] << endl;
		flag = 1;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
}

int main(){
	pthread_t t1, t2, t3;
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_create(&t1, NULL, fun1, NULL);
	pthread_create(&t2, NULL, fun2, NULL);
	pthread_create(&t3, NULL, fun3, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);


	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);
	return 0;
}

