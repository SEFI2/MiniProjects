#ifndef DATAGIVEN_H
#define DATAGIVEN_H


#include <bits/stdc++.h>
#include "MapQ.h"


using namespace std;


class ForEachGivenCourses{
        private:
            string CourseName;
            int NumCredits; // 1~3
            int NumSeats;

        public:
            void Insert (ifstream &tempF) {
                    tempF >> CourseName >> NumCredits >> NumSeats;
                    NumOfSeatsForCourse[CourseName] = NumSeats;
                    NumOfCreditsForCourse[CourseName] = NumCredits;

            }
            void show () {
                    cout << CourseName << " " << NumCredits << " " << NumSeats << "\n";
            }
};


int AllCourses;

ForEachGivenCourses *GivenCourses;

void getGivenData(){
            ifstream tempF;
            tempF.open ("dataCourses.txt");
            tempF >> AllCourses;
            GivenCourses = new ForEachGivenCourses [AllCourses];
            for (int i = 0 ; i < AllCourses ; ++i) {
                    GivenCourses[i].Insert(tempF);
            }
            tempF.close ();
}



#endif // DATAGIVEN_H
