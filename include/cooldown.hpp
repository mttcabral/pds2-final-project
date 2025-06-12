#ifndef COOLDOWN_H
#define COOLDOWN_H

// class for handling time events, such as obstacle spawning or action cooldowns

//keep this synced with 'main' FPS
const float FPS = 30;

class Cooldown {
    private:
        float timeLeft = 0;
        float windUpTime;
        float updateFrequency = 1;
        bool Frozen = false;
    public:
        Cooldown();
        Cooldown(float wuTime);

        void updateCooldown();

        void refreshCooldown();

        void setWindUpTime(float wuTime);
        void setUpdateFrequency(float f);

        void getCurrentTimeLeft();
        void getWindUpTime();

        void freezeCooldown();
        void unfreezeCooldown();
};











#endif