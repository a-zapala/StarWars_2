#include "battle.h"


NumberOfShips Battle::countRebelFleet() const {
    NumberOfShips numberOfShips = 0;

    for (auto &ship: rebelShips) {
        numberOfShips += ship->howManyUndestroyedUnits();
    }

    return numberOfShips;
}

NumberOfShips Battle::countImperialFleet() const {
    NumberOfShips numberOfShips = 0;

    for (auto &ship: imperialShips) {
        numberOfShips += ship->howManyUndestroyedUnits();
    }

    return numberOfShips;
}


void Battle::tick(Time timeStep) {
    NumberOfShips rebelFleet = countRebelFleet(), imperialFleet = countImperialFleet();

    if(rebelFleet == 0 && imperialFleet == 0) {
        std::cout << "DRAW\n" << std::endl;
    }
    else if (imperialFleet == 0) {
        std::cout << "REBELION WON\n" << std::endl;
    }
    else if (rebelFleet == 0) {
        std::cout << "IMPERIUM WON\n" << std::endl;
    }
    else {

        if (spaceTime->isItAttackTime(currentTime)) {
            fight();
        }

        currentTime += timeStep;
        currentTime %= (t1 + 1);
    }
}

Battle::Battle(const std::vector<std::shared_ptr<ImperialStarShip>> &imperialShips,
               const std::vector<std::shared_ptr<RebelStarShip>> &rebelShips,
               Time t0, Time t1, const std::shared_ptr<SpaceTime> &sTime):
               imperialShips(imperialShips),
               rebelShips(rebelShips),
               t0(t0), t1(t1), spaceTime(sTime) {
    currentTime = t0;
}

void Battle::fight() {
    for (auto &imperialShip: imperialShips) {
        for (auto &rebelShip: rebelShips) {
            if (imperialShip->getShield() > 0 && rebelShip->getShield() > 0) {
                // here possibly we can make it smarter than casting every time we want to attack
                std::shared_ptr<StarShip> iShip = std::static_pointer_cast<StarShip>(imperialShip);
                std::shared_ptr<StarShip> rShip = std::static_pointer_cast<StarShip>(rebelShip);
                imperialShip->Attack(rShip);
                rebelShip->Attack(iShip);
            }
        }
    }
}

SpaceBattle::Builder& SpaceBattle::Builder::startTime(Time t) {
    t0 = t;
    return *this;
}

SpaceBattle::Builder& SpaceBattle::Builder::maxTime(Time t) {
    t1 = t;
    return *this;
}

SpaceBattle::Builder& SpaceBattle::Builder::spaceTimeKind(std::shared_ptr<SpaceTime> &sTime) {
    spaceTime = sTime;
    return *this;
}

SpaceBattle::Builder& SpaceBattle::Builder::ship(std::shared_ptr<ImperialStarShip> &imperialShip) {
    imperialShips.push_back(imperialShip);
    return *this;
}

SpaceBattle::Builder& SpaceBattle::Builder::ship(std::shared_ptr<RebelStarShip> &rebelShip) {
    rebelShips.push_back(rebelShip);
    return *this;
}

Battle SpaceBattle::Builder::build() {
    return Battle(imperialShips, rebelShips, t0, t1, spaceTime);
}

SpaceBattle::Builder::Builder(): spaceTime(std::make_shared<DefaultSpaceTime>()) {}