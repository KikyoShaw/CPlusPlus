#include <iostream>
#include "Polymorphism.h"
#include "Copy.h"

using namespace std;

int main()
{
	/*
	*  ��̬&&�麯��&&���麯�� ʾ��
	*/
	#pragma region Polymorphism
	//Animal* pAn = new Tiger();
	//pAn->eat();
	//cout << sizeof(Animal) << endl;
	//Animal animal;
	//Animal* pAn = new Animal();
	//Tiger tiger;
	//Animal* pAn = &tiger;
	//pAn->run();
	//delete pAn;
	//pAn = nullptr;
	#pragma endregion

	/*
	*  ���&&ǳ���� ʾ��
	*/
	#pragma region Copy

	Student s1;
	Student s2;

	s1 = s2;

	#pragma endregion

	system("pause");

	return 0;
}

