//
//  smartpointer.h
//  smart_pointer
//
//  Created by wuminhui on 2017/8/4.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef smartpointer_h
#define smartpointer_h

#include <iostream>

template< typename T >
class SmartPointer {
public:
    SmartPointer(): mPointer(nullptr) {
        std::cout << "create unknown smart pointer." << std::endl;
    }
    SmartPointer(T* p): mPointer(p) {
        std::cout << "create smart pointer at " << static_cast<const void*>(p) << std::endl;
        if(mPointer) mPointer->incRefCount();
    }
    //copy constructor
    SmartPointer(const SmartPointer& other): mPointer(other.mPointer) {
        std::cout <<"copy smart pointer at " << static_cast<const void*>(other.mPointer) << std::endl;
        if(mPointer) mPointer->incRefCount();
    }
    //assign operator
    SmartPointer& operator=(const SmartPointer& other) {
        T* temp(other.mPointer);
        if(temp) temp->incRefCount();
        if(mPointer && mPointer->decRefCount() == 0) delete mPointer;
        mPointer = temp;
        std::cout << "Assign smart pointer at " << static_cast<const void*>(other.mPointer) << std::endl;
        return *this;
    }
    ~SmartPointer() {
        std::cout << "release smart pointer at " << static_cast<const void*>(mPointer) << std::endl;
        if(mPointer && mPointer->decRefCount() == 0) delete mPointer;
    }
    
    //override * and ->
    T& operator*() const { return *mPointer; };
    T* operator->() const { return mPointer; };
    
    bool operator ==(const SmartPointer& o) const {
        return mPointer == o.mPointer;
    }
    bool operator ==(const T* o) const {
        return mPointer == o;
    }
    
    bool operator !=(const SmartPointer& o) const {
        return mPointer != o.mPointer;
    }
    bool operator !=(const T* o) const {
        return mPointer != o;
    }
    
private:
    T *mPointer;
};

class RefBase {
public:
    RefBase(): mCount(0) {}
    virtual ~RefBase() {}
    
    void incRefCount() { mCount ++; }
    int decRefCount() { return --mCount; }
    int getRefCount() { return mCount;}
private:
    int mCount;
};


#endif /* smartpointer_h */
