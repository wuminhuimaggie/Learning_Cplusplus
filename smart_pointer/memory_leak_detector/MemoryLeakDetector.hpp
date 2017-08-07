//
//  MemoryLeakDetector.hpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/4.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef MemoryLeakDetector_hpp
#define MemoryLeakDetector_hpp

#include <stdio.h>

void* operator new(size_t _size, char* _file, unsigned int _line);
void* operator new[](size_t _size, char* file, unsigned int _line);

#ifndef __NEW_OVERLOAD_IMPLEMENTATION__
#define new new(__FILE__, __LINE__)
#endif

class LeakDetector {
public:
    static unsigned int callCount;
    
    LeakDetector() noexcept { ++callCount;}
    ~LeakDetector() noexcept {
        if(--callCount == 0) {
            _leak_detect();
        }
    }
private:
    static unsigned int _leak_detect() noexcept;
};

static LeakDetector _exit_counter;

#endif /* MemoryLeakDetector_hpp */

