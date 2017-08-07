//
//  stackAlloc.cpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/5.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#include <stdio.h>


#include <iostream>
#include <cassert>
#include <ctime>
#include <vector>

#include "MemoryPool.hpp"
#include "StackAlloc.h"

// 根据电脑性能调整这些值
// 插入元素个数
#define ELEMS 2500
// 重复次数
#define REPS 50

int main()
{
    clock_t start;
    
    /* Use the default allocator */
    StackAlloc<int, std::allocator<int> > stackDefault;
    start = clock();
    for (int j = 0; j < REPS; j++)
    {
        assert(stackDefault.empty());
        for (int i = 0; i < ELEMS / 4; i++) {
            // Unroll to time the actual code and not the loop
            stackDefault.push(i);
            stackDefault.push(i);
            stackDefault.push(i);
            stackDefault.push(i);
        }
        for (int i = 0; i < ELEMS / 4; i++) {
            // Unroll to time the actual code and not the loop
            stackDefault.pop();
            stackDefault.pop();
            stackDefault.pop();
            stackDefault.pop();
        }
    }
    std::cout << "Default Allocator Time: ";
    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";
    
    /* Use MemoryPool */
    StackAlloc<int, MemoryPool<int> > stackPool;
    start = clock();
    for (int j = 0; j < REPS; j++)
    {
        assert(stackPool.empty());
        for (int i = 0; i < ELEMS / 4; i++) {
            // Unroll to time the actual code and not the loop
            stackPool.push(i);
            stackPool.push(i);
            stackPool.push(i);
            stackPool.push(i);
        }
        for (int i = 0; i < ELEMS / 4; i++) {
            // Unroll to time the actual code and not the loop
            stackPool.pop();
            stackPool.pop();
            stackPool.pop();
            stackPool.pop();
        }
    }
    std::cout << "MemoryPool Allocator Time: ";
    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";
    
    
    std::cout << "Here is a secret: the best way of implementing a stack"
    " is a dynamic array.\n";
    
    /* Compare MemoryPool to std::vector */
    std::vector<int> stackVector;
    start = clock();
    for (int j = 0; j < REPS; j++)
    {
        assert(stackVector.empty());
        for (int i = 0; i < ELEMS / 4; i++) {
            // Unroll to time the actual code and not the loop
            stackVector.push_back(i);
            stackVector.push_back(i);
            stackVector.push_back(i);
            stackVector.push_back(i);
        }
        for (int i = 0; i < ELEMS / 4; i++) {
            // Unroll to time the actual code and not the loop
            stackVector.pop_back();
            stackVector.pop_back();
            stackVector.pop_back();
            stackVector.pop_back();
        }
    }
    std::cout << "Vector Time: ";
    std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n\n";
    
    std::cout << "The vector implementation will probably be faster.\n\n";
    std::cout << "MemoryPool still has a lot of uses though. Any type of tree"
    " and when you have multiple linked lists are some examples (they"
    " can all share the same memory pool).\n";
    
    return 0;
}
