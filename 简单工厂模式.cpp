#include<iostream>
#include<string>
using namespace std;

enum {
	typea,
	typeb
};

class product{
public:
	virtual void show() = 0;
};

class producta: public product{
public:
	virtual void show(){
		cout<<"product a"<<endl;
	}
};

class productb: public product{
public:
	virtual void show(){
		cout<<"product b"<<endl;
	}
};

class factory{
public:
	static product* CreateObj(int type){
		switch(type){
			case typea:
				return new producta();
			case typeb:
				return new productb();
			default:
				break;
		}
		return nullptr;
	}
};

int main(){
	// cout<<typeb<<endl;

	factory* fy = new factory();

	product* fa = fy->CreateObj(typea);
	product* fb = fy->CreateObj(typeb);
	fa->show();
	fb->show();

	return 0;
}

