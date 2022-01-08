//
// Created by Kavi Palmer on 1/6/22.
//

#ifndef SPORTSBETMANAGER_SPORTSBETMANAGER_H
#define SPORTSBETMANAGER_SPORTSBETMANAGER_H

#include "SportsBet.h"
#include "Spread.h"
#include "OverUnder.h"
#include "Prop.h"
#include "BetNode.h"
#include <stdexcept>
#include <string>
#include <iostream>

class SportsBetManager {

private:

    int numBets; //number of bets
    BetNode* betList; //pointer of head to linked list

public:

    SportsBetManager();

    SportsBetManager(const SportsBetManager &rhs);

    const SportsBetManager &operator=(const SportsBetManager &rhs);

    ~SportsBetManager();

    int getNumBets() const;

    void addBet(const SportsBet &newBet);

    std::string getBetsOnDate(Date date) const;

    std::string getBetsFor(const std::string &newBet) const; //get all bets for param player/team

    std::string getBetsOfSport(const std::string &spt) const;

    std::string getBetsAgainst(const std::string &newBet) const;

    std::string getAllBets() const;

    void deleteAllBets();

    std::string deleteBetsBefore(const Date &date);

    void deleteBet(const SportsBet &oldBet);

    void deleteBetsFor(const std::string &oldBet);

    void deleteBetsAgainst(const std::string &oldBet);

    //void merge(const SportsBetManager &sbm);

    bool exists(const SportsBet &newBet);



};


#endif //SPORTSBETMANAGER_SPORTSBETMANAGER_H
