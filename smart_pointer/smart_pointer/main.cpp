//
//  main.cpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/4.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#include <iostream>
#include "smartpointer.h"

class SomeClass : public RefBase {
public:
    SomeClass() {
        std::cout << "SomeClass default constructor!" << std::endl;
    }
    ~SomeClass(){
        std::cout << "SomeClass deconstructor !" << std::endl;
    }
    void func() {
        std::cout << "SomeClass func()" << std::endl;
    }
};

class OtherClass : public RefBase {
public:
    OtherClass() {
        std::cout << "OtherClass default constructor!" << std::endl;
    }
    ~OtherClass(){
        std::cout << "OtherClass deconstructor !" << std::endl;
    }
    void foo() {
        std::cout << "SomeClass foo()" << std::endl;
    }
};

void test1() {
    //SmartPointer<char> spunknown;
    //SmartPointer<char> spnull = nullptr;
    SmartPointer<SomeClass> spclass = new SomeClass;
    //SmartPointer<const char> spstr = "hell world";
}

void test2() {
    SmartPointer<SomeClass> spclass = new SomeClass;
    std::cout << std::endl;
    
    spclass = spclass;
    std::cout << std::endl;
    
    SmartPointer<SomeClass> spclassother = spclass;
    std::cout << std::endl;
    
    SmartPointer<SomeClass> spclass2 = new SomeClass;
    std::cout << std::endl;
    
    spclass2 = spclass;
    std::cout << std::endl;
}

void test3() {
    SomeClass *pSomeClass = new SomeClass;
    SmartPointer<SomeClass> spOuter = pSomeClass;
    std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") outer 1."<< std::endl;
    
    {
        SmartPointer<SomeClass> spInner = spOuter;
        std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") inner."<< std::endl;
    }
    std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") outer 2."<< std::endl;
    
    std::cout << "new another SomeClass class for spOuter."<< std::endl;
    
    SmartPointer<SomeClass> spOuter2 = new SomeClass;
    spOuter = spOuter2;
}

void test4_1() {
    std::cout << "=======testcase4_1=========" <<std::endl;
    
    SmartPointer<SomeClass> spsomeclass = new SomeClass();
    (*spsomeclass).func();
    spsomeclass->func();
    
    std::cout << "==========================\n" <<std::endl;
}

void test4_2() {
    std::cout << "=======testcase4_2=========" <<std::endl;
    
    SomeClass *psomeclass = new SomeClass();
    SmartPointer<SomeClass> spsomeclass = psomeclass;
    
    SmartPointer<OtherClass> spotherclass = new OtherClass();
    SmartPointer<OtherClass> spotherclass2 = spotherclass;
    
    if (spsomeclass == NULL) std::cout<< "spsomeclass is NULL pointer" << std::endl;
    if (spotherclass != NULL) std::cout<< "spotherclass is not NULL pointer" << std::endl;
    if (spsomeclass == psomeclass)
        std::cout<< "spsomeclass and psomeclass are same pointer" << std::endl;
    if (spsomeclass != psomeclass)
        std::cout<< "spsomeclass and psomeclass are not same pointer" << std::endl;
    //     if (spsomeclass != spotherclass) // ERROR !
    //        std::cout<< "spsomeclass and spotherclass are not same pointer" << std::endl;
    //     if (spsomeclass == spotherclass) // ERROR !
    //        std::cout<< "spsomeclass and spotherclass are same pointer" << std::endl;
    if (spotherclass == spotherclass2)
        std::cout<< "spotherclass and spotherclass2 are same pointer" << std::endl;
    if (spotherclass != spotherclass2)
        std::cout<< "spotherclass and spotherclass2 are not same pointer" << std::endl;
    std::cout << "==========================" <<std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    test4_1();
    test4_2();
    return 0;
}
