#ifndef VARIABLES_H
#define VARIABLES_H


#include <bits/stdc++.h>
using namespace std;


int NumOfAllStudents;



class Course{
        public:
            string Name;
            int Priority;   // priority of each course (1 ~ 5)
            bool retake;
        public:
            void InsertCourse (ifstream &tempF) {
                    tempF >> Name >> Priority >> retake;
            }
};

class Student {
        public:
            int NumCourses;
            Course *StudentCourses;
            int StudentID;
            string FirstName , LastName;
            string Major , Minor;

            int yearOfGraduation;
        public :
            void InsertStudentDatas (ifstream &tempF) {
                    tempF >> FirstName >> LastName >> StudentID;
                    tempF >> NumCourses >> yearOfGraduation >> Major >> Minor;

                    StudentCourses = new Course [NumCourses];
                    for (int i = 0 ; i < NumCourses ; ++i) {
                                StudentCourses[i].InsertCourse(tempF);
                    }
            }
};


#endif // VARIABLES_H
