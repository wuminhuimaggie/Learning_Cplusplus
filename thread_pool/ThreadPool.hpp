//
//  ThreadPool.hpp
//  smart_pointer
//
//  Created by wuminhui on 2017/8/6.
//  Copyright © 2017年 wuminhui. All rights reserved.
//

#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <vector>               // std::vector
#include <queue>                // std::queue
#include <memory>               // std::make_shared
#include <stdexcept>            // std::runtime_error
#include <thread>               // std::thread
#include <mutex>                // std::mutex,        std::unique_lock
#include <condition_variable>   // std::condition_variable
#include <future>               // std::future,       std::packaged_task
#include <functional>           // std::function,     std::bind
#include <utility>              // std::move,         std::forward

//线程池
class ThreadPool {
public:
    //构造函数
    inline ThreadPool(size_t threads) : stop(false) {
        //生成指定数量的工作线程
        for(size_t i = 0;i<threads;++i)
            //采用匿名函数来生成每个工作线程需要的运行函数
            workers.emplace_back([this] {
                //不断循环
                for(;;)
                {
                    std::function<void()> task; // 保存需要运行的任务
                    {
                        //需要用互斥锁来保证从任务列表中取出的任务只被一个工作线程操作
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                                             [this]{ return this->stop || !this->tasks.empty(); });
                        //如果需要停止 并且 任务列表为空 返回
                        if(this->stop && this->tasks.empty())
                            return;
                        //从任务列表取出一个任务，因为task一旦取出就没用了，可以使用std::move来避免拷贝
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    // 运行任务函数
                    task();
                }
            });
    }
    
    //加入任务函数到任务列表 返回函数运行完成后的返回值
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        //
        auto task = std::make_shared< std::packaged_task<return_type()>>(
                                                                         std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                                                                         );
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task]{ (*task)();}); //加入任务函数
        }
        condition.notify_one(); //唤醒一个工作线程
        return res;
    }
    //析构函数
    inline ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            //设置stop
            stop = true;
        }
        //通知所有的工作线程
        condition.notify_all();
        //等待所有的工作线程完成
        for(std::thread &worker: workers)
            worker.join();
    }
private:
    std::vector<std::thread> workers; // 工作线程
    std::queue<std::function<void()>> tasks; //采用列表来存储需要在工作线程中运行的任务函数
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop; //是否停止
};
#endif /* ThreadPool_hpp */
