#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include <algorithm>
#include "Movie.h"
#include "User.h"
#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
    const MovieDatabase& movie_database) 
    :m_udb(user_database) ,m_mdb(movie_database) //User and movie database has been loaded in
{ 
    
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    //Map to a pair of vector to a vector of MovieAndRank
    int numrec = movie_count; 
    unordered_map<string, int> finalmap;
    vector<pair<string, int>> recommender;
    vector<MovieAndRank> result;
    vector<MovieAndRank> reclist;


    User* user = m_udb.get_user_from_email(user_email); //Points to a User object from a given email
    if (user == nullptr) //Return empty vector if email can't be found
    {
        return vector<MovieAndRank>();
    }
    vector<string> watchhistory = user->get_watch_history(); //Gets a vector of the watchhistory from user
    vector<string>::iterator it = watchhistory.begin(); 
    for (it; it != watchhistory.end(); it++)
    {
        Movie* movie = m_mdb.get_movie_from_id((*it)); //Points to a Movie object from a given ID
        vector<string> listdirector = movie->get_directors();
        vector<string> listactor = movie->get_actors();
        vector<string> listgenre = movie->get_genres();
        vector<string>::iterator diritr = listdirector.begin();
        vector<string>::iterator actoritr = listactor.begin();
        vector<string>::iterator genreitr = listgenre.begin();
        //Iterating through the list of directors and putting movies that the director has directed into the map along with the score
        for (diritr; diritr != listdirector.end(); diritr++) 
        {
            vector<Movie*> dmovie = m_mdb.get_movies_with_director(*diritr);
            vector<Movie*>::iterator samedir = dmovie.begin();
            for (samedir; samedir != dmovie.end(); samedir++)
            {
                string d_id = (*samedir)->get_id();
                finalmap[d_id] += 20; //If same movie, add 20. If different movie, add to map and initialize score to 20
            }
        }
        //Iterating through the list of actors and putting movies that the actor has directed into the map along with the score
        for (actoritr; actoritr != listactor.end(); actoritr++)
        {
            vector<Movie*> amovie = m_mdb.get_movies_with_actor(*actoritr);
            vector<Movie*>::iterator sameact = amovie.begin();
            for (sameact; sameact != amovie.end(); sameact++)
            {
                string a_id = (*sameact)->get_id();
                finalmap[a_id] += 30; //If same movie, add 30. If different movie, add to map and initialize score to 30
            }
        }
        //Iterating through the list of genres and putting movies that the genre is in into the map along with the score
        for (genreitr; genreitr != listgenre.end(); genreitr++)
        {
            vector<Movie*> gmovie = m_mdb.get_movies_with_genre(*genreitr);
            vector<Movie*>::iterator samegen = gmovie.begin();
            for (samegen; samegen != gmovie.end(); samegen++)
            {
                string g_id = (*samegen)->get_id();
                finalmap[g_id] += 1; //If same genre, add 1. If different movie, add to map and initialize score to 1
            }
        }
    }
  
    //Iterating through the map, checking for duplicates, and inserting into a vector
    unordered_map<string, int>::iterator mapitr = finalmap.begin();
    for (mapitr; mapitr != finalmap.end(); mapitr++)
    {
        bool duplicate = false;
        string id = mapitr->first;
        int score = mapitr->second; 
        for (int i = 0; i < watchhistory.size(); i++)
        {
            if (id == watchhistory[i])
            {
                duplicate = true;
            }
        }
        if (duplicate == false)
        {
            recommender.push_back({ id, score });
        }
        else
            continue;
    }
    //sorting the vecotor using lambda function from highest score to lowest score
    sort(recommender.begin(), recommender.end(), [this](pair<string, int>& a, pair<string, int>& b)
        { 
            Movie* first = m_mdb.get_movie_from_id(a.first);
            Movie* second = m_mdb.get_movie_from_id(b.first);

            if (a.second > b.second)
                return true;
            else if (a.second < b.second)
                return false;
            else if (a.second == b.second) //When scores are equal, check ratings
            {
                if (first->get_rating() > second->get_rating())
                    return true;
                else if (first->get_rating() < second->get_rating())
                    return false;
                else if (first->get_rating() == second->get_rating()) //When ratings are equal, check alphabetical order
                {
                    if (second->get_title() > first->get_title())
                        return true;
                    else
                        return false;
                }
            }
            return false;
        });
    vector<pair<string, int>>::iterator vecitr = recommender.begin();
    for (vecitr; vecitr != recommender.end(); vecitr++)
    {
        string realid = vecitr->first;
        int realscore = vecitr->second;
        result.push_back(MovieAndRank(realid, realscore)); //Converting vector pair to vector of MovieAndRank
    }
    //Return result
    for (int i = 0; i < numrec; i++)
    {
        reclist.push_back(result[i]);
        if (i == result.size() - 1)
        {
            break;
        }
    }
    return reclist;
}



