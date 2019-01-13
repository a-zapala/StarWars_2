#ifndef STARWARS_2_IMPERIALFLEET_H
#define STARWARS_2_IMPERIALFLEET_H

#include <vector>
#include <memory>
#include "helper.h"

class ImperialStarship : public virtual Starship, public Attacking {
public:
    ImperialStarship(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~ImperialStarship() override = default;
};

class DeathStar : public ImperialStarship {
public:
    DeathStar(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~DeathStar() override = default;
};

class ImperialDestroyer : public ImperialStarship {
public:
    ImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~ImperialDestroyer() override = default;
};

class TIEFighter : public ImperialStarship {
public:
    TIEFighter(ShieldPoints shieldPoints, AttackPower attackPower);
    
    ~TIEFighter() override = default;
};

class Squadron : public ImperialStarship {
private:
    std::vector<std::shared_ptr<ImperialStarship>> ships;
    void takeDamage(AttackPower damage) override;
    
    void updateShieldAndAttackPower();

    NumberOfShips howManyUndestroyedUnits() override;

public:
    Squadron(const std::initializer_list<std::shared_ptr<ImperialStarship>> &ships);
    
    Squadron(const std::vector<std::shared_ptr<ImperialStarship>> &ships);
};

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<ImperialDestroyer> createImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower);

std::shared_ptr<Squadron> createSquadron(const std::initializer_list<std::shared_ptr<ImperialStarship>> &ships);

//std::shared_ptr<Squadron> createSquadron(const std::vector<std::shared_ptr<ImperialStarShip>> &ships);


#endif //STARWARS_2_IMPERIALFLEET_H
