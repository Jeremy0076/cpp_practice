#include<iostream>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;

// unique_ptr
template<class T>
class Unique_Ptr{
private:
	T *_ptr;
public:
	Unique_Ptr(T *ptr = nullptr)
			: _ptr(ptr)
	{}
	~Unique_Ptr(){
		if(_ptr){
			delete = _ptr;
		}
	}

	Unique_Ptr<T>& operator=(const Unique_Ptr<T>& ap) = delete;
	Unique_Ptr(Unique_Ptr<T>& ap) = delete;

	// Move constructor
	Unique_Ptr(Unique_Ptr &&p) noexcept: _ptr(p._ptr) {
		p._ptr = nullptr;
	}

	T* operator->() const noexcept {return _ptr; }

	T& operator*() const noexcept {return *_ptr; }

	T* release() noexcept {
		T *res = _ptr;
		_ptr = nullptr;
		return res;
	}

	void reset(T *P = nullptr) noexcept {
		std::swap(_ptr, p);
		delete p;
	}

	// Move assignment operator 移动赋值运算符
	Unique_Ptr& operator=(Unique_Ptr &&p) noexcept {
		reset(p.release());
		return *this;
	}
};

// shared_ptr
template<class T>
class Shared_Ptr{
private:
	T * _ptr;
	int* _count;
	mutex* _pmtx;
public:
	Shared_Ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _count(new int(1))
			, _pmtx(new mutex)
	{}

	Shared_Ptr(Shared_Ptr<T>& ap)
		:_ptr(ap._ptr)
		, _count(ap._count)
		, _pmtx(ap._pmtx)
	{
		Add();
	}

	void Add(){
		_pmtx->lock();
		++(*_count);
		_pmtx->unlock();
	}

	void Release(){
		bool flag = false;
		_pmtx->lock();
		if(--(*_count) == 0){
			delete _ptr;
			delete _count;
			flag = true;
		}
		_pmtx->unlock();
		if(flag == true)
				delete _pmtx;
	}

	Shared_Ptr<T>& operator=(Shared_Ptr<T>& ap){
		if (_ptr != ap._ptr){
			Release();
			_ptr = ap._ptr;
			_count = ap._count;
			Add();
		}
		return *this;
	}

	T& operator*(){
		return *_ptr;
	}

	T* operator->(){
		return _ptr;
	}

	~Shared_Ptr(){
		Release();
	}
}

int main(){

	return 0;
}