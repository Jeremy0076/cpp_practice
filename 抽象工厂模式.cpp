#include<iostream>
#include<string>

using namespace std;


class dog {
public:
	virtual void show() = 0;
};

class dogA : public dog{
public:
	virtual void show()
	{
		cout << "dog A" << endl;
	}
};

class dogB : public dog{
public:
	virtual void show()
	{
		cout << "dog B" << endl;
	}
};


class cat {
public:
	virtual void show() = 0;
};

class catA : public cat{
public:
	virtual void show()
	{
		cout << "cat A" << endl;
	}
};

class catB : public cat{
public:
	virtual void show()
	{
		cout << "cat B" << endl;
	}
};



class Factory{
public:
	virtual dog* CreateDog() = 0;
	virtual cat* CreateCat() = 0;
};

class FactoryA : public Factory{
public:
	virtual dog* CreateDog()
	{
		return new dogA();
	}
	virtual cat* CreateCat()
	{
		return new catA();
	}
};

class FactoryB : public Factory{
public:
	virtual dog* CreateDog()
	{
		return new dogB();
	}
	virtual cat* CreateCat()
	{
		return new catB();
	}
};

int main()
{
	Factory* fya = new FactoryA();
	dog* da = fya->CreateDog();
	da->show();
	cat* ca = fya->CreateCat();
	ca->show();
	cout << endl;

	Factory* fyb = new FactoryB();
	dog* db = fyb->CreateDog();
	db->show();
	cat* cb = fyb->CreateCat();
	cb->show();


	return 0;
}
