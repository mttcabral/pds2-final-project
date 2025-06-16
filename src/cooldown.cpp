#include "cooldown.hpp"


Cooldown::Cooldown(float wuTime): rechargeTime(wuTime*FPS) {}
Cooldown::Cooldown(): Cooldown(0) {}

void Cooldown::updateCooldown() {
    if (this->frozen) return; //don't update cooldown if frozen

    if (this->timeLeft <= 0) this->timeLeft = 0;
    else {
        timeLeft -= 1 * this->updateFrequency;
    }
}

void Cooldown::restartCooldown() {
    this->timeLeft = this->rechargeTime;
}
void Cooldown::refreshCooldown() {
    this->timeLeft = 0;
}

bool Cooldown::isCooldownUp() {return (this->timeLeft == 0);}


void Cooldown::setRechargeTime(float wuTime) {
    this->rechargeTime = FPS * wuTime;
}
void Cooldown::setUpdateFrequency(float f) {
    this->updateFrequency = f;
}

float Cooldown::getCurrentTimeLeft() {return this->timeLeft;}
float Cooldown::getCurrentPorcentage() {
    return (this->timeLeft / this->rechargeTime);
}
float Cooldown::getRechargeTime() {return this->rechargeTime;}

void Cooldown::freezeCooldown() {
    if (!frozen) frozen = true;
}
void Cooldown::unfreezeCooldown() {
    if (frozen) frozen = false;
}
