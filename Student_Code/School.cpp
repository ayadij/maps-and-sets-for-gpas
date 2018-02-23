#include "School.h"
#include "Student.h"

School::School() : GPAInterface() {}
School::~School() {clear();}

///create a function that converts a string into an ulli using string stream i think?
unsigned long long int IDconverter(string stringID){
	unsigned long long int ID;
	stringstream IDconvert(stringID);
	IDconvert >> ID;
	return ID;
}


/* getMap()
 * Returns the map storing the student information.
 * The key of the map should be the student ID. */
map<unsigned long long int, StudentInterface*> School::getMap(){
	return StudentMap;
}


/* getSet()
 * Returns the set storing the student information.*/
set<StudentInterface*,Comparator> School::getSet(){
	return StudentSet;
}


/* importStudents()
 * Read in and parse through the given files. Each part of an entry in a
 * file is given on a separate line in the file. Student ID is first, name is
 * second, address is third, and phone is last. There are no blank lines between
 * students. The following is an example file:
	 *	 5291738600
	 * 	 Dick B. Smith
	 * 	 879 Maple Road, Centralia, Colorado 24222
	 * 	 312-000-1000
	 * 	 9251738707
	 *	 Harry C. Anderson
	 *	 635 Main Drive, Midville, California 48444
	 * 	 660-050-2200
 * If a valid file is given, the new Students should be added to the existing
 * map and set.
 * If an invalid file name is given or if there is a missing entry for a student,
 * return false. Duplicate student ID numbers and duplicate students will not be
 * tested for. There will never be a student that exists in the map and set. If
 * the function returns false, then no changes should have been made to the
 * existing map or set.
 * The key of the map should be the student ID.
 * Returns false if an invalid filename is given or if there is a missing entry for a
 * student, otherwise true.*/
bool School::importStudents(string mapFileName, string setFileName){
	/*/open a file (declaired by the testdriver)
	//check if the file exists
	//check if lines in file are valid, parse through files using getline
	//by seeing if the number of lines is divisible by 4 		if (count %4 != 0);
		//if the file is invalid --- make no changes to the map/set and return false
		//if the file is valid --- add students to existing map and set*/
	ifstream mapfiles(mapFileName);
	ifstream setfiles(setFileName);

	if (!mapfiles || !setfiles) {
		return false;
	}

		///counts the # of lines in the map file
		string line;
		int linecount = 0;
		while (getline(mapfiles, line) ){
			linecount++;
		}
		if (linecount %4 != 0){
			return false;
		}
		mapfiles.close();

		///counts the # of lines in the set file
		line.clear();
		linecount = 0;
		while (getline(setfiles, line) ){
			linecount++;
		}
		if (linecount %4 != 0){
			return false;
		}
		setfiles.close();

		//reopen valid files
		mapfiles.open(mapFileName.c_str());
		setfiles.open(setFileName.c_str());

		string stringID;
		string name;
		string address;
		string phone;
		while (getline(mapfiles, stringID)){
			getline(mapfiles, name);
			getline(mapfiles, address);
			getline(mapfiles, phone);
			unsigned long long int ID = IDconverter(stringID);
			StudentMap[ID] = new Student(ID, name, address, phone);
		}
		while (getline(setfiles, stringID)){
			getline(setfiles, name);
			getline(setfiles, address);
			getline(setfiles, phone);
			stringstream buffer(stringID);
			unsigned long long int ID;
			buffer >> ID;
			StudentInterface* newstudent = new Student (ID, name, address, phone);
			StudentSet.insert(newstudent);
		}
	return true;
}


/* importGrades()
 * Read in and parse through the given file. Each part of an entry in the file
 * is given on a separate line in the file. Student ID is first, course is
 * second, and grade is last. There are no blank lines between entries. The
 * following is an example file:
	 * 	5291738860
	 * 	CHEM134
	 * 	A
	 * 	9251734870
	 * 	BOT180
	 * 	B
	 * 	9251733870
	 * 	PE273
	 * 	D+
	 * 	5291738760
	 * 	HIS431
	 *  	A-
 * Compute the GPA by finding the average of all the grades with a matching student ID
 * in the Grade file. The GPA is calculated by taking a Student's total sum GPA and
 * dividing by the number of classes taken. If the given student ID has no matching
 * grades in the Grade file, the GPA is 0.00. It is not necessary to store the course
 * names so long as the total number of courses taken is counted.
 * You may assume that the given student ID exists in the map or set.
 * Use the following point values for each grade.
	 *		  A = 4.0  A- = 3.7
	 *	B+ = 3.4  B = 3.0  B- = 2.7
	 *	C+ = 2.4  C = 2.0  C- = 1.7
	 *	D+ = 1.4  D = 1.0  D- = 0.7
	 *		  E = 0.0
 * Returns false if an invalid filename is given, otherwise true. */
bool School::importGrades(string fileName){
	ifstream openfile;
	openfile.open(fileName.c_str());
	if(!openfile){
		return false;
	}
	string stringID;
	string course;
	string letter;
	double grade;
	while(getline(openfile, stringID)){

		getline(openfile, course);
		getline(openfile, letter);

		if(letter == "A"){grade = 4.0;}
		else if(letter == "A-"){grade = 3.7;}
		else if(letter == "B+"){grade = 3.4;}
		else if(letter == "B"){grade = 3.0;}
		else if(letter == "B-"){grade = 2.7;}
		else if(letter == "C+"){grade = 2.4;}
		else if(letter == "C"){grade = 2.0;}
		else if(letter == "C-"){grade = 1.7;}
		else if(letter == "D+"){grade = 1.4;}
		else if(letter == "D"){grade = 1.0;}
		else if(letter == "D-"){grade = 0.7;}
		else if(letter == "E"){grade = 0.0;}

		unsigned long long int ID = IDconverter(stringID);

		for(pair<unsigned long long int, StudentInterface*> student : StudentMap){
			if(ID == student.first){
				student.second->addGPA(grade);
			}
		}
		for(StudentInterface* student: StudentSet){
			if(ID == student->getID()){
				student->addGPA(grade);
			}
		}
	}
	return true;
}


/* querySet()
 * Read in and parse through the given file. The 'Query' file contains a list of
 * student ID numbers. Each entry in the Query file is a student ID given on a
 * line by itself. You are to compute and report the GPA for each of the students
 * listed in the Query file. The following is an example Query file
	 * 	5291738860
	 * 	9251733870
 * For each student ID given in the Query file, use the student information stored in
 * your set to compute the GPA for the student and create an output string which
 * contains the student ID, GPA, and name. If the given student ID does not match any
 * student, do not give any output for that student ID. Each line of the output string
 * contains student ID, GPA, and name as shown:
	 * 	5291738860 2.85 Dick B. Smith
	 *	9251733870 3.00 Harry C. Anderson
 * Return a string representation of the given query. If an invalid file name is given,
 * then return an empty string. The precision of the GPA will be rounded to two decimal places.
 * There will be a trailing new line. */
string School::queryMap(string fileName){
	ifstream qimport(fileName);
	if(!qimport){
		return "";
	}
	string stringID;
	stringstream output;
	while(getline(qimport, stringID)){
		unsigned long long int ID = IDconverter(stringID);
		for(pair<unsigned long long int, StudentInterface*> student : StudentMap){
			if (ID == student.first){
				output << ID << " " << fixed << setprecision(2) << student.second->getGPA()
						<< " " << student.second->getName() << endl;
			}
		}
	}
	return output.str();
}


string School::querySet(string fileName){
	ifstream qimport(fileName.c_str());
	if(!qimport){
		return "";
	}
	string stringID;
	string stringoutput;
	stringstream output;
	while (getline(qimport, stringID)){
		unsigned long long int ID = IDconverter(stringID);
		for(StudentInterface* student: StudentSet){
			if(ID == student->getID()){
				output << ID << " " << fixed << setprecision(2) << student->getGPA() << " " << student->getName() << endl;
			}
		}
	}
	return output.str();
}


/* Clears the students from the map and set. */
void School::clear()
{
	for(pair<unsigned long long int, StudentInterface*> student : StudentMap){
		delete student.second;
	}
	StudentMap.clear();

	for(StudentInterface* student: StudentSet){
		delete student;
	}
	StudentSet.clear();

/*	//iterate through map
		// delete students
	//mapfiles.clear(); ///or/// StudentMap.clear();?

	//iterate throug set
		//delete student.second;
	//setfiles.clear(); ///or/// StudentSet.clear();?*/
}

