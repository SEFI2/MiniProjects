#ifndef COURSESFOREACHTRACK_H
#define COURSESFOREACHTRACK_H

map < pair <string , string> , bool> DoTheyMatch;

int numTracks;
map <string , vector <string> > COfTracks;
map <string , vector <string> > TOfCourses;



void InitializeTracksAndCourses (){
        ifstream tempF;
        tempF.open ("TracksAndCourses.txt");
        tempF >> numTracks;
        for (int i = 0 ; i < numTracks ; ++i) {
                string track , course;
                int nc;
                tempF >> track >> nc;
                while (nc --) {
                        tempF >> course;
                        COfTracks[track].push_back(course);
                        TOfCourses[course].push_back(track);
                        DoTheyMatch.insert(pair< pair <string , string> , bool>(make_pair (track , course) , true));
                }
        }
        tempF.close ();
}

#endif // COURSESFOREACHTRACK_H
