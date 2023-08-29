#pragma once

#include "Arduino.h"


template<class T = uint16_t>
class AnalogReader
{
public:

  typedef T (*TransitionFunctionPtr)(int);

  AnalogReader(const uint8_t& analog_pin = A0) 
  : pin{analog_pin}, value{0}, converted_value{0}, prev_value{0} {}

  const T& read();

  const T& read(const T& from, const T& to);

  const T& read(TransitionFunctionPtr function);

  const T& getConvertedValue() const 
  { 
    return this->converted_value; 
  }

  const int& getOriginalValue() const 
  { 
    return this->value; 
  }

  int valueIsChange(const T& buffor = 0);
  int valueIsChange(const T& buffor, const T& compare_against);

private:
  uint8_t pin;
  int value;
  T converted_value;
  T prev_value;
  void simpleRead();
  T temp_map(const T& out_min, const T& out_max);
};

template<class T>
void AnalogReader<T>::simpleRead()
{
  this->prev_value = this->converted_value;
  this->value = analogRead(this->pin);
}

template<class T>
T AnalogReader<T>::temp_map(const T& out_min, const T& out_max)
{
  return this->value * (out_max - out_min) / 1023 + out_min;
}

template<class T>
const T& AnalogReader<T>::read()
{
  this->simpleRead();
  return this->converted_value = this->value;
}

template<class T>
const T& AnalogReader<T>::read(const T& from, const T& to)
{
  this->simpleRead();
  return this->converted_value = this->temp_map(from, to);
}

template<class T>
const T& AnalogReader<T>::read(TransitionFunctionPtr function)
{
  this->simpleRead();
  return this->converted_value = function(this->value);
}

template<class T>
int AnalogReader<T>::valueIsChange(const T& buffor)
{
  return this->valueIsChange(buffor, this->prev_value);
}

template<class T>
int AnalogReader<T>::valueIsChange(const T& buffor, const T& compare_against)
{
  if (this->converted_value > compare_against && this->converted_value - compare_against > buffor) return 1;
  if (compare_against > this->converted_value && compare_against - this->converted_value > buffor) return -1;
  return 0;
}