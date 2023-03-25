#include "UserDatabase.h"
#include "User.h"
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

UserDatabase::UserDatabase()
{
   
}
UserDatabase::~UserDatabase()
{
    //Deletes every dynamically allocated object that the pointer is pointing to
    for (int i = 0; i < numUser.size(); i++)
    {
        delete numUser[i];
    }
}
bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        return false;
    }
    for(;;)
    {
        string name; //Name line
        getline(infile, name);
        string email; //Email line
        getline(infile, email);
        int num; //Numer line
        infile >> num;
        infile.ignore(10000, '\n');
        vector<string> watchhistory; //Watch history vector
        for (int i = 0; i < num; i++) 
        {
            string item;
            getline(infile, item);
            watchhistory.push_back(item); //Adding the ID to the vector
        }
        User* user = new User(name, email, watchhistory); //Points to new object User
        numUser.push_back(user);
        m_user.insert(email, user); //Add to destructor list
        string empty; //Empty line
        getline(infile, empty);
        if (!infile)
            break;
    }
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, User*>::Iterator it = m_user.find(email);
    if (it.is_valid())
    {
        return it.get_value(); //Return a pointer to User with given email
    }
    return nullptr;  // Replace this line with correct code.
}
