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
const int NUMPROFILES = 8;

using namespace std;

class Profile {
    private:
        string name;
        string nickname;
        int maxPipers;
        int plays;

    public:
        // constructors
        Profile(); // default
        Profile(string, string); // novo jogador registrado, nao jogou ainda
        Profile(string, string, int, int); // inicializar lista de jogadores
        Profile(const Profile&);

        // operators
        bool operator > (const Profile&) const;
        bool operator < (const Profile&) const;
        bool operator == (const Profile&) const;
        Profile operator = (const Profile&);

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
        vector<Profile*> profiles; // too many Profiles in the file can cause segmentation fault

        void clearProfiles();
        void copyProfiles(const vector<Profile*>&);

    public:
        // constructors
        Base(const Base&);
        Base(const vector<Profile*>&);
        Base();
        Base(string);

        // destructor
        ~Base();

        // operator
        Base operator = (const Base&);

        bool inBase (string);
        bool inBase (Profile);

        // add and remove methods
        bool updateProfiles(Profile);
        bool removeProfile(string);

        vector<Profile*> getBestProfiles();
        void saveBase(string);
        void display();
};

// validate functions
bool validateNicknameChars(string);
bool validateNameChars(string);

bool validateNicknameSize(string);
bool validateNameSize(string);

#endif