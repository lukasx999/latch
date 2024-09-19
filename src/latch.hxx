#pragma once

typedef unsigned long delay_t;

class Latch {
  private:
    bool m_state, m_state_old, m_rising_edge;
    delay_t m_quit_time;
    const delay_t m_delay;
    void set_risingedge(), set_quittime();

  public:
    Latch(delay_t set_delay); // delay in seconds
    void trigger(bool state);
    bool is_latched();
};