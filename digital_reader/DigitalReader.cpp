#include "DigitalReader.hpp"


void DigitalReader::init(const uint8_t& mode)
{
  this->mode = mode;
  pinMode(this->pin, mode);
}

const bool& DigitalReader::read()
{
  this->prev_state = this->current_state;
  this->current_state = this->mode ? !digitalRead(this->pin) : digitalRead(this->pin);
  return this->current_state;
}

const bool& DigitalReader::getValue() const
{
  return this->current_state;
}

bool DigitalReader::onActivate(bool incrase_counter)
{
  if (this->current_state && !this->prev_state) {
    this->counter += incrase_counter;
    return true;
  }
  return false;
}

bool DigitalReader::onDeactivate(bool incrase_counter)
{
  if (!this->current_state && this->prev_state) {
    this->counter += incrase_counter;
    return true;
  }
  return false;
}

bool DigitalReader::onToggle(bool incrase_counter)
{
  return this->onActivate(incrase_counter) || this->onDeactivate(incrase_counter);
}

const uint32_t& DigitalReader::getCounter() const
{
  return this->counter;
}

void DigitalReader::resetCounter(const uint32_t& new_count)
{
  this->counter = new_count;
}