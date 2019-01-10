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

private:
    virtual void Attack(std::shared_ptr<StarShip> &ship) {};
    virtual NumberOfShips howManyUndestroyedUnits();
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
    void Attack(std::shared_ptr<StarShip> &ship) override;
};


class SpaceTime {
public:
    virtual bool isItAttackTime(Time t) const = 0;
};

class DefaultSpaceTime: public SpaceTime {
    bool isItAttackTime(Time t) const override;
};


#endif //STARWARS_2_HELPER_H
