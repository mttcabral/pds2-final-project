#include "base.hpp"

Player::Player() : Player("", "", 0, 1) {}; // default

Player::Player(string name, string nickname) : Player(name, nickname, 0, 1) {}; // default

Player::Player(string name, string nickname, int maxPipers, int plays) : name(name), nickname(nickname), maxPipers(maxPipers), plays(plays) {} // inicializar lista de jogadores

Player::Player(const Player& otherPlayer) {
        this->name = otherPlayer.name;
        this->nickname = otherPlayer.nickname;
        this->maxPipers = otherPlayer.maxPipers;
        this->plays = otherPlayer.plays;
    }

bool Player::operator > (const Player& otherPlayer) const {
            return (this->maxPipers > otherPlayer.maxPipers);
        }

bool Player::operator < (const Player& otherPlayer) const {
            return (this->maxPipers < otherPlayer.maxPipers);
        }

bool Player::operator == (const Player& otherPlayer) const {
    return (this->nickname == otherPlayer.nickname);
}

Player Player::operator = (const Player& otherPlayer) {
    if (this != &otherPlayer) {
        this->name = otherPlayer.name;
        this->nickname = otherPlayer.nickname;
        this->plays = otherPlayer.plays;
        this->maxPipers = otherPlayer.maxPipers;
    }
    return *this;
}

string Player::getName() {
    return this->name;
}

string Player::getNickname() {
    return this->nickname;
}

int Player::getPlays() {
    return this->plays;
}

int Player::getMaxPipers() {
    return this->maxPipers;
}

void Player::setPlays(int numPlays) {
    this->plays = numPlays;
}

void Player::setMaxPipers(int numMaxPipers) {
    this->maxPipers = numMaxPipers;
}

void Player::display(){
    cout << this->name << endl;
    cout << this->nickname << endl;
    cout << this->maxPipers << endl;
    cout << this->plays << endl;
}

void Base::clearPlayers() {
    for (Player* player : this->players) {
        delete player;
    }
    players.clear();
}

void Base::copyPlayers(const vector<Player*>& playersVector) {
    for (Player* player : playersVector)
        this->players.push_back(new Player(*player));
}

Base::Base(const Base& otherBase) {
    copyPlayers(otherBase.players);
}

Base::Base(const vector<Player*>& otherBaseVector) {
    copyPlayers(otherBaseVector);
}

Base::Base() {
    this->players.resize(0);
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
            players.push_back(new Player(_name, _nickname, _maxPipers, _plays));
        }
        else { // skip the first line
            noTittles = true;
        }
    };
    base.close();
};

Base::~Base() {
    clearPlayers();
};

Base Base::operator = (const Base& otherBase) {
    if (this != &otherBase) {
        clearPlayers();
        copyPlayers(otherBase.players);
    }
    return *this;
}

bool Base::inBase(string nickname) {
    for (Player* player : this->players)
        if (player->getNickname() == nickname) return true;

    return false;
}

bool Base::inBase(Player otherPlayer) {
    for (Player* player : this->players)
        if (player->getNickname() == otherPlayer.getNickname()) return true;

    return false;
}

bool Base::updatePlayers(Player newPlayer) {
    bool found = false;
    for (Player* player : this->players) {
        if (player->getNickname() == newPlayer.getNickname()) {
            if (player->getName() == newPlayer.getName()) { // if players have the same nickname, so they must be the same person
                if(player->getMaxPipers() < newPlayer.getMaxPipers()) {
                    player->setMaxPipers(newPlayer.getMaxPipers());
                }
                player->setPlays(player->getPlays() + 1);
            }
            else // if players have the same nickname, but their names are different, they can not be different persons
                return false;
            found = 1;
        }
    }
    
    if (!found)
        this->players.push_back(new Player(newPlayer));

    return true;
}

bool Base::removePlayer(string nickname) {
    for (int i = 0; i < this->players.size(); i++) {
        if (this->players[i]->getNickname() == nickname){
            this->players.erase(this->players.begin()+i);
            return true;
        }
    }
    return false;
}

vector<Player*> Base::getBestPlayers(int size){
    vector<Player*> orderedPlayersVector; // a new vector
    for (Player* player : this->players)
        orderedPlayersVector.push_back(new Player(*player));

    sort(orderedPlayersVector.begin(), orderedPlayersVector.end(), [](Player* a, Player* b) {return *a > *b;}); // ordered vector

    vector<Player*> bestPlayers; // the return vector

    if (orderedPlayersVector.size() > size) { // if orderedPlayersVector size is bigger than size, then you need to filtrate
        for (int i = 0; i < size; i++)
            bestPlayers.push_back(new Player(*orderedPlayersVector[i])); 
    }
    else { // if orderedPlayersVector size is smaller than size, then you do not need to filtrate
        for (Player* player : orderedPlayersVector)
            bestPlayers.push_back(new Player(*player));
    }
    
    for (Player* playerPointer : orderedPlayersVector) { // clear memory
        delete playerPointer;
    }
    orderedPlayersVector.clear();

    return bestPlayers;
}

void Base::saveBase(string path){
    ofstream base(path);
    base << "Name,Nickname,MaxPipers,Plays\n";
    for (Player* player : this->players) {
        base << player->getName() << "," << player->getNickname() << "," << player->getMaxPipers() << "," << player->getPlays() << "\n";
    }
    base.close();
}

void Base::display(){
    for(Player *player : players)
        cout << player->getName() << " " << player->getNickname() << " " << player->getMaxPipers() << " " << player->getPlays() << endl;
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
