#include<iostream>
using namespace std;

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
	virtual product* CreateObj() = 0;
};

class fatorya: public factory{
public:
	virtual product* CreateObj(){
		return new producta();
	}
};

class fatoryb: public factory{
public:
	virtual product* CreateObj(){
		return new productb();
	}
};

int main(){
	// cout<<"1"<<endl;

	factory* fya = new fatorya();
	product* fa = fya->CreateObj();
	fa->show();

	factory* fyb = new fatoryb();
	product* fb = fyb->CreateObj();
	fb->show();

	return 0;
}