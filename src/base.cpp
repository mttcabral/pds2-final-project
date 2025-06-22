#include "base.hpp"

Profile::Profile() : Profile("", "", 0, 1) {}; // default

Profile::Profile(string name, string nickname) : Profile(name, nickname, 0, 1) {}; // default

Profile::Profile(string name, string nickname, int maxPipers, int plays) : name(name), nickname(nickname), maxPipers(maxPipers), plays(plays) {} // inicializar lista de jogadores

Profile::Profile(const Profile& otherProfile) {
        this->name = otherProfile.name;
        this->nickname = otherProfile.nickname;
        this->maxPipers = otherProfile.maxPipers;
        this->plays = otherProfile.plays;
    }

bool Profile::operator > (const Profile& otherProfile) const {
            return (this->maxPipers > otherProfile.maxPipers);
        }

bool Profile::operator < (const Profile& otherProfile) const {
            return (this->maxPipers < otherProfile.maxPipers);
        }

bool Profile::operator == (const Profile& otherProfile) const {
    return (this->nickname == otherProfile.nickname);
}

Profile Profile::operator = (const Profile& otherProfile) {
    if (this != &otherProfile) {
        this->name = otherProfile.name;
        this->nickname = otherProfile.nickname;
        this->plays = otherProfile.plays;
        this->maxPipers = otherProfile.maxPipers;
    }
    return *this;
}

string Profile::getName() {
    return this->name;
}

string Profile::getNickname() {
    return this->nickname;
}

int Profile::getPlays() {
    return this->plays;
}

int Profile::getMaxPipers() {
    return this->maxPipers;
}

void Profile::setPlays(int numPlays) {
    this->plays = numPlays;
}

void Profile::setMaxPipers(int numMaxPipers) {
    this->maxPipers = numMaxPipers;
}

void Profile::display(){
    cout << this->name << endl;
    cout << this->nickname << endl;
    cout << this->maxPipers << endl;
    cout << this->plays << endl;
}

void Base::clearProfiles() {
    for (Profile* profile : this->profiles) {
        delete profile;
    }
    profiles.clear();
}

void Base::copyProfiles(const vector<Profile*>& profilesVector) {
    for (Profile* profile : profilesVector)
        this->profiles.push_back(new Profile(*profile));
}

Base::Base(const Base& otherBase) {
    copyProfiles(otherBase.profiles);
}

Base::Base(const vector<Profile*>& otherBaseVector) {
    copyProfiles(otherBaseVector);
}

Base::Base() {
    this->profiles.resize(0);
};

Base::Base(string path) { // path to the file
    ifstream base(path, fstream::in);
    string line = "";

    string _name;
    string _nickname;
    int _plays;
    int _maxPipers;

    bool noTittles = false;
    int count = 1;

    while(getline(base, line)) {
        if(noTittles) {
            stringstream info(line);
            string cell;

            while(getline(info, cell, ',')) {
                if(count == 1) { // 1 and 2 for strings
                    _name = cell;
                    count++;
                }
                else if(count == 2) {
                    _nickname = cell;
                    count++;
                }
                else if (count == 3) { // 3 and 4 for integers
                    istringstream value(cell);
                    value >> _maxPipers;
                    count++;
                }
                else if (count == 4) {
                    istringstream value(cell);
                    value >> _plays;
                    count = 1;
                }
            }
            profiles.push_back(new Profile(_name, _nickname, _maxPipers, _plays));
        }
        else { // skip the first line
            noTittles = true;
        }
    };
    base.close();
};

Base::~Base() {
    clearProfiles();
};

Base Base::operator = (const Base& otherBase) {
    if (this != &otherBase) {
        clearProfiles();
        copyProfiles(otherBase.profiles);
    }
    return *this;
}

bool Base::inBase(string nickname) {
    for (Profile* profile : this->profiles)
        if (profile->getNickname() == nickname) return true;

    return false;
}

bool Base::inBase(Profile otherProfile) {
    for (Profile* profile : this->profiles)
        if (profile->getNickname() == otherProfile.getNickname()) return true;

    return false;
}

bool Base::updateProfiles(Profile newProfile) {
    bool found = false;
    for (Profile* profile : this->profiles) {
        if (profile->getNickname() == newProfile.getNickname()) {
            if (profile->getName() == newProfile.getName()) { // if profiles have the same nickname, so they must be the same person
                if(profile->getMaxPipers() < newProfile.getMaxPipers()) {
                    profile->setMaxPipers(newProfile.getMaxPipers());
                }
                profile->setPlays(profile->getPlays() + 1);
            }
            else // if profiles have the same nickname, but their names are different, they can not be different persons
                return false;
            found = 1;
        }
    }
    
    if (!found)
        this->profiles.push_back(new Profile(newProfile));

    return true;
}

bool Base::removeProfile(string nickname) {
    for (size_t i = 0; i < this->profiles.size(); i++) {
        if (this->profiles[i]->getNickname() == nickname){
            this->profiles.erase(this->profiles.begin()+i);
            return true;
        }
    }
    return false;
}

vector<Profile*> Base::getBestProfiles(){
    vector<Profile*> orderedProfilesVector; // a new vector
    for (Profile* profile : this->profiles)
        orderedProfilesVector.push_back(new Profile(*profile));

    sort(orderedProfilesVector.begin(), orderedProfilesVector.end(), [](Profile* a, Profile* b) {return *a > *b;}); // ordered vector

    vector<Profile*> bestProfiles; // the return vector

    if (orderedProfilesVector.size() > NUMPROFILES) { // if orderedProfilesVector NUMPROFILES is bigger than NUMPROFILES, then you need to filtrate
        for (int i = 0; i < NUMPROFILES; i++)
            bestProfiles.push_back(new Profile(*orderedProfilesVector[i])); 
    }
    else { // if orderedProfilesVector size is smaller than size, then you do not need to filtrate
        for (Profile* profile : orderedProfilesVector)
            bestProfiles.push_back(new Profile(*profile));
    }
    
    for (Profile* profilePointer : orderedProfilesVector) { // clear memory
        delete profilePointer;
    }
    orderedProfilesVector.clear();

    return bestProfiles;
}

void Base::saveBase(string path){
    ofstream base(path);
    base << "Name,Nickname,MaxPipers,Plays\n";
    for (Profile* profile : this->profiles) {
        base << profile->getName() << "," << profile->getNickname() << "," << profile->getMaxPipers() << "," << profile->getPlays() << "\n";
    }
    base.close();
}

void Base::display(){
    for(Profile *profile : profiles)
        cout << profile->getName() << " " << profile->getNickname() << " " << profile->getMaxPipers() << " " << profile->getPlays() << endl;
}

/*
bool validateNicknameChars (string nickname) {
    set<char> validChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'S', 'U', 'V', 'W', 'X', 'Y', 'Z',
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
    for (int i = 0; i < nickname.size(); i++)
        if (validChars.find(nickname[i]) == validChars.end()) return false;
    
    return false;
}

bool validateNameChars (string name) {
    set<char> validChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'S', 'U', 'V', 'W', 'X', 'Y', 'Z',
                                 ' '};
    for (int i = 0; i < name.size(); i++)
        if (validChars.find(name[i]) == validChars.end()) return false;
    
    return false;
}

bool validateNicknameSize (string nickname) {
    if (nickname.size() > 12 ) return false;
    return true;
}

bool validateNameSize (string name) {
    if (name.size() > 20 ) return false;
    return true;
}
*/