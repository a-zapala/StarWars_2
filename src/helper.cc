#include <algorithm>
#include "helper.h"

ShieldPoints StarShip::getShield() const {
    return shieldPoints;
}

void StarShip::takeDamage(AttackPower damage) {
    shieldPoints = std::max(shieldPoints - damage, 0);
}

StarShip::StarShip(ShieldPoints shieldPoints) : shieldPoints(shieldPoints) {}

NumberOfShips StarShip::howManyUndestroyedUnits() {
    if (shieldPoints > 0) {
        return 1;
    }
    else {
        return 0;
    }
}


AttackPower Attacking::getAttackPower() const {
    return attackPower;
}

void Attacking::maybeAttack(std::shared_ptr<StarShip> &ship) {
    ship->takeDamage(attackPower);
}

Attacking::Attacking(ShieldPoints shieldPoints, AttackPower attackPower) : StarShip(shieldPoints),
                                                                           attackPower(attackPower) {}

bool DefaultSpaceTime::isItAttackTime(Time t) const {
    return (t % 2 == 0 ||  t % 3 == 0) && (t % 5 != 0);
}
