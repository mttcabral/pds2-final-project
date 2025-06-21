#ifndef LEADERBOARD_H
#define LEADERBOARD_H

//#include <allegro5/allegro.h>
//#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_color.h>
//#include <allegro5/allegro_font.h>
#include <set>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "base.hpp"
#include "table.hpp"

class LeaderBoard {
    private:
        Table table;
        Base base;
        vector<Player*> topPlayers;

    public:
        LeaderBoard(RectangleT, string);

        void newPlayer(Player);
        void updateLeaderBoard();

        void setTitleRowColor(Color);
        void setFirstRowColor(Color);
        void setSecondRowColor(Color);
        void setThirdRowColor(Color);
        void setOthersRowsColor(Color);

        void setTitleRowTextColor(Color);
        void setFirstRowTextColor(Color);
        void setSecondRowTextColor(Color);
        void setThirdRowTextColor(Color);
        void setOthersRowsTextColor(Color);

        bool close();

        //void displayAllegro(ALLEGRO_FONT*);

        void display();

        void save(string);
};

#endif