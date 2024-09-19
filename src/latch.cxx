#include <Arduino.h>

#include "latch.hxx"

void Latch::set_risingedge()
{
    m_rising_edge = m_state && !m_state_old;
    m_state_old   = m_state;
}

void Latch::set_quittime()
{
    m_quit_time = m_rising_edge ? millis() + m_delay * 1e3 : 0;
}

Latch::Latch(delay_t set_delay)
    : m_delay      {set_delay} // delay in seconds
    , m_state      {false}
    , m_state_old  {false}
    , m_rising_edge{false}
    , m_quit_time  {0}
{}

void Latch::trigger(bool state)
{
    if (is_latched()) return;
    m_state = state;
    set_risingedge();
    set_quittime();
}

bool Latch::is_latched()
{
    return millis() < m_quit_time;
}