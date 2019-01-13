#include "imperialfleet.h"

ImperialStarship::ImperialStarship(ShieldPoints shieldPoints, AttackPower attackPower)
        : Starship(shieldPoints), Attacking(shieldPoints, attackPower) {}

DeathStar::DeathStar(ShieldPoints shieldPoints, AttackPower attackPower) : Starship(shieldPoints),
                                                                             ImperialStarship(shieldPoints,
                                                                                              attackPower) {}

ImperialDestroyer::ImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower) : Starship(shieldPoints),
                                                                                           ImperialStarship(
                                                                                                   shieldPoints,
                                                                                                   attackPower) {}

TIEFighter::TIEFighter(ShieldPoints shieldPoints, AttackPower attackPower) : Starship(shieldPoints),
                                                                             ImperialStarship(shieldPoints,
                                                                                              attackPower) {}

Squadron::Squadron(const std::vector<std::shared_ptr<ImperialStarship>> &ships) : Starship(0), ImperialStarship(0, 0),
                                                                                  ships(ships) {
    updateShieldAndAttackPower();
}

Squadron::Squadron(const std::initializer_list<std::shared_ptr<ImperialStarship>> &ships) : Starship(0),
                                                                                            ImperialStarship(0, 0),
                                                                                            ships(ships) {
    updateShieldAndAttackPower();
}

void Squadron::updateShieldAndAttackPower() {
    attackPower = 0;
    shieldPoints = 0;
    for (const auto &item : ships) {
        if (item->getShield() != 0) {
            shieldPoints += item->getShield();
            attackPower += item->getAttackPower();
        }
    }
}

void Squadron::takeDamage(AttackPower damage) {
    for (auto &item : ships) {
        item->takeDamage(damage);
    }
    updateShieldAndAttackPower();
}

NumberOfShips Squadron::howManyUndestroyedUnits() {
    NumberOfShips numberOfShips = 0;
    
    for (auto &item : ships) {
        numberOfShips += item->howManyUndestroyedUnits();
    }
    
    return numberOfShips;
}

std::shared_ptr<DeathStar> createDeathStar(ShieldPoints shieldPoints, AttackPower attackPower) {
    return std::make_shared<DeathStar>(shieldPoints, attackPower);
}

std::shared_ptr<TIEFighter> createTIEFighter(ShieldPoints shieldPoints, AttackPower attackPower) {
    return std::make_shared<TIEFighter>(shieldPoints, attackPower);
}

std::shared_ptr<ImperialDestroyer> createImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower) {
    return std::make_shared<ImperialDestroyer>(shieldPoints, attackPower);
}

//std::shared_ptr<Squadron> createSquadron(const std::vector<std::shared_ptr<ImperialStarShip>> &ships) {
//    return std::make_shared<Squadron>(ships);
//}

std::shared_ptr<Squadron>
createSquadron(const std::initializer_list<std::shared_ptr<ImperialStarship>> &ships) {
    return std::make_shared<Squadron>(ships);
}
