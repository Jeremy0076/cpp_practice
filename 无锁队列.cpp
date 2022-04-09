#include<iostream>
using namespace std;

// 参考 https://www.cnblogs.com/catch/p/3164829.html

/* 伪代码

cas c++11 atomic 

inline bool atomic_compare_exchange(
   _Inout_ int * _Dest,
   _Inout_ int * _Expected_value,
   int _Value
) restrict(amp);

inline bool atomic_compare_exchange(
   _Inout_ unsigned int * _Dest,
   _Inout_ unsigned int * _Expected_value,
   unsigned int _Value
) restrict(amp);

*/


// new 改 tls


struct Node{
	Node* nxt;
	void* data;
};

static Node* tail = nullptr;
static Node* head = nullptr;

Enqueue(x){
	q = new tlsNode();
	q.data = x;
	q.nxt = nullptr;

	do{
		p = tail;

	}while(cas(p.nxt, nullptr, q) == false)

	cas(tail, p, q);
}

Dequeue(){
	do{
		p = head;
		if(p.nxt == nullptr)
			return nullptr;

	}while(cas(head, p, p.nxt) == false);

	return p.nxt.data;
}

int main(){

	return 0;
}


