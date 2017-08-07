//
//  RTTI.hpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/5.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef RTTI_hpp
#define RTTI_hpp

#include <stdio.h>

#include <cstdint>
#include <array>

#if !defined(RTTI_CHAIN_MAX_SIZE)
#define RTTI_CHAIN_MAX_SIZE 32
#endif

class RTTI {
public:
    virtual ~RTTI() {}
    
    inline void* getPtrKindOf(std::intptr_t type) {
        for(int i = 0; i <= inherChainCounter; ++i) {
            if(inherChainID[i] == type)
                return inherChainPtr[i];
        }
        return nullptr;
    }
    inline bool isKindOf(std::intptr_t type) {
        return getPtrKindOf(type) == nullptr ? false : true;
    }
protected:
    std::array<std::intptr_t, RTTI_CHAIN_MAX_SIZE> inherChainID;
    std::array<void*, RTTI_CHAIN_MAX_SIZE> inherChainPtr;
    
    int inherChainCounter;
    
    RTTI() : inherChainCounter(-1) {
        for(auto &id : inherChainID) id = -1;
        for(auto &ptr : inherChainPtr) ptr = 0;
    }
};

template<typename T>
class RTTIPort : public virtual RTTI {
public:
    static std::intptr_t type();
    
protected:
    RTTIPort() {
        inherChainCounter ++;
        inherChainID[inherChainCounter] = type();
        inherChainPtr[inherChainCounter] = static_cast<T*>(this);
    }
    virtual ~RTTIPort() {}
private:
    static std::intptr_t id;
};

template<typename T>
std::intptr_t RTTIPort<T>::id(0);

template<typename T>
std::intptr_t RTTIPort<T>::type() {
    return reinterpret_cast<std::intptr_t>(&id);
}

template<typename T>
static bool is(RTTI* obj) {
    if(obj == nullptr) return false;
    return obj->getPtrKindOf(RTTIPort<T>::type()) != nullptr;
}


template<typename T>
static T* cast(RTTI* to) {
    if(to == nullptr)  return nullptr;
    return static_cast<T*>(to->getPtrKindOf(RTTIPort<T>::type()));
}

#endif /* RTTI_hpp */
