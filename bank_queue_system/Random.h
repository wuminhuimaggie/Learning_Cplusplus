//
//  Random.h
//  smart_pointer
//
//  Created by wuminhui on 2017/8/7.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef Random_h
#define Random_h

#include <cstdlib>
#include <cmath>

enum RandomType {
    UNIFORM,
    EXPONENTAIL,
    POISSON,
};

class Random {
public:
    //uniform betwween [0, max)
    static double uniform(double max = 1) {
        return ((double)std::rand() / (RAND_MAX)) * max;
    }
    
    // 服从 lambda-指数分布的随机值
    static double exponentail(double lambda) {
        return -log(1 - uniform()) / lambda;
    }
    
    // 服从 lambda-泊松分布的随机值
    static double poisson(double lambda) {
        int t = 0;
        double p = exp(-lambda);
        double f = p;
        double u = uniform();
        while (true) {
            if (f > u)
                break;
            t++;
            p = p*lambda / t;
            f += p;
        }
        return t;
    }
    
    static double getRandom(RandomType type, double parameter) {
        switch (type) {
            case UNIFORM:
                return uniform(parameter);
                break;
            case EXPONENTAIL:
                return exponentail(parameter);
            case POISSON:
                return poisson(parameter);
            default:
                return 0;
                break;
        }
    }
};


#endif /* Random_h */

