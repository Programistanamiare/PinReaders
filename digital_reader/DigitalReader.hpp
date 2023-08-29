#pragma once

#include <Arduino.h>

class DigitalReader
{

public:

  DigitalReader(const uint8_t& pin)
  : pin{pin}, mode{0}, prev_state{false}, current_state{false} {}

  void init(const uint8_t& mode = INPUT_PULLUP);

  const bool& read();

  const bool& getValue() const;

  bool onActivate(bool incrase_counter = false);

  bool onDeactivate(bool incrase_counter = false);

  bool onToggle(bool incrase_counter = false);

  const uint32_t& getCounter() const;

  void resetCounter(const uint32_t& new_count = 0);

private:
  uint8_t pin, mode;
  bool prev_state, current_state;
  uint32_t counter;
};