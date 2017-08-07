//
//  Queue.h
//  smart_pointer
//
//  Created by wuminhui on 2017/8/7.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <iostream>
#include <cstdlib>

#include "Event.h"

template<typename T>
class Queue {
public:
    Queue() {
        front_ = new T;
        if(front_ == nullptr) exit(-1);
        
        front_->next = nullptr;
        rear_ = front_;
    }
    ~Queue() {
        clearQueue();
        if(front_) delete front_;
    }
    
    void clearQueue() {
        T* temp_node = nullptr;
        while(front_->next) {
            temp_node = front_->next;
            front_->next = temp_node->next;
            delete temp_node;
        }
        
        front_->next = nullptr;
        rear_ = front_;
    }
    
    T* enqueue(T& node) {
        T* new_node = new T;
        if(!new_node) exit(-1);
        
        *new_node = node;
        rear_->next = new_node;
        rear_ = new_node;
        return front_;
    }
    T* dequeue() {
        if(front_->next == nullptr) return nullptr;
        
        T* temp_node = front_->next;
        front_->next = temp_node->next;
        
        if(rear_ == temp_node) rear_ = front_;
        return temp_node;
    }
    
    // 当作为事件时的顺序插入
    T* orderEnqueue(Event &event) {
        Event* temp = new Event;
        if (!temp) {
            exit(-1);
        }
        *temp = event;
        
        // 如果这个列表里没有事件, 则把 temp 事件插入
        if (!front_->next) {
            this->enqueue(*temp);
            return front_;
        }
        
        // 按时间顺序插入
        Event *temp_event_list = front_;
        // 如果有下一个事件，且下一个事件的发生时间小于要插入的时间的时间，则继>续将指针后移
        while (temp_event_list->next && temp_event_list->next->occur_time < event.occur_time) {
            temp_event_list = temp_event_list->next;
        }
        
        // 将事件插入到队列中
        temp->next = temp_event_list->next;
        temp_event_list->next = temp;
        
        return front_;
    }
    
    int length() {
        T* temp_node = front_->next;
        int len = 0;
        while(temp_node) {
            temp_node = temp_node->next;
            len++;
        }
        return len;
    }
private:
    T* front_;
    T* rear_;
};


#endif /* Queue_h */

