#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

private: 
    //Four different trees
    TreeMultimap<string, Movie*> m_movie;
    TreeMultimap<string, Movie*> m_director;
    TreeMultimap<string, Movie*> m_actor;
    TreeMultimap<string, Movie*> m_genre;
    vector<Movie*> numMovie; //For destructor
};

#endif // MOVIEDATABASE_INCLUDED
