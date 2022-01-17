#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include "courseName.h"

using namespace std;

class Course {
    //** You may not change the declarations in this private: area.
    CourseName name;           ///< Name of the course
    int numberOfPrerequisites; ///< How many prereqs are currently in the array?
    int maxPrerequisites;      ///< How many prereqs will fit into the array?
    CourseName * prereqs;      ///< Pointer to an array of course names.
public:

	// default constructor (jrich)
	Course();


	/**
	 * Create a new course named cname and having no
	 * known prerequisites;
	 */
	Course (const CourseName& cname);


	// copy constructor (jrich)
	Course(const Course& c);

	//move constructor
	Course(Course&& c);

	// destructor (jrich)
	~Course();

	/**
	 * @return the name of the course
	 */
	CourseName getName() const {return name;}

	/**
	 * @return the number of known prerequisites to this course.
	 */
	int getNumberOfPrereqs() const;

	/**
	 * Adds cname to the list of prerequisites for this course.
	 * If this name is already in the list, this has no effect.
	 *
	 * @param cname name of a prerequisite course
	 */
	void addPrereq(const CourseName& cname);

	/**
	 * Removes cname from the list of prerequisites for this course.
	 * If this name is not in the list, this has no effect.
	 *
	 * @param cname name of a prerequisite course
	 */
	void removePrereq(const CourseName& cname);

	/**
	 * Get the name of the i_th prerequisite.
	 *
	 * @precondition 0 <= i && i < getNumberofPrereqs()
	 * @param i index of the prerequisite to retrieve
	 * @return name of the prerequisite course
	 */
	CourseName getPrereq(int i) const;

	// equality operator overloaded (jrich)
	bool  operator==(const Course& rhs) const;

	// assignment operator overload (jrich)
	Course& operator=(const Course& rhs);

	// move assignment operator overload (jrich)
	Course& operator=(Course&& c);

	// less than operator< overload (jrich)
	bool operator<(const Course& c) const;



private:
	friend std::ostream& operator<< (std::ostream& out, const Course& c);
};

// output stream overload (jrich)
std::ostream& operator<< (std::ostream& out, const Course& c);



#endif
