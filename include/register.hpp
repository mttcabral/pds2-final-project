#ifndef REGISTER_H
#define REGISTER_H
#include <vector>
#include <stdbool.h>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "table.hpp"
#include <set>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

const int MINPROFILENAMESIZE = 4;
const int MAXPROFILENAMESIZE = 20;

const int MINPROFILENICKNAMESIZE = 4;
const int MAXPROFILENICKNAMESIZE = 12;

int const NUMREGISTERROWS = 3;

class Register {
    private:
        int bufferSize;
        char* buffer;
        int index;
        string tittle;
        string message;
        RectangleT plan;
        vector<Row> rows;
    
    public:
        Register(int, RectangleT);
        Register(string, int, RectangleT);
        ~Register();

        Register(const Register&);
        Register& operator = (const Register&);

        bool writeInBuffer(char);
        bool deleteInBuffer();
        bool cleanBuffer();

        string getTittleContent();
        string getMessageContent();
        string getBufferContent();
        string getIthContent(int);

        Color getTittleTextColor();
        Color getMessageTextColor();
        Color getBufferTextColor();
        Color getIthTextColor(int);

        float getIthCenterX(int);
        float getIthCenterY(int);

        void setTittleContent(string);
        void setMessageContent(string);

        void setTittleTextColor(Color);
        void setMessageTextColor(Color);
        void setBufferTextColor(Color);

        void drawRegister(ALLEGRO_FONT*);
};

bool validateNameChars(string);
bool validateNicknameChars(string);

bool validateNameSize(string);
bool validateNicknameSize(string);

bool validateName(string);
bool validateNickname(string);

bool checkName(string, string&);
bool checkNickname(string, string&);

#endif