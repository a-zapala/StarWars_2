#include "imperialfleet.h"

ImperialStarShip::ImperialStarShip(ShieldPoints shieldPoints, AttackPower attackPower)
        : StarShip(shieldPoints), Attacking(shieldPoints, attackPower) {}

DeathStar::DeathStar(ShieldPoints shieldPoints, AttackPower attackPower) : StarShip(shieldPoints),
                                                                             ImperialStarShip(shieldPoints,
                                                                                              attackPower) {}

ImperialDestroyer::ImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower) : StarShip(shieldPoints),
                                                                                           ImperialStarShip(
                                                                                                   shieldPoints,
                                                                                                   attackPower) {}

TIEFighter::TIEFighter(ShieldPoints shieldPoints, AttackPower attackPower) : StarShip(shieldPoints),
                                                                             ImperialStarShip(shieldPoints,
                                                                                              attackPower) {}

Squadron::Squadron(const std::vector<std::shared_ptr<ImperialStarShip>> &ships) : StarShip(0), ImperialStarShip(0, 0),
                                                                                  ships(ships) {
    updateShieldAndAttackPower();
}

Squadron::Squadron(const std::initializer_list<std::shared_ptr<ImperialStarShip>> &ships) : StarShip(0),
                                                                                            ImperialStarShip(0, 0),
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

std::shared_ptr<ImperialStarShip> createDeathStar(ShieldPoints shieldPoints, AttackPower attackPower) {
    return std::make_shared<DeathStar>(shieldPoints, attackPower);
}

std::shared_ptr<ImperialStarShip> createTIEFighter(ShieldPoints shieldPoints, AttackPower attackPower) {
    return std::make_shared<TIEFighter>(shieldPoints, attackPower);
}

std::shared_ptr<ImperialStarShip> createImperialDestroyer(ShieldPoints shieldPoints, AttackPower attackPower) {
    return std::make_shared<ImperialDestroyer>(shieldPoints, attackPower);
}

std::shared_ptr<ImperialStarShip> createSquadron(const std::vector<std::shared_ptr<ImperialStarShip>> &ships) {
    return std::make_shared<Squadron>(ships);
}

std::shared_ptr<ImperialStarShip>
createSquadron(const std::initializer_list<std::shared_ptr<ImperialStarShip>> &ships) {
    return std::make_shared<Squadron>(ships);
}
