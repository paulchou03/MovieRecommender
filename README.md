# MovieRecommender

movies.txt and users.txt can be resizeable (tested up to millions of users or movies).

users.txt must follow the following format:
Person 1’s name
Person 1’s email address
Count of number of movies for person 1
movieID#1
movieID#2
…
movieID#n
Person 2’s name
Person 2’s email address
Count of number of movies for person 2
movieID#1
movieID#2
…
movieID#n
etc.

movies.txt must follow the following format:
Movie ID 1
Movie Name
12
Movie Release Year
director1,director2,...,directorn
actor1,actor2,...,actorn
genre1,genre2,...,genren
rating out of 5 stars
Movie ID 2
Movie Name
Movie Release Year
director1,director2,...,directorn
actor1,actor2,...,actorn
genre1,genre2,...,genren
rating out of 5 stars
etc.


How recommender works

● Using the provided email address to find all of the movies the user has watched in the
past

● For each movie m the user has previously watched, determining a compatibility score:
  ○ For each director d associated with m, each movie in the movie database that
has d in its list of directors contributes 20 points to the compatibility score
  ○ For each actor a associated with m, each movie in the movie database that has a
in its list of actors contributes 30 points to the compatibility score
  ○ For each genre g associated with m, each movie in the movie database that has
g in its list of genres contributes 1 point to the compatibility score

● For the movies that have a compatibility score of at least 1, filtering out the movies that
the user has already watched (so you don't recommend them)

● Rank ordering all candidate movies that have a compatibility score of at least 1, breaking
ties as follows:
  ○ Movies with a higher compatibility score must ordered higher on the
recommendation list than movies with a lower compatibility score
  ○ If two or more movies have the same compatibility score, they must be further
ordered based on:
    ■ The movie's rating; a movie with a higher 5-star rating must be ordered
higher on the recommendation list than a movie with a lower 5-star rating
    ■ If two or more movies have the same compatibility score and the same 5-
star rating, then they must be further ordered based on the movie's name,
alphabetically, in ascending order (e.g., Avalanche comes before The
Matrix)

● Returning a vector with the requested number of the most highly ranked movie
recommendations, ordered as described above. If fewer compatible movies were found
than the requested number, then the vector must have all movies with a compatibility
score of at least 1, ordered as described above.
