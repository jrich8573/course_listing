#include "course.h"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;


// default constructor (jrich)
Course::Course()
:name(), numberOfPrerequisites(0), maxPrerequisites(0), prereqs(nullptr)
{
}

/**
 * Create a new course named cname and having no
 * known prerequisites;
 */
Course::Course (const CourseName& cname)
: name(cname), numberOfPrerequisites(0), maxPrerequisites(10),
  prereqs(new CourseName[maxPrerequisites])
{

}

// copy constructor (jrich)
Course::Course(const Course& c)
    :name(c.name) ,numberOfPrerequisites(c.numberOfPrerequisites),
    maxPrerequisites(c.maxPrerequisites)
    // allocate an new array big enough to hold our data
    {
    prereqs = new CourseName[maxPrerequisites];
    for(int i = 0; i < numberOfPrerequisites; ++i)
        prereqs[i] = c.prereqs[i];
    }

// move constructor (jrich)
Course::Course(Course&& c)
:name(c.name), numberOfPrerequisites(c.numberOfPrerequisites),
 maxPrerequisites(c.maxPrerequisites), prereqs(c.prereqs)
{
    c.prereqs = nullptr;
}

// destructor (jrich)
Course::~Course(){
    delete [] prereqs;
}

/**
 * @return the number of known prerequisites to this course.
 */
int Course::getNumberOfPrereqs() const
{
    return numberOfPrerequisites;
}

/**
 * Adds cname to the list of prerequisites for this course.
 * If this name is already in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::addPrereq(const CourseName& cname)
{
    for (int i = 0; i < numberOfPrerequisites; ++i)
        if (prereqs[i] == cname)
            return;
    assert (numberOfPrerequisites < maxPrerequisites);
    prereqs[numberOfPrerequisites] = cname;
    ++numberOfPrerequisites;
}

/**
 * Removes cname from the list of prerequisites for this course.
 * If this name is not in the list, this has no effect.
 *
 * @param cname name of a prerequisite course
 */
void Course::removePrereq(const CourseName& cname)
{
    for (int i = 0; i < numberOfPrerequisites; ++i)
        if (prereqs[i] == cname)
        {
            for (int j = i+1; j < numberOfPrerequisites; ++j)
                prereqs[j-1] = prereqs[j];
            --numberOfPrerequisites;
            break;
        }
}

/**
 * Get the name of the i_th prerequisite.
 *
 * @precondition 0 <= i && i < getNumberofPrereqs()
 * @param i index of the prerequisite to retrieve
 * @return name of the prerequisite course
 */
CourseName Course::getPrereq(int i) const
{
    assert (i >= 0 && i < numberOfPrerequisites);
    return prereqs[i];
}

    // equality operator overloaded (jrich)
    bool Course::operator==(const Course& rhs) const{
        using namespace std::rel_ops;

        if(name != rhs.name)
            return false;
        if(numberOfPrerequisites != rhs.numberOfPrerequisites)
            return false;
        for(int i = 0; i < numberOfPrerequisites; ++i)
            if(prereqs[i] != rhs.prereqs[i])
                return false;
        return true;

    }
    // copy assignment operator overload
    Course& Course::operator=(const Course& rhs){
        if(this != &rhs){
            name = rhs.name;
            numberOfPrerequisites = rhs.numberOfPrerequisites;
            maxPrerequisites = rhs.maxPrerequisites;
            delete [] prereqs;
            prereqs = new CourseName[maxPrerequisites];
            for(int i = 0; i < numberOfPrerequisites; ++i)
                prereqs[i] = rhs.prereqs[i];
        }
        return *this;
    }

    // move assignment operator overload (jrich)
    Course& Course::operator=(Course&& c){
        if(this != &c){
            name = c.name;
            numberOfPrerequisites = c.numberOfPrerequisites;
            maxPrerequisites = c.maxPrerequisites;
            delete [] prereqs;
            prereqs = c.prereqs;
            c.prereqs = nullptr;
        }
        return *this;
    }

    bool Course::operator<(const Course& c) const{

        using namespace rel_ops;

        if(name != c.name)
            return name < c.name;
        if(numberOfPrerequisites != c.numberOfPrerequisites)
            return numberOfPrerequisites < c.numberOfPrerequisites;
        for(int i = 0; i < numberOfPrerequisites; ++i)
            if(prereqs[i] != c.prereqs[i])
                return prereqs[i] < c.prereqs[i];
         return false;
     }
