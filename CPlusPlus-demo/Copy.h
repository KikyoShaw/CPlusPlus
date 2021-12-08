#pragma once

#include <iostream>
#include <string.h>

using namespace std;

class Student
{
public:
	Student();
	//Student(const Student& stu);
	/*Student& operator =(const Student& stu);*/
	~Student();

private:
	char* name = nullptr;
	//shared_ptr<char> name;
};

Student::Student()
{
	cout << "Student Creat..." << endl;
	if (nullptr == name) {
		name = new char[10];
	}
}

//Student::Student(const Student& stu)
//{
//	cout << "Student custom Creat..." << endl;
//	name = new char[strlen(stu.name) + 1];
//	int lenth = sizeof(stu.name) - 1;
//	strncpy(name, stu.name, lenth);
//	name[lenth] = '\0';
//}

//Student& Student::operator=(const Student& stu)
//{
//	if (this == &stu)
//		return *this;
//
//	cout << "Student operator Creat..." << endl;
//
//	delete[]name;
//	name = nullptr;
//	name = new char[strlen(stu.name) + 1];
//	int lenth = sizeof(stu.name) - 1;
//	strncpy(name, stu.name, lenth);
//	name[lenth] = '\0';
//	return *this;
//}

Student::~Student()
{
	cout << "Student Delete..." << endl;
	delete[]name;
	name = nullptr;
}