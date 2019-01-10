#ifndef STARWARS_2_BATTLE_H
#define STARWARS_2_BATTLE_H

#include <iostream>
#include <vector>
#include "rebelfleet.h"
#include "imperialfleet.h"
#include "helper.h"

class Battle {
public:
    NumberOfShips countRebelFleet() const;
    NumberOfShips countImperialFleet() const;
    void tick(Time timeStep);

    Battle(const std::vector<std::shared_ptr<ImperialStarShip>> &imperialShips,
           const std::vector<std::shared_ptr<RebelStarShip>> &rebelShips,
           Time t0, Time t1, const std::shared_ptr<SpaceTime> &sTime);

private:
    std::vector<std::shared_ptr<ImperialStarShip>> imperialShips;
    std::vector<std::shared_ptr<RebelStarShip>> rebelShips;
    Time t0;
    Time t1;
    std::shared_ptr<SpaceTime> spaceTime;
    Time currentTime;

    void fight();
//public:
//    void static foo() {
//            auto explorer = createExplorer(150, 400000);
//            auto xwing = createXWing(100, 300000, 40);
//            auto cruiser = createStarCruiser(1234, 100000, 11);
//            auto deathStar = createDeathStar(10000, 75);
//            auto fighter = createTIEFighter(50, 9);
//            auto destroyer = createImperialDestroyer(150, 20);
//            auto squadron = createSquadron({deathStar, destroyer});
//
//            std::cout << squadron->getShield() << std::endl;
//            std::cout << fighter->getShield() << std::endl;
//
//            auto p = std::shared_ptr<StarShip>(fighter);
//            auto q = std::shared_ptr<StarShip>(squadron);
//            squadron->maybeAttack(p);
//            p->maybeAttack(q);
//
//            std::cout << fighter->getShield() << std::endl;
//            std::cout << squadron->getShield() << std::endl;
//    }
};

namespace SpaceBattle {

    class Builder{
    public:
        Builder& startTime(Time t);
        Builder& maxTime(Time t);
        Builder& spaceTimeKind(std::shared_ptr<SpaceTime> &sTime);
        Builder& ship(std::shared_ptr<ImperialStarShip> &imperialShip);
        Builder& ship(std::shared_ptr<RebelStarShip> &rebelShip);
        Battle build();

        Builder();

    private:
        std::vector<std::shared_ptr<ImperialStarShip>> imperialShips;
        std::vector<std::shared_ptr<RebelStarShip>> rebelShips;
        Time t0 = 0;
        Time t1 = 1;
        std::shared_ptr<SpaceTime> spaceTime;
    };

}

#endif //STARWARS_2_BATTLE_H
