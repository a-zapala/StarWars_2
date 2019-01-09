#include <algorithm>
#include "helper.h"

ShieldPoints StarShip::getShield() const {
    return shieldPoints;
}

void StarShip::takeDamage(AttackPower damage) {
    shieldPoints = std::max(shieldPoints - damage, 0);
}

StarShip::StarShip(ShieldPoints shieldPoints) : shieldPoints(shieldPoints) {}

AttackPower Attacking::getAttackPower() const {
    return attackPower;
}

void Attacking::maybeAttack(std::shared_ptr<StarShip> &ship) {
    if (shieldPoints > 0) {
        ship->takeDamage(attackPower);
    }
}

Attacking::Attacking(ShieldPoints shieldPoints, AttackPower attackPower) : StarShip(shieldPoints),
                                                                           attackPower(attackPower) {}
