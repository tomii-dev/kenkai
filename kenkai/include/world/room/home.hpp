#pragma once

#include "room.hpp"

#include "util/event.hpp"

class Home : public Room
{
public:
    Home();

    inline Event<>* onEnterKenkai() { return m_enterKenkaiEvent.get(); }
private:
    EventPtr<> m_enterKenkaiEvent;
};