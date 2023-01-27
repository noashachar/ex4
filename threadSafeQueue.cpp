//
// Created by noash on 27/01/2023.
//

#ifndef EX4_THREADSAFEQUEUE_CPP
#define EX4_THREADSAFEQUEUE_CPP

#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
private:
    std::deque<T> q;
    std::mutex m;
    std::condition_variable cv;

public:
    void push(T item)
    {
        std::unique_lock<std::mutex> lock(m);
        q.push_back(item);
        lock.unlock();
        cv.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [this]()
        { return !q.empty(); });
        T item = q.front();
        q.pop_front();
        return item;
    }
};

#endif //EX4_THREADSAFEQUEUE_CPP
