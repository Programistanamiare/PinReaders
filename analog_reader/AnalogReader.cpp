#include "AnalogReader.hpp"

AnalogReader::AnalogReader(const uint8_t& analog_pin)
{
  this->initVars();
  this->pin = analog_pin;
}

void AnalogReader::initVars()
{
  this->value = 0;
}

const int32_t& AnalogReader::read()
{
  return this->value = analogRead(this->pin);
}

const int32_t& AnalogReader::read(const int32_t& from, const int32_t& to)
{
  return this->value = map(analogRead(this->pin), 0, 1023, from, to);
}

const int32_t& AnalogReader::getValue() const
{
  return this->value;
}

const int32_t& AnalogReader::read(TransitionFunctionPtr function)
{
  return this->value = function(analogRead(this->pin));
}