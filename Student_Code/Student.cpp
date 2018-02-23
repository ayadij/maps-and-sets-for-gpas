#include "Student.h"


Student::Student(unsigned long long int ID, string name, string address, string phone)
{
	this->ID = ID;
	this->name = name;
	this->address = address;
	this->phone = phone;
	GPA = 0;
}
Student::~Student() {}


/* getID()
 * Returns the ID of the Student.*/
unsigned long long int Student::getID(){
	return ID;
}


/* getName()
 * Returns the name of the Student*/
string Student::getName(){
	return name;
}


/* getGPA()
 * Returns the string representation of the Student's GPA. */
string Student::getGPA(){
	stringstream ssgpa;
	ssgpa << fixed << setprecision(2) << GPA;
	return ssgpa.str();
}


/* addGPA()
 * Incorporates the given course grade into the Student's overall GPA.*/
void Student::addGPA(double classGrade){
	++totalcourses;
	totalGPA += classGrade;
	GPA = totalGPA/totalcourses;
}


/* toString()
 * The student object will be put into string representation. Student info will be
 * ordered ID, name, address, phone number, and GPA. Each piece of information will
 * be on its own line. GPA will not have a newline following it and the precision
 * of the GPA will be rounded to two decimal places. For example,
	 * 123456789
	 * Ben Thompson
	 * 17 Russell St, Provo, UT 84606
	 * 555-555-5555
	 * 3.12
 * Returns a string representation of the student object There is no trailing new line. */
string Student::toString(){
	stringstream ssts;
	ssts << ID << endl << name << endl << address << endl << phone << endl << fixed << setprecision(2) << GPA;
	return ssts.str();
}

