#include "UserDatabase.h"
#include "User.h"
#include "Movie.h"
#include "MovieDatabase.h"
#include "treemm.h"
#include <vector>
#include <iostream>
#include <string>
#include "Recommender.h"
using namespace std;




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
