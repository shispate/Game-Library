#include <iostream>
#include <string>
#include <limits>
#include "Library.h"
#include "Game.h"

using namespace std;

// ---------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------
void     printMenu();
Game     promptGame();
string   promptLine(const string& label);
float    promptFloat(const string& label);
short    promptShort(const string& label);

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int main() {
    Library lib;
    string  filename;
    int     choice;

    cout << "==============================================\n"
         << "       Steam Game Library Manager v1.0       \n"
         << "==============================================\n\n";

    // Prompt for file on startup
    cout << "Enter database filename to load (or press Enter to start fresh): ";
    getline(cin, filename);

    if (!filename.empty()) {
        if (lib.loadFromFile(filename)) {
            cout << "Loaded " << lib.size() << " game(s) from \"" << filename << "\".\n";
        } else {
            cout << "Could not open \"" << filename
                 << "\". Starting with an empty library.\n";
        }
    }

    // Remember filename for saving later
    if (filename.empty()) {
        filename = "library.txt";
    }

    // Main menu loop
    do {
        printMenu();
        cout << "Choice: ";
        cin  >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            // ------------------------------------------------------------------
            case 1: { // Add game (sorted)
                Game g = promptGame();
                lib.insertSorted(g);
                cout << "  \"" << g.title << "\" added to library (sorted).\n";
                break;
            }
            // ------------------------------------------------------------------
            case 2: { // Add game to front
                Game g = promptGame();
                lib.pushFront(g);
                cout << "  \"" << g.title << "\" added to front of library.\n";
                break;
            }
            // ------------------------------------------------------------------
            case 3: { // Add game to back
                Game g = promptGame();
                lib.pushBack(g);
                cout << "  \"" << g.title << "\" added to back of library.\n";
                break;
            }
            // ------------------------------------------------------------------
            case 4: { // Print all games
                cout << "\n--- Full Library (" << lib.size() << " game(s)) ---";
                lib.printAll();
                break;
            }
            // ------------------------------------------------------------------
            case 5: { // Search by title substring
                string sub = promptLine("Enter title keyword");
                lib.findGame(sub);
                break;
            }
            // ------------------------------------------------------------------
            case 6: { // Search by genre
                string genre = promptLine("Enter genre");
                lib.findGenre(genre);
                break;
            }
            // ------------------------------------------------------------------
            case 7: { // Delete a game
                string title = promptLine("Enter exact game title to delete");
                short  year  = promptShort("Enter release year");
                if (lib.deleteGame(title, year)) {
                    cout << "  \"" << title << "\" (" << year << ") removed.\n";
                } else {
                    cout << "  No matching game found.\n";
                }
                break;
            }
            // ------------------------------------------------------------------
            case 8: { // Save to file
                string saveName = promptLine("Enter filename to save to (Enter for \"" + filename + "\")");
                if (saveName.empty()) {
                    saveName = filename;
                }
                if (lib.saveToFile(saveName)) {
                    cout << "  Library saved to \"" << saveName << "\".\n";
                    filename = saveName;
                } else {
                    cout << "  Error: could not write to \"" << saveName << "\".\n";
                }
                break;
            }
            // ------------------------------------------------------------------
            case 9: { // Load from file
                string loadName = promptLine("Enter filename to load");
                if (lib.loadFromFile(loadName)) {
                    cout << "  Loaded " << lib.size() << " game(s) from \""
                         << loadName << "\".\n";
                    filename = loadName;
                } else {
                    cout << "  Error: could not open \"" << loadName << "\".\n";
                }
                break;
            }
            // ------------------------------------------------------------------
            case 0:
                cout << "\n  Saving library to \"" << filename << "\" before exit...\n";
                if (lib.saveToFile(filename)) {
                    cout << "  Saved successfully. Goodbye!\n";
                } else {
                    cout << "  Warning: could not save. Goodbye!\n";
                }
                break;
            // ------------------------------------------------------------------
            default:
                cout << "  Invalid option. Please try again.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}

// ---------------------------------------------------------------------------
// Helper functions
// ---------------------------------------------------------------------------

/**
 * @brief Displays the main menu options.
 */
void printMenu() {
    cout << "\n+----------------------------------+\n"
         << "|         LIBRARY MENU             |\n"
         << "+----------------------------------+\n"
         << "| 1. Add game (sorted)             |\n"
         << "| 2. Add game to front             |\n"
         << "| 3. Add game to back              |\n"
         << "| 4. Print all games               |\n"
         << "| 5. Search by title keyword       |\n"
         << "| 6. Search by genre               |\n"
         << "| 7. Delete a game                 |\n"
         << "| 8. Save library to file          |\n"
         << "| 9. Load library from file        |\n"
         << "| 0. Save & Exit                   |\n"
         << "+----------------------------------+\n";
}

/**
 * @brief Prompts the user to enter all fields for a new Game.
 * @return A fully populated Game struct.
 */
Game promptGame() {
    Game g;
    cout << "\n  -- Enter game details --\n";
    g.title       = promptLine("  Title");
    g.publisher   = promptLine("  Publisher");
    g.genre       = promptLine("  Genre (e.g. RPG, FPS, Simulation)");
    g.hoursPlayed = promptFloat("  Hours Played");
    g.price       = promptFloat("  Price ($)");
    g.year        = promptShort("  Release Year");
    return g;
}

/**
 * @brief Prompts the user for a single line of text.
 * @param label The prompt label to display.
 * @return The entered string.
 */
string promptLine(const string& label) {
    string val;
    cout << "  " << label << ": ";
    getline(cin, val);
    return val;
}

/**
 * @brief Prompts the user for a float value, re-prompting on bad input.
 * @param label The prompt label to display.
 * @return A valid float entered by the user.
 */
float promptFloat(const string& label) {
    float val;
    cout << "  " << label << ": ";
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. " << label << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

/**
 * @brief Prompts the user for a short integer, re-prompting on bad input.
 * @param label The prompt label to display.
 * @return A valid short entered by the user.
 */
short promptShort(const string& label) {
    short val;
    cout << "  " << label << ": ";
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. " << label << ": ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}
