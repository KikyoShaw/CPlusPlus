#pragma once

#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class String
{
public:
	//构造函数
	String(const char *str = nullptr);
	//析构函数
	~String();
	//拷贝构造函数
	String(const String &other);
	////赋值函数
	//String & operater=(const String &rhs);

private:
	char *m_data = nullptr;
};

String::String(const char* str = nullptr)
{
	if (nullptr == str) {
		m_data = new char[1];
		m_data = '\0';
	}
	else {
		m_data = new char[strlen(str) + 1];
		int lenth = sizeof(str) - 1;
		strncpy(m_data, str, lenth);
		m_data[lenth] = '\0';
	}
}

String::~String()
{
	delete []m_data;
}

String::String(const String& other)
{
	m_data = new char[strlen(other.m_data) + 1];
	int lenth = sizeof(other.m_data) - 1;
	strncpy(m_data, other.m_data, lenth);
	m_data[lenth] = '\0';
}

//String::String & operater = (const String& rhs)
//{
//	if (this == &rhs)
//		return this;
//
//	delete []m_data;
//	m_data = new char[strlen(rhs.m_data) + 1];
//	int lenth = sizeof(rhs.m_data) - 1;
//	strncpy(m_data, rhs.m_data, lenth);
//	m_data[lenth] = '\0';
//	return *this;
//}
