#ifndef COOLDOWN_H
#define COOLDOWN_H

// class for handling time events, such as obstacle spawning or action cooldowns

//keep this synced with 'main' FPS
const float FPS = 30;

class Cooldown {
    private:
        //Frames left to finish cooldown
        float timeLeft = 0;
        //how much time it takes to finish cooldown each time
        float rechargeTime;
        //how fast it counts down, 1 is normal time and X is X times faster
        float updateFrequency = 1;
        bool frozen = false;
    public:
        //always input time IN SECONDS units
        Cooldown(float wuTime);
        Cooldown();

        //count timeLeft down until it finishes
        void updateCooldown();

        //resets timeLeft to rechargeTime
        void restartCooldown();
        //sets timeLeft to 0
        void refreshCooldown();

        //outputs rather the cooldown is finished or not
        bool isCooldownUp();

        //sets new wind up time, remember to input time IN SECONDS units
        void setRechargeTime(float wuTime);
        //new update frequency factor, 1 is normal and 2 is twice as fast, for example
        void setUpdateFrequency(float f);

        float getCurrentTimeLeft();
        float getCurrentPorcentage();
        float getRechargeTime();

        void freezeCooldown();
        void unfreezeCooldown();
};











#endif