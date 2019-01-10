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

class DeatheStar : public ImperialStarShip {
public:
    DeatheStar(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~DeatheStar() override = default;
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

std::shared_ptr<ImperialStarShip> createDeathStar(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<ImperialStarShip> createTIEFighter(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<ImperialStarShip> createImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<ImperialStarShip> createSquadron(const std::initializer_list<std::shared_ptr<ImperialStarShip>> &ships);

std::shared_ptr<ImperialStarShip> createSquadron(const std::vector<std::shared_ptr<ImperialStarShip>> &ships);


#endif //STARWARS_2_IMPERIALFLEET_H
