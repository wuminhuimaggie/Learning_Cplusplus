//
//  MemoryLeakDetector.cpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/4.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#include <iostream>
#include <cstring>

#define __NEW_OVERLOAD_IMPLEMENTATION__
#include "MemoryLeakDetector.hpp"

typedef struct _MemoryList {
    struct _MemoryList* next, *prev;
    size_t size; // memory size
    bool isArray;
    char* file;
    unsigned int line;
}MemoryList;

static unsigned long _memory_allocated = 0;
static MemoryList _root = {
    &_root, &_root, 0, false, nullptr, 0
};

unsigned int LeakDetector::callCount = 0;


void* AllocateMemory(size_t _size, bool _array, char* _file, unsigned int _line) {
    size_t newSize = sizeof(MemoryList) + _size;
    
    MemoryList* newElem = (MemoryList*)malloc(newSize);
    newElem->next = _root.next;
    newElem->prev = &_root;
    newElem->size = _size;
    newElem->isArray = _array;
    newElem->file = nullptr;
    
    if(_file) {
        newElem->file = (char*)malloc(strlen(_file) + 1);
        strcpy(newElem->file, _file);
    }
    newElem->line = _line;
    
    //update
    _root.next->prev = newElem;
    _root.next = newElem;
    
    _memory_allocated += _size;
    
    return (char*)newElem + sizeof(MemoryList);
}

void DeleteMemory(void* _ptr, bool _array) {
    MemoryList* currentElem = (MemoryList*)((char*)_ptr - sizeof(MemoryList));
    if(currentElem->isArray != _array) return;
    
    //update
    currentElem->prev->next = currentElem->next;
    currentElem->next->prev = currentElem->prev;
    
    _memory_allocated -= currentElem->size;
    
    //release
    if(currentElem->file) free(currentElem->file);
    free(currentElem);
}

//override new
void* operator new(size_t _size) {
    return AllocateMemory(_size, false, nullptr, 0);
}
void* operator new[](size_t _size) {
    return AllocateMemory(_size, true, nullptr, 0);
}
void* operator new(size_t _size, char* _file, unsigned int _line) {
    return AllocateMemory(_size, false, _file, _line);
}
void* operator new[](size_t _size, char* _file, unsigned int _line) {
    return AllocateMemory(_size, true, _file, _line);
}

//override delete
void operator delete(void* _ptr) noexcept {
    DeleteMemory(_ptr, false);
}
void operator delete[](void* _ptr) noexcept {
    DeleteMemory(_ptr, true);
}

unsigned int LeakDetector::_leak_detect() noexcept {
    unsigned int count = 0;
    MemoryList* ptr = _root.next;
    while(ptr && ptr != & _root) {
        if(ptr->isArray) {
            std::cout << "leak [] ";
        } else {
            std::cout << "leak ";
        }
        std::cout << ptr << " size " << ptr->size;
        if(ptr->file) {
            std::cout<< " (locate " << ptr->file << " line " << ptr->line << " )" ;
        } else {
            std::cout << "(no file info)";
        }
        std::cout << std::endl;
        ++count;
        
        ptr = ptr->next;
    }
    if (count)
        std::cout << "Total : " << count << "leaks, including "<< _memory_allocated << " byte." << std::endl;
    
    return count;
}






        
