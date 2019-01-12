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
           Time t0, Time t1);

    Battle(const std::vector<std::shared_ptr<ImperialStarShip>> &imperialShips,
           const std::vector<std::shared_ptr<RebelStarShip>> &rebelShips,
           const std::shared_ptr<SpaceTime> sTime);

private:
    std::vector<std::shared_ptr<ImperialStarShip>> imperialShips;
    std::vector<std::shared_ptr<RebelStarShip>> rebelShips;
    std::shared_ptr<SpaceTime> spaceTime;

    void fight();
};

namespace SpaceBattle {

    class Builder{
    public:
        Builder& startTime(Time t);
        Builder& maxTime(Time t);
        Builder& spaceTimeKind(std::shared_ptr<SpaceTime> sTime);
        Builder& ship(std::shared_ptr<ImperialStarShip> imperialShip);
        Builder& ship(std::shared_ptr<RebelStarShip> rebelShip);
        Battle build();

    private:
        std::vector<std::shared_ptr<ImperialStarShip>> imperialShips;
        std::vector<std::shared_ptr<RebelStarShip>> rebelShips;
        Time t0 = 0;
        Time t1 = 1;
        std::shared_ptr<SpaceTime> spaceTime;
    };
}

#endif //STARWARS_2_BATTLE_H
