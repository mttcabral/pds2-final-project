#ifndef BASE_H
#define BASE_H
#include <set>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// pressupoe-se que name e nickname sao validos (foram tratados no main)

using namespace std;

class Player {
    private:
        string name;
        string nickname;
        int maxPipers;
        int plays;

    public:
        // constructors
        Player(); // default
        Player(string, string); // novo jogador registrado, nao jogou ainda
        Player(string, string, int, int); // inicializar lista de jogadores
        Player(const Player&);

        // operators
        bool operator > (const Player&) const;
        bool operator < (const Player&) const;
        bool operator == (const Player&) const;
        Player operator = (const Player&);

        // getters
        string getName();
        string getNickname();
        int getPlays();
        int getMaxPipers();

        // setters
        void setPlays(int);
        void setMaxPipers(int);

        void display();
};

class Base {
    private:
        vector<Player*> players; // too many players in the file can cause segmentation fault

        void clearPlayers();
        void copyPlayers(const vector<Player*>&);

    public:
        // constructors
        Base(const Base&);
        Base(const vector<Player*>&);
        Base();
        Base(string);

        // destructor
        ~Base();

        // operator
        Base operator = (const Base&);

        bool inBase (string);
        bool inBase (Player);

        // add and remove methods
        bool updatePlayers(Player);
        bool removePlayer(string);

        vector<Player*> getBestPlayers(int);
        void saveBase(string);
        void display();
};

// validate functions
bool validateNicknameChars(string);
bool validateNameChars(string);

bool validateNicknameSize(string);
bool validateNameSize(string);

#endif