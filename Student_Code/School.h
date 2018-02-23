#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GPAInterface.h"

class School : public GPAInterface
{
protected:

	map<unsigned long long int, StudentInterface*> StudentMap;
	set<StudentInterface*, Comparator> StudentSet;

public:

	School();
	~School();

	virtual map<unsigned long long int, StudentInterface*> getMap();
	virtual set<StudentInterface*, Comparator> getSet();
	virtual bool importStudents(string mapFileName, string setFileName);
	virtual bool importGrades(string fileName);
	virtual string queryMap(string fileName);
	virtual string querySet(string fileName);
	virtual void clear();

};

