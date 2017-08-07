//
//  main.cpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/7.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#include <stdio.h>

#include "QueueSystem.hpp"

#include <iostream>
#include <cstdlib>

int main() {
    
    std::srand((unsigned)std::time(0)); // 使用当前时间作为随机数种子
    
    int total_service_time = 240;       // 按分钟计算
    int window_num         = 4;
    int simulate_num       = 1;    // 模拟次数
    
    QueueSystem system(total_service_time, window_num);
    system.simulate(simulate_num);
    
    std::cout << "The average time of customer stay in bank: "
    << system.getAvgStayTime() << std::endl;
    std::cout << "The number of customer arrive bank per minute: "
    << system.getAvgCustomers() << std::endl;
    
    return 0;
}
