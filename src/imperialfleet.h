#ifndef STARWARS_2_IMPERIALFLEET_H
#define STARWARS_2_IMPERIALFLEET_H

#include <vector>
#include <memory>
#include "helper.h"

class ImperialStarShip : public virtual StarShip, public Attacking {
public:
    ImperialStarShip(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~ImperialStarShip() override = default;
};

class DeathStar : public ImperialStarShip {
public:
    DeathStar(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~DeathStar() override = default;
};

class ImperialDestroyer : public ImperialStarShip {
public:
    ImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~ImperialDestroyer() override = default;
};

class TIEFighter : public ImperialStarShip {
public:
    TIEFighter(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~TIEFighter() override = default;
};

class Squadron : public ImperialStarShip {
private:
    std::vector<std::shared_ptr<ImperialStarShip>> ships;
    void takeDamage(AttackPower damage) override;
    
    void updateShieldAndAttackPower();

    NumberOfShips howManyUndestroyedUnits() override;

public:
    Squadron(const std::initializer_list<std::shared_ptr<ImperialStarShip>> &ships);
    
    Squadron(const std::vector<std::shared_ptr<ImperialStarShip>> &ships);
};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<ImperialDestroyer> createImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<Squadron> createSquadron(const std::initializer_list<std::shared_ptr<ImperialStarShip>> &ships);

std::shared_ptr<Squadron> createSquadron(const std::vector<std::shared_ptr<ImperialStarShip>> &ships);


#endif //STARWARS_2_IMPERIALFLEET_H
