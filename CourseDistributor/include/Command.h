#ifndef COMMAND_H
#define COMMAND_H
#include <bits/stdc++.h>
#include "Variables.h"

using namespace std;

Student *GivenStudents;


void cmd () {
            ifstream tempF;
            tempF.open ("dataStudents.txt");
            tempF >> NumOfAllStudents;
            GivenStudents = new Student[NumOfAllStudents];
            for (int i = 0 ; i < NumOfAllStudents ; ++i) {
                    GivenStudents[i].InsertStudentDatas(tempF);
            }
            tempF.close ();
}

#endif // COMMAND_H
