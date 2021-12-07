#include <iostream>

#include "Polymorphism.h"

using namespace std;

int main()
{
	//Animal* pAn = new Tiger();
	//pAn->eat();
	//cout << sizeof(Animal) << endl;
	//Animal animal;
	Animal* pAn = new Animal();
	Tiger tiger;
	Animal* pAn = &tiger;
	pAn->run();



	//delete pAn;
	//pAn = nullptr;

	system("pause");

	return 0;
}

