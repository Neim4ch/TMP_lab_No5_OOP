#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <utility>
using namespace std;

class film {
	string name;
public:
	string country;

	// ?????????????, ?????????? ? ???? ?????? ?? ??????
	static film* In(ifstream& ifst);
	virtual void InData(ifstream& ifst) = 0; // ????
	virtual void Out(ofstream& ofst) = 0; // ?????
	int countVowels(); // ??????? 
	void OutName(ofstream& ofst);
	bool cmp(film& f);
	virtual void OutFeature(ofstream& ofst);
};

class Node {
public:
	film* pic;
	Node* next;
	Node(film* newfigure);
};

class feature : public film {
	string director; // ???????
public:
	void InData(ifstream& ifst);
	void Out(ofstream& ofst); 
	void OutFeature(ofstream& ofst);
	feature() {}
};

class animation : public film {
	enum way { DRAWN, DOLL, STOP_MOTION };// ?????? ????????
	way woc;//?????? ????????
public:
	// ?????????????? ????????? ??????
	void InData(ifstream& ifst); // ????
	void Out(ofstream& ofst); // ?????
	
	//void OutFeature(ofstream& ofst);
	animation() {}
};

class documentary : public film {
	int year;
public:
	void InData(ifstream& ifst);
	void Out(ofstream& ofst);

	documentary() {}
};

class container {
public:
	Node* head;
	Node* curr;
	int size;

	void In(ifstream& ifst); 
	void Out(ofstream& ofst);
	void OutFeature(ofstream& ofst); 
	void OutCntVowels(ofstream& ofst);
	void Clear();
	void Sort();
	container(); 
	~container() { Clear(); } 
};

bool fileCheck(ifstream& ifst);
