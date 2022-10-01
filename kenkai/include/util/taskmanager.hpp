#pragma once

#include <stdint.h>
#include <functional>
#include <vector>
#include <SFML/System.hpp>

class Object;

// allows us to queue tasks to happen after a certain amount of time
class TaskManager
{
public:
    using Callback = std::function<void()>;

    void update(sf::Time elapsed);
    void addTask(Object* subject, uint32_t time, Callback callback);
private:
    struct Task
    {
        Object* subject;
        sf::Time end;
        Callback callback;
    };

    std::vector<Task> m_tasks;
    sf::Time m_elapsed;
};