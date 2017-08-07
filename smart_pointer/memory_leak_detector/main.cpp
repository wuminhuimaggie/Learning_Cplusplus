//
//  main.cpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/4.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#include <iostream>

// 在这里实现内存泄露检查
#include "MemoryLeakDetector.hpp"

// 测试异常分支泄露
class Err {
public:
    Err(int n) {
        if(n == 0) throw 1000;
        data = new int[n];
    }
    ~Err() {
        delete[] data;
    }
private:
    int *data;
};

int main() {
    
    // 忘记释放指针 b 申请的内存，从而导致内存泄露
    int *a = new int;
    int *b = new int;
    delete a;
    
    // 0 作为参数传递给构造函数将发生异常，从而导致异常分支的内存泄露
    try {
        Err* e = new Err(0);
        delete e;
    } catch (int &ex) {
        std::cout << "Exception catch: " << ex << std::endl;
    };
    return 0;
    
}
