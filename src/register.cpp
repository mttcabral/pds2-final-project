#include "register.hpp"

Register::Register(RectangleT plan) : plan(plan) {
    buffer[0] = '\0';
    index = 0;
    tittle = "";
    message = "";

    PointT firstRowTopLeft = plan.topLeft; // first Row top left point
    float rowLength = plan.length;
    float rowHeight = plan.height/((float) NUMREGISTERROWS);
    PointT firstRowBottomRight = firstRowTopLeft + PointT(rowLength, rowHeight); // first Row bottom right point
    
    rows.resize(NUMREGISTERROWS);
    for (int i = 0; i < NUMREGISTERROWS; i++)
        rows[i].rowRectangle = RectangleT(firstRowTopLeft + PointT(0, i*rowHeight), firstRowBottomRight + PointT(0, i*rowHeight));
}

Register::Register(const Register& otherRegister) {
    this->index = otherRegister.index;
    this->tittle = otherRegister.tittle;
    this->message = otherRegister.message;
    this->plan = otherRegister.plan;

    for(int i = 0; i < otherRegister.index + 1; i++) {
            this->buffer[i] = otherRegister.buffer[i];
    }

    this->rows.resize(NUMREGISTERROWS);
    for (int i = 0; i < NUMREGISTERROWS; i ++) {
        this->rows[i] = otherRegister.rows[i];
    }
}

Register& Register::operator = (const Register& otherRegister) {
    if (this != &otherRegister) {
        this->index = otherRegister.index;
        this->tittle = otherRegister.tittle;
        this->message = otherRegister.message;
        this->plan = otherRegister.plan;

        for(int i = 0; i < otherRegister.index + 1; i++) {
            this->buffer[i] = otherRegister.buffer[i];
        }

        this->rows.resize(NUMREGISTERROWS); // to avoid segmentation fault
        for (int i = 0; i < NUMREGISTERROWS; i ++)
            this->rows[i] = otherRegister.rows[i];
    }

    return *this;
}

bool Register::writeInBuffer(char c) {
    if (index < 20) {
        buffer[index] = c;
        index++;
        buffer[index] = '\0';

        return true;
    }
    return false;
}

bool Register::deleteInBuffer() {
    if (index > 0) {
        index--;
        buffer[index] = '\0';

        return true;
    }
    return false;
}

string Register::getTittleContent() {
    return this->tittle;
}

string Register::getMessageContent() {
    return this->message;
}

string Register::getBufferContent() {
    string content = this->buffer;
    return content;
}

string Register::getIthContent(int i){
    string empty = "";
    switch (i) {
        case 0:
            return this->getTittleContent();
            break;
        case 1:
            return this->getMessageContent();
            break;
        case 2:
            return this->getBufferContent();
            break;
    }
    return empty;
};

Color Register::getTittleTextColor() {
    return this->rows[0].textColor;
}

Color Register::getMessageTextColor() {
    return this->rows[1].textColor;
}

Color Register::getBufferTextColor() {
    return this->rows[2].textColor;
}

Color Register::getIthTextColor(int i){
    Color empty;
    switch (i) {
        case 0:
            return this->getTittleTextColor();
            break;
        case 1:
            return this->getMessageTextColor();
            break;
        case 2:
            return this->getBufferTextColor();
            break;
    }
    return empty;
}

float Register::getIthCenterX(int i) {
    if (i>= 0 && i < 3)
        return this->rows[i].rowRectangle.center.x;
    return 0;
}

float Register::getIthCenterY(int i) {
    if (i>= 0 && i < 3)
        return this->rows[i].rowRectangle.center.y;
    return 0;
}

void Register::setTittleContent(string tittleText) {
    this->tittle = tittleText;
}

void Register::setMessageContent(string messageText) {
    this->message = messageText;
}

void Register::setTittleTextColor(Color color) {
    this->rows[0].textColor = color;
}

void Register::setMessageTextColor(Color color) {
    this->rows[1].textColor = color;
}

void Register::setBufferTextColor(Color color) {
    this->rows[2].textColor = color;
}

void Register::drawRegister(ALLEGRO_FONT* font) {
    for (int i = 0; i < 3; i ++) {
        Color tempColor = this->getIthTextColor(i);
        ALLEGRO_COLOR aColor = al_map_rgb(tempColor.r, tempColor.g, tempColor.b);
        float tempX = this->getIthCenterX(i);
        float tempY = this->getIthCenterY(i);
        string tempText = this->getIthContent(i);
        const char* aText = tempText.c_str();
        al_draw_text(font, aColor, tempX, tempY, ALLEGRO_ALIGN_CENTRE, aText);
    }
}

bool validateNameChars(string name) {
    set<char> validChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'S', 'U', 'V', 'W', 'X', 'Y', 'Z',
                            ' '};
    for (char c : name)
        if (validChars.find(c) == validChars.end())
            throw invalid_argument("Only letters (without accentes) and spaces are allowed.");
    
    return true;
}

bool validateNicknameChars(string nickname) {
    set<char> validChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'T', 'S', 'U', 'V', 'W', 'X', 'Y', 'Z',
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
    for (char c : nickname)
        if (validChars.find(c) == validChars.end())
            throw invalid_argument("Only letters (without accents), numbers and _ are allowed.");
    
    return true;
}

bool validateNameSize(string name) {
    if (name.size() < static_cast<size_t>(MINPROFILENAMESIZE) || name.size() > static_cast<size_t>(MAXPROFILENAMESIZE))
        throw range_error("Name must be " + to_string(MINPROFILENAMESIZE) + "-" + to_string(MAXPROFILENAMESIZE) + " characters.");
    return true;
}

bool validateNicknameSize(string nickname) {
    if (nickname.size() < static_cast<size_t>(MINPROFILENICKNAMESIZE) || nickname.size() > static_cast<size_t>(MAXPROFILENICKNAMESIZE))
        throw range_error("Nickname must be " + to_string(MINPROFILENICKNAMESIZE) + "-" + to_string(MAXPROFILENICKNAMESIZE) + " characters.");
    return true;
}

bool validateName(string name) {
    if (validateNameSize(name) && validateNameChars(name))
        return true;
    else
        throw runtime_error("Something went wrong! Please, try to register again.");
}

bool validateNickname(string name) {
    if (validateNicknameSize(name) && validateNicknameChars(name))
        return true;
    else
        throw runtime_error("Something went wrong! Please, try to register again.");
}

string checkName(string& name, bool& signal, const char*& warning) { // recebe nome, analisa se eh valido, atribui a signal a validade e a warning um aviso, caso houver
    signal = false;

    try {
        validateName(name);
        signal = true;
        warning = "";
    }
    catch (invalid_argument &i) {
        warning = i.what();
    }
    catch (range_error &r) {
        warning = r.what();
    }
    catch (runtime_error &r) {
        warning = r.what();
    }
    if (!signal)
        name = "";

    return name;
}

string checkNickname(bool& signal, const char*& warning) {
    signal = false;
    string nickname;

    try {
        validateNickname(nickname);
        signal = true;
        warning = "";
    }
    catch (invalid_argument &i) {
        warning = i.what();
    }
    catch (range_error &r) {
        warning = r.what();
    }
    catch (runtime_error &r) {
        warning = r.what();
    }
    if (!signal)
        nickname = "";

    return nickname;
}