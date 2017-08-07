//
//  Node.h
//  smart_pointer
//
//  Created by wuminhui on 2017/8/7.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include "Random.h"

#define RANDOM_PARAMETER 100

struct Node {
    int arrive_time;
    int duration;
    struct Node* next;
    
    Node(int arrive_time = 0,
         int duration = Random::getRandom(EXPONENTAIL, 0.1)):
    arrive_time(arrive_time),
    duration(duration),
    next(nullptr) {}
};


typedef struct Node Node;
typedef struct Node Customer;


#endif /* Node_h */


