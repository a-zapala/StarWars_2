#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include "helper.h"
#include <cassert>
#include <iostream>

using namespace std;

int main() {

    // starwars_example
    auto xwing = createXWing(100.0f, 300000.0f, 50.0f);
    auto explorer = createExplorer(150, 400000);
    auto cruiser = createStarCruiser(1234, 100000, 11);
    auto deathStar = createDeathStar(10000, 75);
    auto fighter = createTIEFighter(50, 9);
    auto destroyer = createImperialDestroyer(150, 20);

    //get tests
    assert(xwing->getShield() == 100);
    assert(xwing->getSpeed() == 300000);
    //assert(xwing->getAttackPower() == 50);
    //assert(explorer->getAttackPower() == 23); //expected error
    assert(fighter->getAttackPower() == 9);
    assert(fighter->getShield() == 50);

    auto spaceTime = std::make_shared<PastSpaceTime>(1, 23, std::make_shared<PastAttackTime>());

    auto battle = SpaceBattle::Builder()
            .startTime(1)
            .maxTime(23)
            .ship(deathStar)
            .ship(explorer)
            .ship(fighter)
            .ship(xwing)
            .spaceTimeKind(spaceTime)
            .build();

    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 2);

    battle.tick(2);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(1);
    assert(battle.countRebelFleet() == 2);
    assert(battle.countImperialFleet() == 1);

    battle.tick(4);
    assert(battle.countRebelFleet() == 0);
    assert(battle.countImperialFleet() == 1);

    cout << "Starwars example correct answer: " << "IMPERIUM WON" << endl;

    battle.tick(1); // Wypisuje "IMPERIUM WON\n".

    //starwars_example_end

    // time_test

    //static assert errors
    //auto battle_time1 = SpaceBattle::Builder().startTime(-1).maxTime(8).build();
    //auto battle_time2 = SpaceBattle::Builder().startTime(9).maxTime(8).build();

    // require getCurrentTimeFunction
//    auto getCurrentTime(){
//        return currentTime;
//    }

//    auto spaceTime2 = std::make_shared<PastSpaceTime>(4, 45, std::make_shared<PastAttackTime>());
//
//    auto battle_time = SpaceBattle::Builder().spaceTimeKind(spaceTime2).build();
//
//    battle_time.tick(23);
//    assert(spaceTime2->getCurrentTime() == 27);
//
//    battle_time.tick(37);
//    assert(spaceTime2->getCurrentTime() == 18);
//
//    battle_time.tick(37);
//    assert(spaceTime2->getCurrentTime() == 9);
//
//    battle_time.tick(36);
//    assert(spaceTime2->getCurrentTime() == 45);
//
//    battle_time.tick(1);
//    assert(spaceTime2->getCurrentTime() == 0);

    //time_test_end


    // just_one_fraction

    // just rebelships
    auto battle_just_rebel = SpaceBattle::Builder()
            .startTime(2)
            .startTime(23)
            .ship(cruiser)
            .ship(explorer)
            .ship(xwing)
            .spaceTimeKind(std::make_shared<PastSpaceTime>(2, 23, std::make_shared<PastAttackTime>()))
            .build();

    cout << endl << "Just rebelships correct answer: " << "REBELLION WON" << endl;

    battle_just_rebel.tick(1); // "REBELLION WON\n"


    // just imperialships
    auto battle_just_imperial = SpaceBattle::Builder()
            .startTime(2)
            .maxTime(23)
            .ship(deathStar)
            .ship(fighter)
            .build();

    cout << endl << "Just imperialships correct answer: " << "IMPERIUM WON" << endl;

    battle_just_imperial.tick(1); // "IMPERIUM WON\n"


    // just_one_fraction_end

    // empty_battle

    auto battle_empty = SpaceBattle::Builder().maxTime(45).startTime(4).build();

    cout << endl << "Empty battle correct answer: " << "DRAW" << endl;

    battle_empty.tick(1000000); // "DRAW\n"

    // empty_battle_end

    // normal battles

    //battle2
    auto xwing21 = createXWing(35.0f, 300000.0f, 15.0f);
    auto xwing22 = createXWing(35.0f, 300000.0f, 15.0f);
    auto explorer2 = createExplorer(75, 400000);
    auto cruiser2 = createStarCruiser(62, 100000, 41);
    auto deathStar2 = createDeathStar(90, 30);
    auto fighter21 = createTIEFighter(15, 2);
    auto fighter22 = createTIEFighter(15, 2);
    auto destroyer2 = createImperialDestroyer(35, 10);
    auto battle2 = SpaceBattle::Builder()
            .startTime(6)
            .maxTime(36)
            .ship(xwing21)
            .ship(xwing22)
            .ship(deathStar2)
            .ship(explorer2)
            .ship(fighter21)
            .ship(fighter22)
            .ship(destroyer2)
            .ship(cruiser2)
            .spaceTimeKind(std::make_shared<PastSpaceTime>(6, 36, std::make_shared<PastAttackTime>()))
            .build();

    assert(battle2.countRebelFleet() == 4);
    assert(battle2.countImperialFleet() == 4);

    battle2.tick(3); //6
    assert(battle2.countRebelFleet() == 4);
    assert(battle2.countImperialFleet() == 4);

    battle2.tick(3); //9
    assert(battle2.countRebelFleet() == 2);
    assert(battle2.countImperialFleet() == 1);
    //status: 0 0 19 35 0 0 0 22

    battle2.tick(24); //12
    assert(battle2.countRebelFleet() == 2);
    assert(battle2.countImperialFleet() == 1);

    battle2.tick(1); //36
    assert(battle2.countRebelFleet() == 1);
    assert(battle2.countImperialFleet() == 0);
    //status: 0 0 0 5 0 0 0 0

    cout << endl << "Battle2 correct answer: " << "REBELLION WON" << endl;

    battle2.tick(1); // "REBELLION WON\n"

    // battle3
    auto xwing32 = createXWing(35, 300000, 15);
    auto xwing31 = createXWing(45.0f, 300000.0f, 10.0f);
    auto fighter31 = createTIEFighter(37, 20);
    auto fighter32 = createTIEFighter(42, 7);

    auto battle3 = SpaceBattle::Builder()
            .startTime(3)
            .maxTime(10)
            .ship(fighter31)
            .ship(xwing32)
            .ship(xwing31)
            .ship(fighter32)
            .spaceTimeKind(std::make_shared<PastSpaceTime>(3, 10, std::make_shared<PastAttackTime>()))
            .build();

    assert(battle3.countRebelFleet() == 2);
    assert(battle3.countImperialFleet() == 2);

    battle3.tick(8); //3
    assert(battle3.countRebelFleet() == 2);
    assert(battle3.countImperialFleet() == 2);

    battle3.tick(1); //0
    assert(battle3.countRebelFleet() == 2);
    assert(battle3.countImperialFleet() == 2);
    // status: 12 8 18 17

    battle3.tick(8); //1
    assert(battle3.countRebelFleet() == 1);
    assert(battle3.countImperialFleet() == 1);
    // status: 0 0 11 7

    battle3.tick(1); //9
    assert(battle3.countRebelFleet() == 1);
    assert(battle3.countImperialFleet() == 0);
    // status: 0 0 4 0

    cout << endl << "Battle3 correct answer: " << "REBELLION WON" << endl;

    battle3.tick(0); // "REBELLION WON\n"

    //battle4
    auto cruiser4 = createStarCruiser(123, 100000, 80);
    auto deathStar4 = createDeathStar(100, 75);
    // starship with shield = 0
    auto xwing41 = createXWing(0, 2997960, 3);
    // starship with shield = -1
    auto xwing42 = createXWing(-1, 299796, 3);

    auto battle4 = SpaceBattle::Builder()
            .startTime(2)
            .maxTime(4)
            .ship(cruiser4)
            .ship(deathStar4)
            .ship(xwing41)
            .ship(xwing42)
            .spaceTimeKind(std::make_shared<PastSpaceTime>(2, 4, std::make_shared<PastAttackTime>()))
            .build();

    battle4.tick(2); //2
    assert(battle4.countRebelFleet() == 1);
    assert(battle4.countImperialFleet() == 1);

    battle4.tick(2); //4
    assert(battle4.countRebelFleet() == 1);
    assert(battle4.countImperialFleet() == 1);

    battle4.tick(2); //1
    assert(battle4.countRebelFleet() == 0);
    assert(battle4.countImperialFleet() == 0);

    cout << endl << "Battle4 correct answer: " << "DRAW" << endl;
    battle4.tick(0); // "DRAW\n"

    // normal_battles_end

    // const starships
    const auto cruiser_const = StarCruiser(123, 100000, 80);
    const auto deathStar_const = createDeathStar(100, 75);
    const auto explorer_const = createExplorer(150, 400000);

    // get tests
    assert(cruiser_const.getShield() == 123);
    assert(cruiser_const.getAttackPower() == 80);
    assert(cruiser_const.getSpeed() == 100000);
    assert(deathStar_const->getAttackPower() == 75);
    assert(deathStar_const->getShield() == 100);
    assert(explorer_const->getSpeed() == 400000);
    assert(explorer_const->getShield() == 150);
    //assert(explorer_const->getAttackPower() == 3); //expected error

    // const_strarships_end

}
