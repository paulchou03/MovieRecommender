#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include "treemm.h"
#include <string>

class User;

class UserDatabase
{
public:
    UserDatabase();
    ~UserDatabase();
    bool load(const string& filename);
    User* get_user_from_email(const string& email) const;

private:
    TreeMultimap<string, User*> m_user;
    vector<User*> numUser;
};

#endif // USERDATABASE_INCLUDED
