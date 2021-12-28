#pragma once

#include <string>
using namespace std;

//蛮力匹配
int BruteForce(const string& s1, const string& s2);

//BM算法
int BoyerMoore(const string& s1, const string& s2);

//RK算法
int RobinKarp(const string& s1, const string& s2);

//KMP算法
int KnuthMorrisPratt(const string& s1, const string& s2);