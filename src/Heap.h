/*
Student Name : Rey Baltar
Student ID : hrb217
Compiler used : Eclipse using MinGW
Program description:
	This program allows the user to interact with a command line interface so that the user
	can add and make modifications to a patient queue simulator for a
	hospital.
*/

#ifndef HEAP_H_
#define HEAP_H_

#include<iostream>
#include<vector>

using namespace std;


class Patient{
private:
	string priority;
	string complaint;
public:
	string first;
	string last;
	vector<string> symptoms;
	int ticket;

	Patient():ticket(0){}
	Patient(string first, string last, int ticket): priority("ambulatory"), complaint(""), first(first), last(last), ticket(ticket){}
	friend ostream & operator<<(ostream&os, Patient&rhs);
	bool operator<(const Patient&P);
	string get_priority() const;
	string get_complaint() const;
	void set_priority(string level);
	void set_complaint(string text);

};

class Heap {
private:
	vector<Patient> array;

public:
	//int size;

	Heap(){}
	void peak(ostream &os);
	Patient pop();
	void insert(Patient P);
	int size();

};



#endif /* HEAP_H_ */
