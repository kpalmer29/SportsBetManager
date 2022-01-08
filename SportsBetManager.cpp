//b
// Created by Kavi Palmer on 1/6/22.
//

#include "SportsBetManager.h"


SportsBetManager::SportsBetManager(): numBets(0), betList(nullptr) {}

SportsBetManager::SportsBetManager(const SportsBetManager &rhs): numBets(rhs.numBets), betList(nullptr) {
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

const SportsBetManager& SportsBetManager::operator=(const SportsBetManager &rhs) {
    if (this != &rhs) {
        SportsBetManager temp(rhs);
        std::swap(betList, temp.betList);
        std::swap(numBets, temp.numBets);
    }
    return *this;
}

SportsBetManager::~SportsBetManager() {
    while (betList != nullptr) {
        BetNode* temp = betList;
        betList = betList -> next;
        delete temp;
    }
}

int SportsBetManager::getNumBets() const {
    return numBets;
}

void SportsBetManager::addBet(const SportsBet &newBet) {
    if (exists(newBet))
        throw std::invalid_argument("Bet Already Exists");

    BetNode* temp = new BetNode;
    temp->bet = newBet;
    temp->next = nullptr;
    if (numBets == 0) {
        betList = temp;
    }

    else {

        Date insertDate = newBet.getDate();

        if (insertDate < betList->bet.getDate()) {
            temp->next = betList;
            betList = temp;
        }

        else {

            BetNode* temp2 = betList;

            while (temp2 != nullptr && temp2 -> bet.getDate() <= insertDate) { //moves temp2 to insertion point
                temp2 = temp2 ->next;
            }

            BetNode* prev = betList;

            if (temp2  == nullptr) {
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

bool SportsBetManager::exists(const SportsBet &newBet) {
    if (numBets == 0)
        return false;

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp ->bet.equals(newBet))
            return true;
        temp = temp -> next;
    }

    return false;

}

std::string SportsBetManager::getBetsOnDate(Date date) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsOnDate = 0;

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp->bet.getDate() == date) {
            returnString.append(temp->bet.toString() + "\n");
            numBetsOnDate++;
        }
        temp = temp -> next;
    }

    if (numBetsOnDate == 0)
        return "No bets stored for " + date.toString();

    else
        return returnString;

}

std::string SportsBetManager::getBetsAgainst(const std::string &newBet) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsAgainst = 0;

    BetNode* temp = betList;

    while (temp != nullptr) {
        if (temp -> bet.getAgainst() == newBet) {
            returnString.append(temp->bet.toString() + "\n");
            numBetsAgainst++;
        }
        temp = temp -> next;
    }

    if (numBetsAgainst == 0)
        return "No bets were placed against " + newBet;
    else
        return returnString;
}

std::string SportsBetManager::getBetsOfSport(const std::string &spt) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsOfSport = 0;

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

std::string SportsBetManager::getBetsFor(const std::string &newBet) const {
    if (numBets == 0)
        return "This Sports Bet Manager is empty";

    std::string returnString;
    int numBetsFor = 0;

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

void SportsBetManager::deleteAllBets() {
    betList = nullptr;
    numBets = 0;
}

void SportsBetManager::deleteBet(const SportsBet &oldBet) {
    if (!exists(oldBet))
        throw std::invalid_argument("Bet does not exist in current Manager");

    if (betList->bet == oldBet)
        betList = betList->next;

    else {

        BetNode *temp;

        for (temp = betList; temp != nullptr; temp = temp->next) {
            if (temp->bet == oldBet) {
                BetNode *prev = betList;
                while (prev->next != temp) {
                    prev = prev->next;
                }

                prev->next = temp->next;

            }
        }
    }
    numBets--;
}

void SportsBetManager::deleteBetsFor(const std::string &oldBet) {
    if (numBets == 0)
        throw std::invalid_argument("Manager is empty");

    BetNode* curr;

    for (curr = betList; curr != nullptr; curr = curr -> next) {
        if (curr->bet.getFor() == oldBet) {
            if (betList == curr)
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

void SportsBetManager::deleteBetsAgainst(const std::string &oldBet) {
    if (numBets == 0)
        throw std::invalid_argument("Manager is empty");

    BetNode* curr;

    for (curr = betList; curr != nullptr; curr = curr -> next) {
        if (curr->bet.getAgainst() == oldBet) {
            if (betList == curr)
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

//void SportsBetManager::merge(const SportsBetManager &sbm) {
//    if (sbm.numBets == 0)
//        return;
//
//    if (numBets == 0)
//        betList = sbm.betList;
//
//    BetNode* list1ptr = betList;
//    BetNode* list2ptr = sbm.betList;
//
//    while (list1ptr != nullptr && list2ptr != nullptr) {
//        if (list2ptr == nullptr)
//            list1ptr = list1ptr -> next;
//        else if (list1ptr == nullptr) {
//            BetNode* temp = betList;
//            while (temp-> next != nullptr) {
//                temp = temp -> next;
//            }
//            temp -> next = list2ptr;
//        }
//
//
//        if (list1ptr -> bet.getDate() <= list2ptr -> bet.getDate())
//            list1ptr = list1ptr -> next;
//    }
//
//}