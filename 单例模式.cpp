#include<iostream>
#include<mutex>
using namespace std;

std::mutex mtx;

class SingletonHungry
{
private:
	static SingletonHungry ins;
public:
	SingletonHungry();
	~SingletonHungry();
	static SingletonHungry* getins(){
		return &ins;
	}
};



class SingletonLazy
{
private: 
	static SingletonLazy* iny;
public:
	static SingletonLazy* getins(){
		if(iny == nullptr){
			mtx.lock();
			if(iny == nullptr){
				iny = new SingletonLazy();
			}
			mtx.unlock();
		}
		return iny;
	}
};


int main(){
	SingletonLazy* lz = SingletonLazy::getins();
	delete lz;
	return 0;
}