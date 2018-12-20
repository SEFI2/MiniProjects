#ifndef CONSTRUCTANDSTARTALGORITHM_H
#define CONSTRUCTANDSTARTALGORITHM_H
#include "SuperClass.h"
#include "CoursesForEachTrack.h"

map <string , vector <SuperClass> > forEachCourseSuperClass;

map <string , vector <SuperClass> > :: iterator it;


string foraWhile;

bool cmp (SuperClass a , SuperClass b) {
        if (a.priority != b.priority) {
                return a.priority > b.priority;
        }
        bool A = DoTheyMatch[ make_pair(GivenStudents[a.studentInd].Major , a.course) ];
        bool B = DoTheyMatch[ make_pair(GivenStudents[b.studentInd].Major , b.course) ];

        if (A != B) {
                return A > B;
        }

        A = DoTheyMatch[ make_pair(GivenStudents[a.studentInd].Minor , a.course) ];
        B = DoTheyMatch[ make_pair(GivenStudents[b.studentInd].Minor , b.course) ];

        if (A != B) {
                return A > B;
        }

        int AA = GivenStudents[a.studentInd].yearOfGraduation;
        int BB = GivenStudents[b.studentInd].yearOfGraduation;
        if (AA != BB) {
                return AA > BB;
        }

        return rand () % 2;
}



void ConstructAndStartAlgorithm () {


            for (int i = 0 ; i < NumOfAllStudents ; ++i) {
                        for (int j = 0 ; j < GivenStudents[i].NumCourses ; ++j) {
                                                string course = GivenStudents[i].StudentCourses[j].Name;
                                                int prior = GivenStudents[i].StudentCourses[j].Priority;
                                                SuperClass T (i , prior , course);
                                                forEachCourseSuperClass[course].push_back (T);
                        }
            }
            srand (time (NULL));

            for  (it = forEachCourseSuperClass.begin() ; it != forEachCourseSuperClass.end() ; it ++) {
                            vector <SuperClass> &tmp = it->second;
                            sort (tmp.begin() , tmp.end() , &cmp);
            }

            for  (it = forEachCourseSuperClass.begin() ; it != forEachCourseSuperClass.end() ; it ++) {
                            vector <SuperClass> &V = it->second;
                            int NumOfSeats = NumOfSeatsForCourse[it->first];
                            int NumOfCredits = NumOfCreditsForCourse[it->first];
                            int WantedStudents = (int) V.size();

            }

}

#endif // CONSTRUCTANDSTARTALGORITHM_H





















