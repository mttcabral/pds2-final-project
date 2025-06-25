#include "base.hpp"

Profile::Profile() : Profile("", "", 0, 0) {}; // default

Profile::Profile(string name, string nickname) : Profile(name, nickname, 0, 1) {}; // default

Profile::Profile(string name, string nickname, int maxDistance, int plays) : name(name), nickname(nickname), maxDistance(maxDistance), plays(plays) {} // inicializar lista de jogadores

Profile::Profile(const Profile& otherProfile) {
        this->name = otherProfile.name;
        this->nickname = otherProfile.nickname;
        this->maxDistance = otherProfile.maxDistance;
        this->plays = otherProfile.plays;
    }

bool Profile::operator > (const Profile& otherProfile) const {
            return (this->maxDistance > otherProfile.maxDistance);
        }

bool Profile::operator < (const Profile& otherProfile) const {
            return (this->maxDistance < otherProfile.maxDistance);
        }

bool Profile::operator == (const Profile& otherProfile) const {
    return (this->nickname == otherProfile.nickname);
}

Profile Profile::operator = (const Profile& otherProfile) {
    if (this != &otherProfile) {
        this->name = otherProfile.name;
        this->nickname = otherProfile.nickname;
        this->plays = otherProfile.plays;
        this->maxDistance = otherProfile.maxDistance;
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

int Profile::getMaxDistance() {
    return this->maxDistance;
}

void Profile::setPlays(int numPlays) {
    this->plays = numPlays;
}

void Profile::setMaxDistance(int distance) {
    if (distance > this->maxDistance) this->maxDistance = distance;
}


void Profile::display(){
    cout << this->name << endl;
    cout << this->nickname << endl;
    cout << this->maxDistance << endl;
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
    int _maxDistance;

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
                    value >> _maxDistance;
                    count++;
                }
                else if (count == 4) {
                    istringstream value(cell);
                    value >> _plays;
                    count = 1;
                }
            }
            profiles.push_back(new Profile(_name, _nickname, _maxDistance, _plays));
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
                profile->setMaxDistance(newProfile.getMaxDistance());
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
    base << "Name,Nickname,MaxDistance,Plays\n";
    for (Profile* profile : this->profiles) {
        base << profile->getName() << "," << profile->getNickname() << "," << profile->getMaxDistance() << "," << profile->getPlays() << "\n";
    }
    base.close();
}

void Base::display(){
    for(Profile *profile : profiles)
        cout << profile->getName() << " " << profile->getNickname() << " " << profile->getMaxDistance() << " " << profile->getPlays() << endl;
}