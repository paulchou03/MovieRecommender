#include "MovieDatabase.h"
#include "Movie.h"
#include "fstream"
#include <string>
#include <vector>
using namespace std;

MovieDatabase::MovieDatabase()
{
}

MovieDatabase::~MovieDatabase()
{
    //Deletes every dynamically allocated object that the pointer is pointing to
    for (int i = 0; i < numMovie.size(); i++)
    {
        delete numMovie[i];
    }
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        return false;
    }
    for (;;)
    {
        string id; //ID line
        getline(infile, id); 
        string name; //Name line
        getline(infile, name);   
        string year; //Year line
        getline(infile, year);
        vector<string> directorlist; //Director vector
        string director;
        getline(infile, director);
        for (int i = 0; i < director.size(); i++) //Separating the string of directors and putting them into the vector 
        {
            if (director.at(i) == ',')
            {
                directorlist.push_back(director.substr(0, i));
                director = director.substr(i + 1);
                i = 0;
            }
        }
        directorlist.push_back(director); //Push_back last Director
        vector<string> actorlist; //Actor vector
        string actor;
        getline(infile, actor);
        for (int i = 0; i < actor.size(); i++) //Separating the string of directors and putting them into the vector 
        {
            if (actor.at(i) == ',')
            {
                actorlist.push_back(actor.substr(0, i));
                actor = actor.substr(i+1);
                i = 0;
            }
        }
        actorlist.push_back(actor);
        vector<string> genrelist; //Genre vector
        string genre;
        getline(infile, genre);
        for (int i = 0; i < genre.size(); i++) //Separating the string of genres and putting them into the vector 
        {
            if (genre.at(i) == ',')
            {
                genrelist.push_back(genre.substr(0, i));
                genre = genre.substr(i + 1);
                i = 0;
            }
        }
        genrelist.push_back(genre);
        float rating;
        infile >> rating;
        infile.ignore(10000, '\n');

        Movie* movie = new Movie(id, name, year, directorlist, actorlist, genrelist, rating); //Points to new movie Object
        numMovie.push_back(movie); 
        string idcopy = id;
        for (int i = 0; i < idcopy.size(); i++) //Case sensitive
        {
            idcopy[i] = tolower(idcopy[i]);
        }
        m_movie.insert(idcopy, movie); //Insert to Tree
        for (int i = 0; i < directorlist.size(); i++) //Case sensitive
        {
            string directorcopy = directorlist.at(i);
            for (int k = 0; k < directorcopy.size(); k++)
            {
                directorcopy[k] = tolower(directorcopy[k]);
            }
            m_director.insert(directorcopy, movie); //Insert to Tree
        }
        for (int i = 0; i < actorlist.size(); i++) //Case sensitive
        {
            string actorcopy = actorlist.at(i);
            for (int k = 0; k < actorcopy.size(); k++)
            {
                actorcopy[k] = tolower(actorcopy[k]);
            }
            m_actor.insert(actorcopy, movie);//Insert to tree
        }
        for (int i = 0; i < genrelist.size(); i++) //Case sensitive
        {
            string genrecopy = genrelist.at(i);
            for (int k = 0; k < genrecopy.size(); k++)
            {
                genrecopy[k] = tolower(genrecopy[k]);
            }
            m_genre.insert(genrecopy, movie); //Insert to tree
        }
        string empty; //Space
        getline(infile, empty);
        if (!infile)
            break;
    }
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string copyid = id;
    for (int i = 0; i < copyid.size(); i++)
    {
        copyid[i] = tolower(copyid[i]); //Case sensitive
    }
    
    TreeMultimap<string, Movie*>::Iterator it = m_movie.find(copyid);
    if (it.is_valid())
    {
        return it.get_value(); //Return pointer to Movie object
    }
    return nullptr;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string copydirector = director;
    for (int i = 0; i < copydirector.size(); i++)
    {
        copydirector[i] = tolower(copydirector[i]); //Case sensitive
    }
    vector<Movie*> directorptr;
    TreeMultimap<string, Movie*>::Iterator it = m_director.find(copydirector); //MY FIND IS PROBABLY WRONG
 
    while (it.is_valid())
    {
        directorptr.push_back(it.get_value()); //Add to vector of pointers to Movie object
        it.advance();
    }
    return directorptr;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string copyactor = actor;
    for (int i = 0; i < copyactor.size(); i++)
    {
        copyactor[i] = tolower(copyactor[i]); //Case sensitive
    }
    vector<Movie*> actorptr;
    TreeMultimap<string, Movie*>::Iterator it = m_actor.find(copyactor);
    while (it.is_valid())
    {
        actorptr.push_back(it.get_value()); //Add to vector of pointers to Movie object
        it.advance();
    }
    return actorptr;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string copygenre = genre;
    for (int i = 0; i < copygenre.size(); i++)
    {
        copygenre[i] = tolower(copygenre[i]); //Case sensitive
    }
    vector<Movie*> genreptr;
    TreeMultimap<string, Movie*>::Iterator it = m_genre.find(copygenre);
    while (it.is_valid())
    {
        genreptr.push_back(it.get_value()); //Add to vector of pointers to Movie object
        it.advance();
    }
    return genreptr;
}