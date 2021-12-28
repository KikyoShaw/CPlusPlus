#pragma once

#include <string>
using namespace std;

//����ƥ��
int BruteForce(const string& s1, const string& s2);

//BM�㷨
int BoyerMoore(const string& s1, const string& s2);

//RK�㷨
int RobinKarp(const string& s1, const string& s2);

//KMP�㷨
int KnuthMorrisPratt(const string& s1, const string& s2);