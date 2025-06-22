#ifndef LEADERBOARD_H
#define LEADERBOARD_H

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
        Base base;
        vector<Profile*> topProfiles;

    public:
        Table table;

        LeaderBoard(string, RectangleT);

        void newProfile(Profile);
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

        //void drawLeaderBoard(ALLEGRO_FONT*);

        void display();

        void save(string);
};

#endif
