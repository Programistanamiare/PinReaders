#pragma once

#include <Arduino.h>

class AnalogReader
{
public:
  /**
   * Typ wskaźnikowy przyjmujący funkcję, która przyjmuje jeden argument typu "int" oraz zwraca typ "uint32_t".
  */
  typedef uint32_t (*TransitionFunctionPtr)(int);
  /**
   * Konstruktor klasy AnalogReader. Klasa służy do odczytu wartości z podanego wejścia analogowego.
   * Poprzez wbudowaną funkcję read() w zależności od podanych argumentów można tę wartość mapować liniowo 
   * bądź poprzez własną funkcję przejścia.
   * @param analog_pin pin analogowy, z którego będą odczytywane wartości.
  */
  AnalogReader(const uint8_t& analog_pin = A0);

  /**
   * Funkcja składowa odczytująca bezpośrednią wartość z wejścia analogowego i zapisująca pomiar do wew. zmiennej
   * w celu późniejszego jej odczytu.
   * @return odczytaną wartość z wejścia analogowego.
  */
  const int32_t& read();

  /**
   * Funkcja składowa odczytująca wartość z wejścia analogowego, mapująca ją przez podany zakres i zapisująca wynik do 
   * wew. zmiennej w celu późniejszego jej odczytu.
   * @param from dolna granica mapowania.
   * @param to górna granica mapowania.
   * @return wynik mapowania odczytanej wartości.
  */
  const int32_t& read(const int32_t& from, const int32_t& to);

  /**
   * Funkcja składowa odczytująca wartość z wejścia analogowego, przepuszczająca wynik pomiaru przez podaną jako argument
   * funkcję i zapisująca wynik podanej funkcji do wew. zmiennej w celu późniejszego jej odczytu.
   * @param function wskaźnik do funkcji przejścia, która pobiera typ "int" i zwraca typ "uint32_t".
   * @return wynik podanej funkcji.
  */
  const int32_t& read(TransitionFunctionPtr function);

  /**
   * Funkcja składowa umożliwiająca pobranie ostatniego odczytu wejścia analogowego po ewentualnych modyfikacjach.
   * @return wartość ostatnio wywołanej funkcji składowej read.
  */
  const int32_t& getValue() const;

  
private:
  void initVars();
  uint8_t pin;
  int32_t value;
};