#ifndef STARWARS_2_HELPER_H
#define STARWARS_2_HELPER_H

#include <memory>

using ShieldPoints = int;
using AttackPower = int;
using Speed = int;
using NumberOfShips = size_t;
using Time = size_t;

class StarShip {
    friend class Battle;

protected:
    ShieldPoints shieldPoints;

public:
    ShieldPoints getShield() const;
    
    virtual void takeDamage(AttackPower damage);
    
    StarShip(ShieldPoints shieldPoints);
    
    virtual ~StarShip() = default;

    virtual NumberOfShips howManyUndestroyedUnits();

private:
    virtual void maybeAttack(std::shared_ptr<StarShip> ship) {};

};


class Attacking : public virtual StarShip {
    friend class Battle;

protected:
    AttackPower attackPower;

public:
    AttackPower getAttackPower() const;
    
    Attacking(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~Attacking() override = default;

private:
    void maybeAttack(std::shared_ptr<StarShip> ship) override;
};


class AttackTime {
public:
    virtual bool isItAttackTime(Time t) const = 0;
};

class DefaultAttackTime: public AttackTime {
    bool isItAttackTime(Time t) const override;
};

class SpaceTime {
public:
    virtual void tick(Time t) = 0;

    SpaceTime(Time t0, Time t1);

    SpaceTime(Time t0, Time t1, std::shared_ptr<AttackTime> attackTime);

    virtual ~SpaceTime() = default;

    bool isItAttackTime();

    void setAttackTime(std::shared_ptr<AttackTime> newAttackTime);

protected:
    Time t0;
    Time t1;
    Time currentTime;
    std::shared_ptr<AttackTime> attackTime;
};

class DefaultSpaceTime: public SpaceTime {
public:
    void tick(Time t) override;

    DefaultSpaceTime(Time t0, Time t1) : SpaceTime(t0, t1) {}

    DefaultSpaceTime(Time t0, Time t1, std::shared_ptr<AttackTime> attackTime) :
            SpaceTime(t0, t1, attackTime) {}

    ~DefaultSpaceTime() override = default;
};


// for tests
class PastAttackTime: public AttackTime {
    bool isItAttackTime(Time t) const override;
};

class PastSpaceTime: public SpaceTime {
public:
    void tick(Time t) override;

    PastSpaceTime(Time t0, Time t1) : SpaceTime(t0, t1) {}

    PastSpaceTime(Time t0, Time t1, std::shared_ptr<AttackTime> attackTime) :
            SpaceTime(t0, t1, attackTime) {}

    ~PastSpaceTime() override = default;
};


#endif //STARWARS_2_HELPER_H
