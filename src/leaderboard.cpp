#include "leaderboard.hpp"
// topPlayers has size NUMPLAYERS
// table.row has size NUMROWS

LeaderBoard::LeaderBoard(RectangleT plan, string path) : table(plan), base(path) {
    this->topPlayers.resize(NUMPLAYERS);
    this->table.row[0].texts = {"RANK", "NICKNAME", "MAX PIPERS", "PLAYS"};
    
    this->topPlayers = base.getBestPlayers(NUMPLAYERS);
    int i = 1;
    for (Player* player : this->topPlayers) { // write table with information
        string _rank = to_string(i);
        string _nickname = player->getNickname();
        string _maxPipers = to_string(player->getMaxPipers());
        string _plays = to_string(player->getPlays());
        table.row[i].texts = {_rank, _nickname, _maxPipers, _plays};
        i++;
    }
};

void LeaderBoard::newPlayer(Player player) {
    this->base.updatePlayers(player);
}

void LeaderBoard::updateLeaderBoard() { // called after newPlayer
    for (Player* player : topPlayers)
        delete player;
    this->topPlayers.clear();

    topPlayers = this->base.getBestPlayers(NUMPLAYERS);
    int i = 1;
    for (Player* player : this->topPlayers) { // write table with information
        string _rank = to_string(i);
        string _nickname = player->getNickname();
        string _maxPipers = to_string(player->getMaxPipers());
        string _plays = to_string(player->getPlays());
        table.row[i].texts = {_rank, _nickname, _maxPipers, _plays};
        i++;
    }
}

void LeaderBoard::setTitleRowColor(Color rgb) {
    this->table.row[0].rowColor = rgb;
};

void LeaderBoard::setFirstRowColor(Color rgb) {
    this->table.row[1].rowColor = rgb;
};

void LeaderBoard::setSecondRowColor(Color rgb) {
    this->table.row[2].rowColor = rgb;
};

void LeaderBoard::setThirdRowColor(Color rgb) {
    this->table.row[3].rowColor = rgb;
};

void LeaderBoard::setOthersRowsColor(Color rgb) {
    for(int i = 4; i < NUMROWS; i++) {
        this->table.row[i].rowColor = rgb;
    }
};

void LeaderBoard::setTitleRowTextColor(Color rgb) {
    this->table.row[0].textColor = rgb;
};

void LeaderBoard::setFirstRowTextColor(Color rgb) {
    this->table.row[1].textColor = rgb;
};

void LeaderBoard::setSecondRowTextColor(Color rgb) {
    this->table.row[2].textColor = rgb;
};

void LeaderBoard::setThirdRowTextColor(Color rgb) {
    this->table.row[3].textColor = rgb;
};

void LeaderBoard::setOthersRowsTextColor(Color rgb) {
    for(int i = 4; i < NUMROWS; i++) {
        this->table.row[i].textColor = rgb;
    }
};

/*
void LeaderBoard::displayAllegro(ALLEGRO_FONT* font) {
    for (Row line : this->table.row) {
        Color tempTextColor = line.textColor;
        ALLEGRO_COLOR aColor = al_map_rgb(tempTextColor.r, tempTextColor.g, tempTextColor.b);
        for (int i = 0; i < NUMCOLUMNS; i++){
            float subX = line.rowRectangle.subCenters[i].x;
            float subY = line.rowRectangle.subCenters[i].y;
            char const *aText = line.texts[i].c_str();
            al_draw_text(FONTFILENAME, aColor, subX, subY, ALLEGRO_ALIGN_CENTRE, aText);
        }
    }
    al_flip_display();
}
*/

void LeaderBoard::display(){
    this->table.display();
}

void LeaderBoard::save(string path) {
    this->base.saveBase(path);
}