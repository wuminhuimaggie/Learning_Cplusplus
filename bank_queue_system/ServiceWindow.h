//
//  ServiceWindow.h
//  smart_pointer
//
//  Created by wuminhui on 2017/8/7.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef ServiceWindow_h
#define ServiceWindow_h

#include "Node.h"

enum WindowStatus {
    SERVICE,
    IDLE,
};

class ServiceWindow {
public:
    
    inline ServiceWindow() : window_status_(IDLE) {}
    
    inline bool isIdle() const {
        return (window_status_ == IDLE) ? true : false;
    }
    
    inline void serveCustomer(const Customer& customer) {
        this->customer_ = customer;
    }
    inline void setBusy() { window_status_ = SERVICE; }
    inline void setIdle() { window_status_ = IDLE; }
    
    inline int getCustomerArriveTime() const { return customer_.arrive_time; }
    inline int getCustomerDuration() const { return customer_.duration; }
    
private:
    Customer customer_;
    WindowStatus window_status_;
    
};


#endif /* ServiceWindow_h */


