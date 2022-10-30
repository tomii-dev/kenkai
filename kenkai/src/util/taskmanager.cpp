#include "util/taskmanager.hpp"

void TaskManager::update(sf::Time elapsed)
{
    for(auto it = m_tasks.begin(); it != m_tasks.end();)
    {
        if(elapsed >= it->end)
        {
            it->callback();
            it = m_tasks.erase(it);
        }
        else it++;
    }

    m_elapsed = elapsed;
}

void TaskManager::addTask(Object* subject, uint32_t time, Callback callback)
{
    const sf::Time endTime = m_elapsed + sf::milliseconds(time);
    Task task{ subject, endTime, callback };

    m_tasks.push_back(task);
}
