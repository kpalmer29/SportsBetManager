//b
// Created by Kavi Palmer on 1/6/22.
//

#include "SportsBetManager.h"


SportsBetManager::SportsBetManager(): numBets(0), betList(nullptr) {}

SportsBetManager::SportsBetManager(const SportsBetManager &rhs): numBets(rhs.numBets), betList(nullptr) { //alt ctor
    if (rhs.betList != nullptr) {
        betList = new BetNode;
        betList->bet = rhs.betList->bet;
        betList->next = nullptr;
        BetNode *newPtr = betList;
        BetNode *original = rhs.betList;
        while (original->next != nullptr) {
            original = original->next;
            newPtr->next = new BetNode;
            newPtr = newPtr->next;
            newPtr->bet = original->bet;
        }
        newPtr->next = nullptr;
    }
}

const SportsBetManager& SportsBetManager::operator=(const SportsBetManager &rhs) { //assignment op
    if (this != &rhs) {
        SportsBetManager temp(rhs);
        std::swap(betList, temp.betList);
        std::swap(numBets, temp.numBets);
    }
    return *this;
}

SportsBetManager::~SportsBetManager() { //destructor
    while (betList != nullptr) {
        BetNode* temp = betList;
        betList = betList -> next;
        delete temp;
    }
}

int SportsBetManager::getNumBets() const {
    return numBets;
}

//adds a bet to SportsBetManager. Bets stored based on date - earliest first - and are added
//at the appropriate point in the linked list according to the bet's date. If other bets
//exist on the same date, the param bet is added after those bets.
void SportsBetManager::addBet(const SportsBet &newBet) {
    if (exists(newBet))
        throw std::invalid_argument("Bet Already Exists");

    BetNode* temp = new BetNode; //create new node for new bet
    temp->bet = newBet;
    temp->next = nullptr;

    if (numBets == 0) { //base case
        betList = temp;
    }

    else {

        Date insertDate = newBet.getDate();

        if (insertDate < betList->bet.getDate()) { //bet should be added at beginning of list
            temp->next = betList;
            betList = temp;
        }

        else {

            BetNode* temp2 = betList;

            while (temp2 != nullptr && temp2 -> bet.getDate() <= insertDate) { //moves temp2 to insertion point
                temp2 = temp2 ->next;
            }

            BetNode* prev = betList;

            if (temp2  == nullptr) { //new bet should be inserted at end of list
                while (prev ->next != nullptr) {
                    prev = prev -> next;
                }
            }

            else {
                while (prev -> next != temp2) { //moves prev to one before temp2
                    prev = prev -> next;
                }

            }

            temp -> next = prev -> next;
            prev -> next = temp;
        }
    }
    numBets++;
}

//return true if the param bet is equal to any bets in the Manager
//otherwise, returns false
bool SportsBetManager::exists(const SportsBet &newBet) {
    if (numBets == 0)
        return false;

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp ->bet.equals(newBet))
            return true;
        temp = temp -> next;
    }

    return false; //bet does not exist in Manager

}

//returns a string of all bets which occur on param date
std::string SportsBetManager::getBetsOnDate(Date date) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsOnDate = 0; //counter

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp->bet.getDate() == date) {
            returnString.append(temp->bet.toString() + "\n"); //add bet to returnString
            numBetsOnDate++;
        }
        temp = temp -> next;
    }

    if (numBetsOnDate == 0)
        return "No bets stored for " + date.toString();

    else
        return returnString;

}

//returns a string of all bets placed against param team
std::string SportsBetManager::getBetsAgainst(const std::string &newBet) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsAgainst = 0; //counter

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp -> bet.getAgainst() == newBet) {
            returnString.append(temp->bet.toString() + "\n"); //append bet to returnString
            numBetsAgainst++;
        }
        temp = temp -> next;
    }

    if (numBetsAgainst == 0)
        return "No bets were placed against " + newBet;
    else
        return returnString;
}

//returns a string of all bets for a sport
std::string SportsBetManager::getBetsOfSport(const std::string &spt) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsOfSport = 0; //counter

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp -> bet.getSport() == spt) {
            returnString.append(temp->bet.toString() + "\n");
            numBetsOfSport++;
        }
        temp = temp -> next;
    }

    if (numBetsOfSport == 0)
        return "You do not have any current bets in" + spt;
    else
        return returnString;
}

//returns a string of all bets placed for a team
std::string SportsBetManager::getBetsFor(const std::string &newBet) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsFor = 0; //counter

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp -> bet.getFor() == newBet) {
            returnString.append(temp->bet.toString() + "\n");
            numBetsFor++;
        }
        temp = temp -> next;
    }

    if (numBetsFor == 0)
        return "You do not have any current bets for" + newBet;
    else
        return returnString;
}

//returns a string of all bets stored by the Manager
std::string SportsBetManager::getAllBets() const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;

    BetNode* temp = betList;

    while (temp != nullptr) {
        returnString.append(temp->bet.toString() + "\n");
        temp = temp -> next;
    }

    return returnString;
}

//deletes all bets in the manager
void SportsBetManager::deleteAllBets() {
    betList = nullptr;
    numBets = 0;
}

//deletes the specified bet from the Manager
void SportsBetManager::deleteBet(const SportsBet &oldBet) {
    if (!exists(oldBet))
        throw std::invalid_argument("Bet does not exist in current Manager");

    if (betList->bet == oldBet) //bet for deletion is first bet in Manager.
        betList = betList->next;

    else {

        BetNode *temp;

        for (temp = betList; temp != nullptr; temp = temp->next) {
            if (temp->bet == oldBet) { //temp points to node to be deleted
                BetNode *prev = betList;
                while (prev->next != temp) { //move prev to one before temp
                    prev = prev->next;
                }

                prev->next = temp->next; //assignment

            }
        }
    }
    numBets--;
}

//deletes all bets placed for a certain team
void SportsBetManager::deleteBetsFor(const std::string &oldBet) {
    if (numBets == 0)
        throw std::invalid_argument("Manager is empty");

    BetNode* curr;

    for (curr = betList; curr != nullptr; curr = curr -> next) {
        if (curr->bet.getFor() == oldBet) { //if curr is pointed towards a node to be deleted
            if (betList == curr) //base case
                betList = curr -> next;
            else {
                BetNode* prev;
                for (prev = betList; prev -> next != curr; prev = prev -> next) {}//move ptr to one before curr
                prev->next = curr -> next;
            }
            numBets--;
        }
    }
}

//delets all bets placed against a certain team
void SportsBetManager::deleteBetsAgainst(const std::string &oldBet) {
    if (numBets == 0)
        throw std::invalid_argument("Manager is empty");

    BetNode* curr;

    for (curr = betList; curr != nullptr; curr = curr -> next) {
        if (curr->bet.getAgainst() == oldBet) { //if curr is pointed towards a node to be deleted
            if (betList == curr) //base case
                betList = curr -> next;
            else {
                BetNode* prev;
                for (prev = betList; prev -> next != curr; prev = prev -> next) {}//move ptr to one before curr
                prev->next = curr -> next;
            }
            numBets--;
        }
    }
}

//deletes all bets before a specified date
std::string SportsBetManager::deleteBetsBefore(const Date &date) {
    if (numBets == 0)
        throw std::invalid_argument("Manager is empty");

    BetNode* temp;
    temp = betList;
    if (temp->bet.getDate() > date)
        return "No bets before date" + date.toString();

    else {
        int counter = 0;
        while (temp->bet.getDate() < date) {
            temp = temp -> next;
            counter++;
        }
        //temp now pointing to first node whose date is >= param
        betList = temp;
        numBets = numBets - counter;
        return "Done";
    }
}
