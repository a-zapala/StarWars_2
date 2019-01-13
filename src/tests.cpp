#include "rebelfleet.h"
#include "imperialfleet.h"
#include "battle.h"
#include "helper.h"
#include <cassert>
#include <iostream>
#include <vector>

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
    assert(xwing->getAttackPower() == 50);
    //assert(explorer->getAttackPower() == 23); //expected error
    assert(fighter->getAttackPower() == 9);
    assert(fighter->getShield() == 50);

    auto spaceTime = std::make_shared<DefaultSpaceTime>(1, 23, std::make_shared<PastAttackTime>());

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

//    auto spaceTime2 = std::make_shared<DefaultSpaceTime>(4, 45, std::make_shared<PastAttackTime>());
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
            .spaceTimeKind(std::make_shared<DefaultSpaceTime>(2, 23, std::make_shared<PastAttackTime>()))
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
            .spaceTimeKind(std::make_shared<DefaultSpaceTime>(6, 36, std::make_shared<PastAttackTime>()))
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
            .spaceTimeKind(std::make_shared<DefaultSpaceTime>(3, 10, std::make_shared<PastAttackTime>()))
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
            .spaceTimeKind(std::make_shared<DefaultSpaceTime>(2, 4, std::make_shared<PastAttackTime>()))
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


    //old tests, new attackTime

    // just_one_faction

    // just rebelships
    auto battleBuilder = SpaceBattle::Builder();
    battleBuilder
            .startTime(2)
            .maxTime(23)
            .ship(createStarCruiser(100, 100000, 10))
            .ship(createExplorer(10, 1000000))
            .ship(createXWing(10, 1000000, 1));

    auto battle_just_rebel2 = battleBuilder.build();

    cout << endl << "Just rebelships correct answer: " << "REBELLION WON" << endl;

    battle_just_rebel2.tick(1); // "REBELLION WON\n"


    // just imperialships
    battleBuilder = SpaceBattle::Builder();

    battleBuilder
            .startTime(2)
            .maxTime(23)
            .ship(createDeathStar(1000, 10000))
            .ship(createImperialDestroyer(200, 15));

    auto battle_just_imperial2 = battleBuilder.build();

    cout << endl << "Just imperialships correct answer: " << "IMPERIUM WON" << endl;

    battle_just_imperial2.tick(1); // "IMPERIUM WON\n"


    // just_one_faction_end

    // empty_battle

    battleBuilder = SpaceBattle::Builder();
    battleBuilder.startTime(4).maxTime(45);

    auto battle_empty2 = battleBuilder.build();

    cout << endl << "Empty battle correct answer: " << "DRAW" << endl;

    battle_empty2.tick(1000000); // "DRAW\n"

    // empty_battle_end

    // normal battles

    //battle5

    battleBuilder = SpaceBattle::Builder();

    battleBuilder.startTime(6).maxTime(36)
            .ship(createXWing(35, 300000, 15))
            .ship(createXWing(35, 300000, 15))
            .ship(createExplorer(75, 400000))
            .ship(createStarCruiser(62, 100000, 41))
            .ship(createDeathStar(90, 30))
            .ship(createTIEFighter(15, 2))
            .ship(createTIEFighter(15, 2))
            .ship(createImperialDestroyer(35, 10));

    auto battle5 = battleBuilder.build();

    assert(battle5.countRebelFleet() == 4);
    assert(battle5.countImperialFleet() == 4);

    battle5.tick(9);
    assert(battle5.countRebelFleet() == 2);
    assert(battle5.countImperialFleet() == 1);

    battle5.tick(2);
    assert(battle5.countRebelFleet() == 2);
    assert(battle5.countImperialFleet() == 1);

    battle5.tick(5);
    assert(battle5.countRebelFleet() == 2);
    assert(battle5.countImperialFleet() == 1);

    battle5.tick(1);
    assert(battle5.countRebelFleet() == 1);
    assert(battle5.countImperialFleet() == 0);

    cout << endl << "Battle5 correct answer: " << "REBELLION WON" << endl;

    battle5.tick(1); // "REBELLION WON\n"

    // battle6

    battleBuilder = SpaceBattle::Builder();

    battleBuilder.startTime(5).maxTime(10)
            .ship(createXWing(35, 300000, 15))
            .ship(createXWing(45, 300000, 10))
            .ship(createTIEFighter(37, 20))
            .ship(createTIEFighter(42, 7));

    auto battle6 = battleBuilder.build();

    assert(battle6.countRebelFleet() == 2);
    assert(battle6.countImperialFleet() == 2);

    battle6.tick(6); //5
    assert(battle6.countRebelFleet() == 2);
    assert(battle6.countImperialFleet() == 2);

    battle6.tick(2); //0
    assert(battle6.countRebelFleet() == 2);
    assert(battle6.countImperialFleet() == 2);

    battle6.tick(1); //2
    assert(battle6.countRebelFleet() == 2);
    assert(battle6.countImperialFleet() == 2);
    // status: 12 8 18 17

    battle6.tick(11); //3
    assert(battle6.countRebelFleet() == 1);
    assert(battle6.countImperialFleet() == 1);
    // status: 0 0 11 7

    battle6.tick(1); //4
    assert(battle6.countRebelFleet() == 1);
    assert(battle6.countImperialFleet() == 0);
    // status: 0 0 4 0

    cout << endl << "Battle6 correct answer: " << "REBELLION WON" << endl;

    battle6.tick(0); // "REBELLION WON\n"

    //battle7

    battleBuilder = SpaceBattle::Builder();

    battleBuilder.startTime(1).maxTime(4)
            .ship(createStarCruiser(123, 100000, 80))
            .ship(createDeathStar(100, 75));

    auto battle7 = battleBuilder.build();

    battle7.tick(3); //1
    assert(battle7.countRebelFleet() == 1);
    assert(battle7.countImperialFleet() == 1);

    battle7.tick(3); //4
    assert(battle7.countRebelFleet() == 1);
    assert(battle7.countImperialFleet() == 1);

    battle7.tick(2); //2
    assert(battle7.countRebelFleet() == 0);
    assert(battle7.countImperialFleet() == 0);

    cout << endl << "Battle7 correct answer: " << "DRAW" << endl;
    battle7.tick(0); // "DRAW\n"

    //battle8

    battleBuilder = SpaceBattle::Builder();

    battleBuilder.startTime(6).maxTime(36)
            .ship(createXWing(35, 300000, 15))
            .ship(createXWing(35, 300000, 15))
            .ship(createExplorer(75, 400000))
            .ship(createStarCruiser(62, 100000, 21))
            .ship(createDeathStar(90, 30))
            .ship(createSquadron({createTIEFighter(15, 3), createTIEFighter(15, 3)}))
            .ship(createImperialDestroyer(35, 10));

    auto battle8 = battleBuilder.build();

    assert(battle8.countRebelFleet() == 4);
    assert(battle8.countImperialFleet() == 4);

    battle8.tick(9); //6
    assert(battle8.countRebelFleet() == 2);
    assert(battle8.countImperialFleet() == 1);
    //status: 0 0 35 22 39 0 0 0

    battle8.tick(2); //15
    assert(battle8.countRebelFleet() == 2);
    assert(battle8.countImperialFleet() == 1);

    battle8.tick(5); //17
    assert(battle8.countRebelFleet() == 2);
    assert(battle8.countImperialFleet() == 1);

    battle8.tick(2); //22
    assert(battle8.countRebelFleet() == 1);
    assert(battle8.countImperialFleet() == 1);
    //status: 0 0 5 0 18 0 0 0

    battle8.tick(1); //24
    assert(battle8.countRebelFleet() == 0);
    assert(battle8.countImperialFleet() == 1);
    //status: 0 0 0 0 18 0 0 0

    cout << endl << "Battle8 correct answer: " << "IMPERIUM WON" << endl;

    battle8.tick(1); // "IMPERIUM WON\n"

    //battle9

    battleBuilder = SpaceBattle::Builder();

    battleBuilder.startTime(6).maxTime(36)
            .ship(createXWing(35, 300000, 15))
            .ship(createXWing(35, 300000, 15))
            .ship(createExplorer(75, 400000))
            .ship(createStarCruiser(85, 100000, 41))
            .ship(createSquadron({createDeathStar(90, 30), createTIEFighter(16, 5)}))
            .ship(createSquadron(std::vector<std::shared_ptr<ImperialStarship>>({createTIEFighter(15, 5),
                                                                                 createImperialDestroyer(42, 10)})));

    auto battle9 = battleBuilder.build();

    assert(battle9.countRebelFleet() == 4);
    assert(battle9.countImperialFleet() == 4);

    battle9.tick(9); //6
    assert(battle9.countRebelFleet() == 2);
    assert(battle9.countImperialFleet() == 2);
    //status: 0 0 30 20 19 0 0 1

    battle9.tick(2); //15
    assert(battle9.countRebelFleet() == 2);
    assert(battle9.countImperialFleet() == 2);

    battle9.tick(5); //17
    assert(battle9.countRebelFleet() == 2);
    assert(battle9.countImperialFleet() == 2);

    battle9.tick(1); //22
    assert(battle9.countRebelFleet() == 0);
    assert(battle9.countImperialFleet() == 0);
    //status: 0 0 0 0 0 0 0 0

    cout << endl << "Battle9 correct answer: " << "DRAW" << endl;

    battle9.tick(1); // "DRAW\n"
}
