#pragma once
#include <sstream>
#include <iostream>
#include <iomanip>
#include "StudentInterface.h"


class Student : public StudentInterface
{
protected:

	unsigned long long int ID;
	string name;
	string address;
	string phone;
	double GPA;
	double totalGPA = 0;
	int totalcourses = 0;

public:

	Student(unsigned long long int ID, string name, string address, string phone);
	virtual ~Student();

	virtual unsigned long long int getID();
	virtual string getName();
	virtual string getGPA();
	virtual void addGPA(double classGrade);
	virtual string toString();

};
