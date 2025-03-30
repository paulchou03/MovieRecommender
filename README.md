# Movie Recommendation System

This project implements a movie recommendation engine that offers personalized suggestions to users based on a built-in algorithm. The system relies on a database of users and a database of movies—each user has specific preferences, and each movie is defined by a set of attributes.

---

## Program Structure

The application is built around several core classes, each of which includes a source file (`*.cpp`) and a corresponding header file (`*.h`):

- **`User`**  
  Represents an individual user in the platform. This class stores essential information such as the user's name, email, and list of preferred movies.

- **`Movie`**  
  Represents a single movie. This class holds key details like the movie's title, release year, genre, and rating.

- **`UserDatabase`**  
  Acts as a container for `User` objects. It supports loading user data from a file, looking up users by their email, and managing other user-related tasks.

- **`MovieDatabase`**  
  Functions similarly to `UserDatabase`, but for movies. It allows the system to load movie data, search for movies by ID, and perform other movie-centric operations.

- **`Recommender`**  
  Contains the system’s recommendation logic. This class leverages data from both the `UserDatabase` and `MovieDatabase` to generate tailored movie suggestions for individual users.

- **`TreeMultimap`**  
  A template class designed to associate a single key with multiple values. It’s useful for linking users to many movies or the other way around.

---

The `main.cpp` file serves as the entry point of the program. It initializes the `UserDatabase` and `MovieDatabase` using data from `users.txt` and `movies.txt`, and then uses the `Recommender` class to provide movie suggestions based on user input.

## Files

Here is a list of all the source files included in this project:

1. `User.h` and `User.cpp`
2. `Movie.h` and `Movie.cpp`
3. `UserDatabase.h` and `UserDatabase.cpp`
4. `MovieDatabase.h` and `MovieDatabase.cpp`
5. `Recommender.h` and `Recommender.cpp`
6. `main.cpp`
7. `users.txt` (sample data format is provided)
8. `movies.txt` (sample data format is provided)
9. `treemm.h`

---

## How to Run

To run the program, compile all `*.cpp` source files together. The entry point is `main.cpp`.  
Ensure that both `users.txt` and `movies.txt` are located in the same directory as the compiled executable.

Once the program is compiled, executing it will load the user and movie data from the text files and then generate personalized movie recommendations based on a specific user.


Enjoy exploring your personalized movie suggestions!

## Compilation and Execution

To build and run this program, you’ll need a C++ compiler that supports C++11 or newer. For demonstration purposes, we’ll use `g++`, a commonly used compiler that comes with the GNU Compiler Collection (GCC).

---

### Compilation

To compile all `.cpp` files, navigate to the folder containing the source code and enter the following command in your terminal:

```bash
g++ -std=c++11 -o MovieRecommender main.cpp User.cpp UserDatabase.cpp Movie.cpp MovieDatabase.cpp Recommender.cpp
```

This command tells g++ to compile all the necessary .cpp files and output an executable named MovieRecommender

### Execution
To run the compiled MovieRecommender program, use the command below:
```bash
./MovieRecommender
```
Make sure that both users.txt and movies.txt are in the same directory as the executable when you run the program. These files are necessary for the system to load user and movie data.




