#include <cassert>
#include "rebelfleet.h"

Speed RebelStarship::getSpeed() const {
    return speed;
}

RebelStarship::RebelStarship(ShieldPoints shieldPoints, Speed speed) : Starship(shieldPoints), speed(speed) {}

Explorer::Explorer(ShieldPoints shieldPoints, Speed speed) : Starship(shieldPoints),
                                                             RebelStarship(shieldPoints, speed) {
    assert(speed >= 299796 && speed <= 2997960);
}

StarCruiser::StarCruiser(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower)
        : Starship(shieldPoints), RebelStarship(shieldPoints, speed), Attacking(shieldPoints, attackPower) {
    assert(speed >= 99999 && speed <= 299795);
}

XWing::XWing(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower)
        : Starship(shieldPoints), RebelStarship(shieldPoints, speed), Attacking(shieldPoints, attackPower) {
    
    assert(speed >= 299796 && speed <= 2997960);
}

std::shared_ptr<Explorer> createExplorer(ShieldPoints shieldPoints, Speed speed) {
    return std::make_shared<Explorer>(shieldPoints,speed);
}

std::shared_ptr<XWing> createXWing(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower) {
    return std::make_shared<XWing>(shieldPoints,speed,attackPower);
}

std::shared_ptr<StarCruiser> createStarCruiser(ShieldPoints shieldPoints, Speed speed, AttackPower attackPower) {
    return std::make_shared<StarCruiser>(shieldPoints,speed,attackPower);
}
