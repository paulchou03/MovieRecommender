//#include "UserDatabase.h"
//#include "User.h"
//#include "Movie.h"
//#include "MovieDatabase.h"
//#include "treemm.h" 
//#include <vector>
//#include <fstream>
//#include <iostream>
//#include <string>
//#include "Recommender.h"
//using namespace std;
//#if defined(_MSC_VER)  &&  !defined(_DEBUG)
//#include <iostream>
//#include <windows.h>
//#include <conio.h>
//
//struct KeepWindowOpenUntilDismissed
//{
//	~KeepWindowOpenUntilDismissed()
//	{
//		DWORD pids[1];
//		if (GetConsoleProcessList(pids, 1) == 1)
//		{
//			std::cout << "Press any key to close this window . . . ";
//			_getch();
//		}
//	}
//} keepWindowOpenUntilDismissed;
//#endif
//
////////////////////////////i/////////////////////////////////////////////////////
////
//// You are free to do whatever you want with this file, since you won't
//// be turning it in.  Presumably, you will make changes to help you test
//// your classes.  For example, you might try to implement only some User
//// member functions to start out with, and so replace our main routine with
//// one that simply creates a User and verifies that the member functions you
//// implemented work correctly.
////
////////////////////////////i/////////////////////////////////////////////////////
//
//
//  // If your program is having trouble finding these files. replace the
//  // string literals with full path names to the files.  Also, for test
//  // purposes, you may want to create some small, simple user and movie
//  // data files to makde debuggiing easier, so you can replace the string
//  // literals with the names of those smaller files.
//
//const string USER_DATAFILE = "users.txt";
//const string MOVIE_DATAFILE = "movies.txt";
//
//int main()
//{
//	//ifstream infile("test.txt");
//	//while(!infile)
//	//{
//		/*if (!infile)
//			break;*/
//		//string name;
//		//getline(infile, name);
//		//cout << name << endl;
//		//string email;
//		//getline(infile, email);
//		//cout << email << endl;
//		//int num;
//		//infile >> num;
//		//infile.ignore(10000, '\n');
//		//cout << num << endl;
//		//vector<string> watchhistory;
//		//for (int i = 0; i < num; i++)
//		//{
//		//	string item;
//		//	getline(infile, item);
//		//	watchhistory.push_back(item);
//		//	cout << item << endl;
//		//}
//		///*for (int i = 0; i < watchhistory.size(); i++)
//		//{
//		//	cout << watchhistory[i] << endl;
//		//}*/
//
//	//	string empty;
//	//	getline(infile, empty);
//	//	cout << empty << endl;
//	//}
//	
//	UserDatabase udb;
//	
//	if (udb.load("test.txt") == false)  // In skeleton, load always return false
//	{
//		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
//		return 1;
//	}
//	else
//		cout << "loaded" << endl;
//	for (;;)
//	{
//		cout << "Enter user email address (or quit): ";
//		string email;
//		getline(cin, email);
//		if (email == "quit")
//			return 0;
//		User* u = udb.get_user_from_email(email);
//		if (u == nullptr)
//			cout << "No user in the database has that email address." << endl;
//		else
//			cout << "Found " << u->get_full_name() << endl;
//	}
//}
//
////MovieDatabase udb;
////
////if (udb.load("test.txt") == false)  // In skeleton, load always return false
////{
////	cout << "Failed to load movie data file " << USER_DATAFILE << "!" << endl;
////	return 1;
////}
////else
////cout << "loaded" << endl;
////for (;;)
////{
////	cout << "Enter director name: ";
////	string director;
////	getline(cin, director);
////	if (director == "quit")
////		return 0;
////	vector<Movie*> u = udb.get_movies_with_director(director);
////	for (int i = 0; i < u.size(); i++)
////	{
////		cout << u[i]->get_title() << endl;
////	}
////}
////for (;;)
////{
////	cout << "Enter director ID (or quit): ";
////	string director;
////	getline(cin, director);
////	if (director == "quit")
////		return 0;
////	vector<Movie*> u = udb.get_movies_with_director(director);
////	cout << u.size() << endl;
////	for (int i = 0; i < u.size(); i++)
////	{
////		cout << u[i]->get_title() << endl;
////	}
////}
////for (;;)
////{
////	cout << "Enter movie ID (or quit): ";
////	string id;
////	getline(cin, id);
////	if (id == "quit")
////		return 0;
////	Movie* u = udb.get_movie_from_id(id);
////	if (u == nullptr)
////		cout << "No movie in the database has that id." << endl;
////	else
////	{
////		cout << "ID: " << u->get_id() << endl;
////		cout << "Found " << u->get_title() << endl;
////	}
////}
//
//
//
////TreeMultimap<string, int> tmm;
//	//tmm.insert("carey", 5);
//	//tmm.insert("carey", 6);
//	//tmm.insert("carey", 7);
//	//tmm.insert("david", 25);
//	//tmm.insert("david", 425);
//	//TreeMultimap<string, int>::Iterator it = tmm.find("carey");
//	//// prints 5, 6, and 7 in some order
//	//while (it.is_valid()) {
//	//	cout << it.get_value() << endl;
//	//	it.advance();
//	//}
//	//it = tmm.find("laura");
//	//if (!it.is_valid())
//	//	cout << "laura is not in the multimap!\n";



















//start here
#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;

#include "treemm.h"


void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations) {
	vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
	if (recommendations.empty())
		cout << "We found no movies to recommend.\n";
	else {
		for (int i = 0; i < recommendations.size(); i++) {
			const MovieAndRank& mr = recommendations[i];
			Movie* m = md.get_movie_from_id(mr.movie_id);
			cout << i + 1 << ". " << m->get_title() << " ("
				<< m->get_release_year() << ")\n Rating: "
				<< m->get_rating() << "\n Compatibility Score: "
				<< mr.compatibility_score << "\n";
		}
	}
};

const string USER_DATAFILE = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

int main()
{
	UserDatabase udb;
	if (!udb.load(USER_DATAFILE))  
	{
		cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
		return 1;
	}
	MovieDatabase mdb;
	if (!mdb.load(MOVIE_DATAFILE))  
	{
		cout << "Failed to load movie data file " << MOVIE_DATAFILE << "!" << endl;
		return 1;
	}
	TreeMultimap<std::string, int> tmm;


	for (;;)
	{
		cout << "Enter user email address for recommendation (or quit): ";
		string email;
		getline(cin, email);
		if (email == "quit")
			return 0;
		User* u = udb.get_user_from_email(email);
		if (u == nullptr)
			cout << "No user in the database has that email address." << endl;
		else
		{
			cout << "Enter number of recommendations to provide: ";
			int numrec;
			cin >> numrec;
			cout << "User " << u->get_full_name() << " has watched the following movies: " << endl;
			vector<string> watchhistory = u->get_watch_history();
			for (int i = 0; i < watchhistory.size(); i++)
			{
				Movie* m = mdb.get_movie_from_id(watchhistory.at(i));
				cout << m->get_title() << endl;
			}
			cout << "Here are the recommendations: " << endl;
			Recommender r(udb, mdb);
			findMatches(r, mdb, email, numrec);
			//AbFow2483@charter.net
		}
	}
}