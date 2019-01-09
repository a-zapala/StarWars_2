#ifndef STARWARS_2_BATTLE_H
#define STARWARS_2_BATTLE_H


#include <iostream>
#include "rebelfleet.h"
#include "imperialfleet.h"

class battle {
public:
    void static foo() {
        auto explorer = createExplorer(150, 400000);
        auto xwing = createXWing(100, 300000, 40);
        auto cruiser = createStarCruiser(1234, 100000, 11);
        auto deathStar = createDeathStar(10000, 75);
        auto fighter = createTIEFighter(50, 9);
        auto destroyer = createImperialDestroyer(150, 20);
        auto squadron = createSquadron({deathStar, destroyer});
    
        std::cout << squadron->getShield() << std::endl;
        std::cout << fighter->getShield() << std::endl;
    
        auto p = std::shared_ptr<StarShip>(fighter);
        auto q = std::shared_ptr<StarShip>(squadron);
        squadron->maybeAttack(p);
        p->maybeAttack(q);
    
        std::cout << fighter->getShield() << std::endl;
        std::cout << squadron->getShield() << std::endl;
    }
};


#endif //STARWARS_2_BATTLE_H
