#include "leaderboard.hpp"
// topProfiless has size NUMPROFILES
// table.row has size NUMROWS

LeaderBoard::LeaderBoard(string path, RectangleT plan) : base(path), table(plan) {
    this->topProfiles.resize(NUMPROFILES);
    //this->table.row[0].texts = {"RANK", "NICKNAME", "MAX DISTANCE", "PLAYS"};  // COMENT HERE TO REMOVE THE TITTLE LINE
    
    this->topProfiles = base.getBestProfiles();
    int i = 0;
    for (Profile* profile : this->topProfiles) { // write table with information
        string _nickname = profile->getNickname();
        string _maxDistance = to_string(profile->getMaxDistance());
        string _plays = to_string(profile->getPlays());
        table.row[i].texts = {_nickname, _maxDistance, _plays};
        i++;
    }
};

bool LeaderBoard::addNewProfile(Profile profile) {
    bool profileAdded = this->base.updateProfiles(profile);
    if (profileAdded) return true;
    else return false;
}

void LeaderBoard::updateLeaderBoard() { // called after newProfiles
    for (Profile* profile : topProfiles)
        delete profile;
    this->topProfiles.clear();

    topProfiles = this->base.getBestProfiles();
    int i = 0;
    for (Profile* profile : this->topProfiles) { // write table with information
        string _nickname = profile->getNickname();
        string _maxDistance = to_string(profile->getMaxDistance());
        string _plays = to_string(profile->getPlays());
        table.row[i].texts = {_nickname, _maxDistance, _plays};
        i++;
    }
}

//void LeaderBoard::setTitleRowColor(Color rgb) {
    //this->table.row[0].rowColor = rgb;
//};

void LeaderBoard::setFirstRowColor(Color rgb) {
    this->table.row[0].rowColor = rgb;
};

void LeaderBoard::setSecondRowColor(Color rgb) {
    this->table.row[1].rowColor = rgb;
};

void LeaderBoard::setThirdRowColor(Color rgb) {
    this->table.row[2].rowColor = rgb;
};

void LeaderBoard::setOthersRowsColor(Color rgb) {
    for(int i = 3; i < NUMROWS; i++) {
        this->table.row[i].rowColor = rgb;
    }
};

/*void LeaderBoard::setTitleRowTextColor(Color rgb) {
    this->table.row[0].textColor = rgb;
};*/

void LeaderBoard::setFirstRowTextColor(Color rgb) {
    this->table.row[0].textColor = rgb;
};

void LeaderBoard::setSecondRowTextColor(Color rgb) {
    this->table.row[1].textColor = rgb;
};

void LeaderBoard::setThirdRowTextColor(Color rgb) {
    this->table.row[2].textColor = rgb;
};

void LeaderBoard::setOthersRowsTextColor(Color rgb) {
    for(int i = 3; i < NUMROWS; i++) {
        this->table.row[i].textColor = rgb;
    }
};


void LeaderBoard::drawLeaderBoard(ALLEGRO_FONT* font) {
    for (Row line : this->table.row) {
        Color tempTextColor = line.textColor;
        ALLEGRO_COLOR aColor = al_map_rgb(tempTextColor.r, tempTextColor.g, tempTextColor.b);
        for (int i = 0; i < NUMCOLUMNS; i++){
            float subX = line.rowRectangle.subCenters[i].x;
            float subY = line.rowRectangle.subCenters[i].y;
            char const *aText = line.texts[i].c_str();
            al_draw_text(font, aColor, subX, subY, ALLEGRO_ALIGN_CENTRE, aText);
        }
    }
}


void LeaderBoard::display(){
    this->table.display();
}

void LeaderBoard::save(string path) {
    this->base.saveBase(path);
}