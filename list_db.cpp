/*****************************************************************************
 * File: list_db.cpp
 * Purpose: Simple example of linked list with structs
 *****************************************************************************/


#include <iostream>
#include <list>

using namespace std;

/* A simple movie struct */
struct movie {
  string title;
  string director;
};


int main() {
  /* A simple linked list-based movie DB */
  list<movie> movies;
  
  movie temp;
  /* Create a temporary movie */
  temp.title = "Pi";
  temp.director = "Darren Aronofsky";
  
  /*Add the movie to our list */
  movies.push_back(temp);


  /* Create a second temporary movie */
  temp.title = "Star Wars";
  temp.director = "George Lucas";


  /* Add the movies to a list */
  movies.push_back(temp);



  list<movie>::iterator it;

  /* Iterate over the list and print the contents (2 movies) */
  cout << "List of 2 items" << endl;
  for(it = movies.begin(); it != movies.end(); it++) {
    cout << "List item: " << it -> director << " - " << it -> title << endl;
  }
  cout << endl << endl;


  /* Create a third movie */
  temp.title = "Primer";
  temp.director = "Carruth";


  /* Insert the third movie in alphabetical order (will between Aronofsky and Lucas) */
  it = movies.begin();
  //Move iterator to the correct location.
  it++;


  /* Insert the movie using list.insert() */
  movies.insert(it, temp);


  cout << "List of 3 items:" << endl;
  /* Iterate over the list and print the contents (2 movies) */
  for(it = movies.begin(); it != movies.end(); it++) {
    cout << "List item: " << it -> director << " - " << it -> title << endl;
  }


  return 0;
}
