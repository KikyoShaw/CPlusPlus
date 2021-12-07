#include <iostream>

#include "Polymorphism.h"

using namespace std;

int main()
{
	Tiger tiger;
	Animal* pAn = &tiger;
	pAn->sleep();
	pAn->eat();

	system("pause");

	return 0;
}

