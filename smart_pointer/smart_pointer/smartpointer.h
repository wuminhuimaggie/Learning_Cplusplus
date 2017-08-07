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

//智能指针
template< typename T >
class SmartPointer {
public:
    //默认构造函数
    SmartPointer(): mPointer(nullptr) {
        std::cout << "create unknown smart pointer." << std::endl;
    }
    //T类型的指针数据初始化
    SmartPointer(T* p): mPointer(p) {
        std::cout << "create smart pointer at " << static_cast<const void*>(p) << std::endl;
        //增加引用计数
        if(mPointer) mPointer->incRefCount();
    }
    //复制构造函数
    SmartPointer(const SmartPointer& other): mPointer(other.mPointer) {
        std::cout <<"copy smart pointer at " << static_cast<const void*>(other.mPointer) << std::endl;
        //增加引用计数
        if(mPointer) mPointer->incRefCount();
    }
    //赋值操作符
    SmartPointer& operator=(const SmartPointer& other) {
        //调用指针初始化的构造函数，将other的指针赋给temp
        T* temp(other.mPointer);
        //增加temp指针的引用计数
        if(temp) temp->incRefCount();
        //因为要替换mPointer，因此mPointer以前的指针数据需要减少其引用计数
        if(mPointer && mPointer->decRefCount() == 0) delete mPointer;
        //赋值
        mPointer = temp;
        std::cout << "Assign smart pointer at " << static_cast<const void*>(other.mPointer) << std::endl;
        return *this;
    }
    //析构函数
    ~SmartPointer() {
        std::cout << "release smart pointer at " << static_cast<const void*>(mPointer) << std::endl;
        //如果指针的引用计数为0，则其可以删除
        if(mPointer && mPointer->decRefCount() == 0) delete mPointer;
    }
    
    //override * and ->
    T& operator*() const { return *mPointer; };
    T* operator->() const { return mPointer; };
    
    //重载 ==
    bool operator ==(const SmartPointer& o) const {
        return mPointer == o.mPointer;
    }
    bool operator ==(const T* o) const {
        return mPointer == o;
    }
    
    //重载 !=
    bool operator !=(const SmartPointer& o) const {
        return mPointer != o.mPointer;
    }
    bool operator !=(const T* o) const {
        return mPointer != o;
    }
    
private:
    // 指向T类型的指针
    T *mPointer;
};

//所有上面的类型T都必须继承自RefBase，因为其必须实现inc和dec函数
class RefBase {
public:
    RefBase(): mCount(0) {}
    virtual ~RefBase() {}
    
    //增加引用计数
    void incRefCount() { mCount ++; }
    //删除引用计数
    int decRefCount() { return --mCount; }
    //返回当前的引用计数
    int getRefCount() { return mCount;}
private:
    //前面的应用技术
    int mCount;
};


#endif /* smartpointer_h */
