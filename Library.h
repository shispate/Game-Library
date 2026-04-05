/**
 * @file Library.h
 * @brief Header file for the game library class
 */
#ifndef LIBRARY_H
#define LIBRARY_H

#include <list>
#include <string>
#include "Game.h"

// manages a sorted linked list of game entries
class Library {
public:
    // loads game data from a file into the list in sorted order
    bool loadFromFile(const std::string& filename);
    // saves all games in the list to a file
    bool saveToFile(const std::string& filename) const;
    // inserts a game into the list in alphabetical order by title
    void insertSorted(const Game& g);
    // inserts a game at the front of the list
    void pushFront(const Game& g);
    // inserts a game at the back of the list
    void pushBack(const Game& g);
    // prints all games matching the given genre
    void findGenre(const std::string& genre) const;
    // prints all games whose title contains the given substring
    void findGame(const std::string& substring) const;
    // removes the game matching the given title and release year
    bool deleteGame(const std::string& title, short year);
    // prints all games in the library to standard output
    void printAll() const;
    // returns the number of games currently in the library
    int size() const;

private:
    std::list<Game> games; // sorted linked list of all game entries

    // converts a string to lowercase for case-insensitive comparison
    std::string toLower(const std::string& s) const;
    // prints a single game entry as a formatted table row
    void printGame(const Game& g) const;
    // prints the column header for game output
    void printHeader() const;
};

#endif // LIBRARY_H