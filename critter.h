#ifndef CRITTER_H
#define CRITTER_H


class Critter {
private:
    int id;
    int hitpoints;
    int reward;
    int strength;
    double speed;
    int level;
    float x, y;

public:
    Critter();
    Critter(int id, int hitpoints, int reward, int strength, double speed, int level);

    int getId() const;
    int getHitpoints() const;
    int getReward() const;
    int getStrength() const;
    double getSpeed() const;
    int getLevel() const;

    void setId(int id);
    void setHitpoints(int hitpoints);
    void setReward(int reward);
    void setStrength(int strength);
    void setSpeed(double speed);
    void setLevel(int level);

    void takeDamage(int damage);

    bool isAlive() const;

    void move();

    float getX() const;
    float getY() const; 
    void setPosition(float newX, float newY);
};


#endif //CRITTER_H