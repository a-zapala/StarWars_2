#include <cassert>
#include "rebelfleet.h"

Speed RebelStarShip::getSpeed() const {
    return speed;
}

RebelStarShip::RebelStarShip(ShieldPoints shieldPoints, Speed speed) : StarShip(shieldPoints), speed(speed) {}

Explorer::Explorer(ShieldPoints shieldPoints, Speed speed) : StarShip(shieldPoints),
                                                             RebelStarShip(shieldPoints, speed) {}

StarCruiser::StarCruiser(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower)
        : StarShip(shieldPoints), RebelStarShip(shieldPoints, speed), Attacking(shieldPoints, attackPower) {
    assert(speed >= 99999 && speed <= 299795);
}

XWing::XWing(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower)
        : StarShip(shieldPoints), RebelStarShip(shieldPoints, speed), Attacking(shieldPoints, attackPower) {
    
    assert(speed >= 299796 && speed <= 2997960);
}

std::shared_ptr<RebelStarShip> createExplorer(ShieldPoints shieldPoints, Speed speed) {
    return std::make_shared<Explorer>(shieldPoints,speed);
}

std::shared_ptr<RebelStarShip> createXWing(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower) {
    return std::make_shared<XWing>(shieldPoints,speed,attackPower);
}

std::shared_ptr<RebelStarShip> createStarCruiser(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower) {
    return std::make_shared<StarCruiser>(shieldPoints,speed,attackPower);
}
