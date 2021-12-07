#pragma once

#include <iostream>

using namespace std;

class Animal
{
public:
	Animal(){ /*cout << "Animal Create..." << endl;*/ }
	~Animal(){ /*cout << "Animal Delete..." << endl;*/ }


	/*
	* 编译器为每个类的对象提供一个虚表指针，这个指针指向对象所属类的虚表。在程序运行时，根据对象的类型去初始化vptr，
	* 从而让vptr正确的指向所属类的虚表，从而在调用虚函数时，就能够找到正确的函数。
	* 由于pAn实际指向的对象类型是Tiger，因此vptr指向的Tiger类的vtable，当调用pAn->breathe()时，
	*根据虚表中的函数地址找到的就是Tiger类的breathe()函数。
	*正是由于每个对象调用的虚函数都是通过虚表指针来索引的，也就决定了虚表指针的正确初始化是非常重要的。
	*换句话说，在虚表指针没有正确初始化之前，我们不能够去调用虚函数。那么虚表指针在什么时候，或者说在什么地方初始化呢？
	*答案是在构造函数中进行虚表的创建和虚表指针的初始化。还记得构造函数的调用顺序吗，
	*在构造子类对象时，要先调用父类的构造函数，此时编译器只“看到了”父类，
	*并不知道后面是否后还有继承者，它初始化父类对象的虚表指针，该虚表指针指向父类的虚表。
	*当执行子类的构造函数时，子类对象的虚表指针被初始化，指向自身的虚表。
	*/
	virtual void sleep() { cout << "Animal sleep..." << endl; }

	virtual void run(){}

	/*
	* 1.从编译者角度来说
	* C++编译器在编译的时候，要确定每个对象调用的函数的地址，这称为早期绑定（early binding），
	* 当我们将Tiger类的对象fh的地址赋给pAn时，C++编译器进行了类型转换，此时C++编译器认为变量pAn保存的就是animal对象的地址。
	* 当在main()函数中执行pAn->breathe()时，调用的当然就是animal对象的breathe函数。
	* 2.内存模型的角度
	* 我们构造Tiger类的对象时，首先要调用animal类的构造函数去构造animal类的对象，然后才调用Tiger类的构造函数完成自身部分的构造，
	* 从而拼接出一个完整的Tiger对象。当我们将Tiger类的对象转换为animal类型时，该对象就被认为是原对象整个内存模型的上半部分，
	* 那么当我们利用类型转换后的对象指针去调用它的方法时，当然也就是调用它所在的内存中的方法。因此，输出animal breathe，也就顺理成章了
	*/
	void eat() { cout << "Animal eat..." << endl; }

private:

};

class Tiger : public Animal
{
public:
	Tiger(){ /*cout << "Tiger Create..." << endl;*/ }
	~Tiger(){ /*cout << "Tiger Delete..." << endl;*/ }

	void sleep() { cout << "Tiger sleep..." << endl; }

	void eat() { cout << "Tiger eat..." << endl; }

private:

};