//
// Created by Kavi Palmer on 1/4/22.
//

#ifndef SPORTSBETMANAGER_BETNODE_H
#define SPORTSBETMANAGER_BETNODE_H

#include "SportsBet.h"

struct BetNode {
    SportsBet bet;
    BetNode *next;
};

#endif //SPORTSBETMANAGER_BETNODE_H
