# PinReaders for Arduino Framework v1.0.0

### The library is used for easier reading and management of measurements from analog inputs and digital microcontrollers, whose programming can be based on the Arduino framework.


## Example

```cpp

  #include <PinReaders.h>

  #define LED_PIN 2

  AnalogReader<uint8_t> light_detector(A2);
  DigitalReader ir_detector(3);


  void setup()
  {
    ir_detector.init(); // INPUT_PULLUP default
    pinMode(LED_PIN, OUTPUT); // simple LED.
  }

  void loop()
  {
    ir_detector.read();
    light_detector.read(255, 0); // map 0, 1023 to 255, 0

    if (ir_detector.onActivate()) {
      analogWrite(LED_PIN, light_detector.getConvertedValue());
    }

    if (ir_detector.onDeactivate()) {
      digitalWrite(LED_PIN, 0);
    }
    delay(1000);
  }

```

## Documentation

### Analog reader

<details>
<summary> The class reads and stores the value from the analog pin. </summary>

The class is used for more practical reading and manipulation of the value read from the analog pin.
Due to the use of the class template, you can specify any type of value to which the value read from the pin will be transformed. Numeric types seem to be the best choice, but you can also provide your own types, but they must meet several rules:

* The class must be convertible to an int type, or its constructor must assume the value 0, due to the initialization of the object parameter of the given type by calling 'parameter{0}'.
* Class must support multiplication with type int.
* Class must support division by int.
* Class must support addition with type int.
* Class must support the self-subtraction operator.
* Class must support the ">" and "<" operators on itself.

```cpp
  template<class T = uint16_t>
  class AnalogReader
  {
    ...
  };
```
---

The class constructor accepts as a template argument the type of value to which the reading from the analog pin will be converted.<br>
@param **T** value type (uint16_t by default),<br>
@param **analog_pin** number of analog pin (A1 by default).

```cpp
  AnalogReader<T>::AnalogReader(uint8_t analog_pin = A1);
```
---
<br>

A member function that reads a value from an analog pin and returns the result of converting the reading of this value (int) to the specified template type.<br>

```cpp
  const T& AnalogReader<T>::read();
```
---
<br>

A member function that reads a value from an analog pin and returns the result of mapping the read value to the range given as arguments to the call.<br>
@param **from** lower mapping range,<br>
@param **to** higher mapping range.<br>
@return mapped value.

```cpp
  const T& AnalogReader<T>::read(const T& from, const T& to);
```
---
<br>

A member function that reads the value from the analog pin and returns the result of the function given as the argument of the call.<br>
@param **function** pointer to function, that return the type provided in the template and take one integer argument.<br>
@return converted value.

```cpp
  const T& AnalogReader<T>::read(TransitionFunctionPtr function);
```
---
<br>

A member function that returns the value of the last conversion of the value read from the analog pin to the type given in the template.<br>
@return last conversion ot the value read.

```cpp
  const T& AnalogReader<T>::getConvertedValue() const;
```
---
<br>

A member function that return the value of the last read from the analog pin, without any conversions.<br>
@return original value of the last analog pin read. 

```cpp
  const int& AnalogReader<T>::getOriginalValue() const;
```
---
<br>

A component function that returns information on whether and how the new reading value has changed in relation to the previous reading from the analog pin. Reacting to contact vibrations can be prevented by using a buffer.<br>
@param **buffer** the amount by which the previous reading must change from the new reading for a change in value to be detected.<br>
@returns: <br>
* **1** if value incrased,<br>
* **-1** if value decrased,<br>
* **0** if value is not change.

```cpp
  int AnalogReader<T>::valueIsChange(const T& buffer = 0);
```
---
<br>

Overloading a member function by adding a value parameter against which to compare the new value. This solution will prevent the lack of reaction to slow changes of values falling within the buffer range.<br>
@param **buffer** the amount by which the previous reading must change from the new reading for a change in value to be detected.<br>
@param **compare_against** your own value to compare against current converted read value.
@returns: <br>
* **1** if value incrased,<br>
* **-1** if value decrased,<br>
* **0** if value is not change.

```cpp
  int AnalogReader<T>::valueIsChange(const T& buffor = 0, const T& compare_against);
```

</details>


### DigitalReader

<details>
<summary> A class used to read values from a digital pin and react to changes in its state. </summary>

Constructor.<br>
@param **pin** digital pin number (2 by default).

```cpp
  DigitalReader::DigitalReader(const uint8_t pin = 2);
```
---
<br>

A member function that set new digital pin.<br>
@param **pin** digital pin number.<br.
@attention **This member function must be used before calling DigitalReader::init(const uint8_t&), due to the need to correctly initialize the pin as input.**

```cpp
  void DigitalReader::setPin(const uint8_t pin);
```
---
<br>

A member function that initializes the digital pin as input, according to the given mode.<br>
@param **mode** INPUT or INPUT_PULLUP according to prefference (INPUT_PULLUP by default).<br>
@attention **if the mode is set to INPUT_PULLUP, the object will always negate the read input signal. In the case of INPUT mode, the signal will be read unchanged.**

```cpp
  void DigitalReader::init(const uint8_t mode = INPUT_PULLUP);
```
---
<br>

A member function that set preview read value, and read new value from digital pin.<br>
@return current read value.<br>
@attention **if the mode is set to INPUT_PULLUP, the object will always negate the read input signal. In the case of INPUT mode, the signal will be read unchanged.**

```cpp
  const bool& DigitalReader::read();
```
---
<br>

A member function that return latest read value.<br>
@return latest read value.<br>
@attenttion **if the mode is set to INPUT_PULLUP, the object will always negate the read input signal. In the case of INPUT mode, the signal will be read unchanged.**

```cpp
  const bool& DigitalRead::getValue() const;
```
---
<br>

A member function that returns true when the previous pin state reading was LOW and the current one is HIGH.<br>
@param **incrase_counter** setting it to 'true' will increment the internal counter if function return 'true' ('false' by default).<br>
@attention **if the mode is set to INPUT_PULLUP, the object will always negate the read input signal. In the case of the INPUT mode, the signal will be read in an unchanged form, so if the INPUT_PULLUP mode, this function will return 'true' if the previous state was HIGH and the current one is LOW, and vice versa in the case of INPUT.**

```cpp
  bool DigitalRead::onActivate(bool incrase_counter = false);
```
---
<br>

A member function that returns true when the previus pin state reading was HIGH and the current one is LOW.<br>
@param **incrase_counter** setting it to 'true' will increment the internal counter if function return 'true' ('false' by default).<br>
@attention **if the mode is set to INPUT_PULLUP, the object will always negate the read input signal. In the case of the INPUT mode, the signal will be read in an unchanged form, so if the INPUT_PULLUP mode, this function will return 'true' if the previous state was LOW and the current one is HIGH, and vice versa in the case of INPUT.**

```cpp
  bool DigitalReader::onDeactivate(bool incrase_counter = false);
```
---
<br>

A member function that return 'true' when the previous and current state reading are different.<br>
@param **incrase_counter** setting it to 'true' will increment the internal counter if function return 'true' ('false' by default).<br>

```cpp
  bool DigitalReader::onToggle(bool incrase_counter = false);
```
---
<br>

A member function that return internal counter value.<br>
@return internal counter value.

```cpp
  const uint32_t DigitalReader::getCounter() const;
```
---
<br>

A member function that reset internal counter value.<br>
@param **new_count** new value of internal counter (0 by default).

```cpp
  void DigitalReader::resetCounter(const uint32_t& new_count = 0);
```
---
<br>

</details>