//
//  Event.h
//  smart_pointer
//
//  Created by wuminhui on 2017/8/7.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef Event_h
#define Event_h

#include "Random.h"

#define RANDOM_PARAMETER 100

struct Event {
    int occur_time;
    
    // -1 : arrive event, >=0 : leave event and the number is the service window number
    int event_type;
    
    Event* next;
    
    Event(int occur_time = Random::getRandom(POISSON, 0.5), int event_type = -1): //int occur_time = Random::uniform(RANDOM_PARAMETER), int event_type = -1):
    occur_time(occur_time),
    event_type(event_type),
    next(nullptr) {}
};


#endif /* Event_h */
