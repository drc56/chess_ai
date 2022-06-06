#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

namespace common{
template<typename T>
class ThreadSafeQueue{
    public:
        
        ThreadSafeQueue() {};
        // Delete copy and move constructors for now
        ThreadSafeQueue(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
        ThreadSafeQueue(ThreadSafeQueue&&) = delete;
        ThreadSafeQueue& operator=(ThreadSafeQueue&&) = delete;

        bool isempty() const
        {
            std::lock_guard<std::mutex> lk(data_m_);
            return data_.empty();
        }

        // bool full() const
        // {
        //     std::lock_guard<std::mutex> lk(data_m_);
        //     return data_.size() == size_;
        // }

        void push(T val)
        {
            std::lock_guard<std::mutex> lk (data_m_);
            data_.push(val);
            empty_con_v_.notify_all();
        }

        T pop()
        {
            std::unique_lock<std::mutex> lk (data_m_);
            while(data_.empty()){
                empty_con_v_.wait(lk, [this]{return data_.empty() != true;});
            }
            T res = data_.front();
            data_.pop();
            full_con_v_.notify_all();
            lk.unlock();
            return res;
        }
        
    private:
        std::queue<T> data_;
        mutable std::mutex data_m_;
        std::condition_variable empty_con_v_;
        std::condition_variable full_con_v_;
};
} //namespace common
#endif