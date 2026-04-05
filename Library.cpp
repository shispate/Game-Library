#include "Library.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 *  Loads games from a plain-text file. Each game occupies 6 consecutive
 *  lines: title, publisher, genre, hoursPlayed, price, year.
 *  Games are inserted in sorted order as they are read.
 */
bool Library::loadFromFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        return false;
    }

    Game g;
    string line;

    while (getline(fin, g.title)) {
        // skip blank lines between games
        if (g.title.empty()) {
            continue;
        }
        if (!getline(fin, g.publisher))  break;
        if (!getline(fin, g.genre))      break;

        if (!getline(fin, line)) break;
        g.hoursPlayed = stof(line);

        if (!getline(fin, line)) break;
        g.price = stof(line);

        if (!getline(fin, line)) break;
        g.year = static_cast<short>(stoi(line));

        insertSorted(g);
    }

    fin.close();
    return true;
}

bool Library::saveToFile(const string& filename) const {
    ofstream fout(filename);
    if (!fout) {
        return false;
    }

    for (const Game& g : games) {
        fout << g.title       << "\n"
             << g.publisher   << "\n"
             << g.genre       << "\n"
             << g.hoursPlayed << "\n"
             << g.price       << "\n"
             << g.year        << "\n"
             << "\n"; // the blank line
    }

    fout.close();
    return true;
}


// Insertion

/**
 * Inserts game into the list so that the list remains sorted
 * alphabetically by title (case-insensitive).
 */
void Library::insertSorted(const Game& g) {
    string gLower = toLower(g.title);

    for (auto it = games.begin(); it != games.end(); ++it) {
        if (gLower < toLower(it->title)) {
            games.insert(it, g);
            return;
        }
    }
    // gmae belongs at the end
    games.push_back(g);
}

// pushes game to the front of the list (unsorted insertion).
void Library::pushFront(const Game& g) {
    games.push_front(g);
}

// pushes g to the back of the list (unsorted insertion).
void Library::pushBack(const Game& g) {
    games.push_back(g);
}


// Search
void Library::findGenre(const string& genre) const {
    string target = toLower(genre);
    bool   found  = false;

    printHeader();
    for (const Game& g : games) {
        if (toLower(g.genre) == target) {
            printGame(g);
            found = true;
        }
    }
    if (!found) {
        cout << "  No games found in genre: " << genre << "\n";
    }
}

void Library::findGame(const string& substring) const {
    string target = toLower(substring);
    bool   found  = false;

    printHeader();
    for (const Game& g : games) {
        if (toLower(g.title).find(target) != string::npos) {
            printGame(g);
            found = true;
        }
    }
    if (!found) {
        cout << "  No games found matching: \"" << substring << "\"\n";
    }
}


// Deletion
bool Library::deleteGame(const string& title, short year) {
    string target = toLower(title);

    for (auto it = games.begin(); it != games.end(); ++it) {
        if (toLower(it->title) == target && it->year == year) {
            games.erase(it);
            return true;
        }
    }
    return false;
}


// Print
void Library::printAll() const {
    if (games.empty()) {
        cout << "  The library is empty.\n";
        return;
    }
    printHeader();
    for (const Game& g : games) {
        printGame(g);
    }
}

// number of games
int Library::size() const {
    return static_cast<int>(games.size());
}

string Library::toLower(const string& s) const {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void Library::printHeader() const {
    cout << "\n"
         << left
         << setw(32) << "Title"
         << setw(20) << "Publisher"
         << setw(12) << "Genre"
         << setw(8)  << "Hours"
         << setw(8)  << "Price"
         << setw(6)  << "Year"
         << "\n"
         << string(86, '-') << "\n";
}

void Library::printGame(const Game& g) const {
    cout << left
         << setw(32) << g.title
         << setw(20) << g.publisher
         << setw(12) << g.genre
         << setw(8)  << fixed << setprecision(1) << g.hoursPlayed
         << "$" << setw(7) << fixed << setprecision(2) << g.price
         << setw(6)  << g.year
         << "\n";
}
