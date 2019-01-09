#ifndef STARWARS_2_HELPER_H
#define STARWARS_2_HELPER_H

#include <memory>

class battle;

using ShieldPoints = int;
using AttackPower = int;
using Speed = int;

class StarShip {
    friend class battle;

protected:
    ShieldPoints shieldPoints;

public:
    ShieldPoints getShield() const;
    
    virtual void takeDamage(AttackPower damage);
    
    StarShip(ShieldPoints shieldPoints);
    
    virtual ~StarShip() = default;

private:
    virtual void maybeAttack(std::shared_ptr<StarShip> &ship) {};
};

class Attacking : public virtual StarShip {
    friend class battle;

protected:
    AttackPower attackPower;

public:
    AttackPower getAttackPower() const;
    
    Attacking(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~Attacking() override = default;

private:
    void maybeAttack(std::shared_ptr<StarShip> &ship) override;
};


#endif //STARWARS_2_HELPER_H
