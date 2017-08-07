//
//  QueueSystem.hpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/7.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef QueueSystem_hpp
#define QueueSystem_hpp

#include <stdio.h>
#include "Event.h"
#include "Queue.h"
#include "ServiceWindow.h"

class QueueSystem {
public:
    QueueSystem(int total_service_time, int window_num);
    ~QueueSystem();
    
    void simulate(int simulate_num);
    
    inline double getAvgStayTime() const {
        return avg_stay_time_;
    }
    inline double getAvgCustomers() const {
        return avg_customers_;
    }
    
private:
    
    double run();
    
    void init();
    
    void end();
    
    int getIdleServiceWindow();
    
    void customerArrived();
    
    void customerDeparture();
    
private:
    
    int window_num_;
    int total_service_time_;
    int total_customer_num_;
    int total_customer_stay_time_;
    
    ServiceWindow* windows_;
    Queue<Customer> customer_list_;
    Queue<Event> event_list_;
    Event* current_event_;
    
    double avg_customers_;
    double avg_stay_time_;
    
};

#endif /* QueueSystem_hpp */


