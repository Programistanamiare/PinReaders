#pragma once

#include <Arduino.h>

class DigitalReader
{

public:
  /**
   * Konstruktor klasy DigitalReader. Klasa umożliwia odczyt wartości z wejścia cyfrowego,
   * reagowanie na zmiany stanu oraz zliczanie zmian stanów na wejściu cyfrowym.
   * @param pin numer pinu, do którego podłączony jest sygnał z detektora.
  */
  DigitalReader(const uint8_t& pin);

  /**
   * Funkcja składowa inicjalizująca działanie detektora. Obiekt wymaga użycie jej w funkcji setup(), 
   * do poprawnego działania obiektu.
   * 
   * @param mode tryb pracy do wyboru pomiędzy INPUT (0) lub INPUT_PULLUP (2)
  */
  void init(const uint8_t& mode = INPUT_PULLUP);

  /**
   * Funkcja składowa odczytująca wartość z detektora.
   * @return odczytana wartość.
  */
  const bool& read();

  /**
   * Funkcja składowa zwracająca ostastnią odczytaną wartość z detektora.
  */
  const bool& getValue() const;

  /**
   * Funkcja składowa informująca o aktywacji detektora.
   * @param incrase_counter domyślnie false. Jeśli ustawiony na true po aktywacji czujnika zwiększa się wew. licznik.
   * @return true w przypadku zmiany stanu wejścia cyfrowego z 0 na 1.
  */
  bool onActivate(bool incrase_counter = false);

  /**
   * Funkcja składowa informująca o dezaktywacji detektora.
   * @param incrase_counter domyślnie false. Jeśli ustawiony na true po deaktywacji czujnika zwiększa się wew. licznik.
   * @return true w przypadku zmiany stanu wejścia cyfrowego z 1 na 0.
  */
  bool onDeactivate(bool incrase_counter = false);

  /**
   * Funkcja składowa zwracająca wew. licznik (patrz funkcje składowe onActivete oraz onDeactivate) od momentu ostatniego resetu.
   * @return wew. licznik.
  */
  const uint32_t& getCounter() const;

  /**
   * Funkcja składowa resetująca wartość wew. licznika.
   * 
   * @param new_count wartość, do której licznik ma zostać zresetowany (domyślnie jest to 0).
  */
  void resetCounter(const uint32_t& new_count = 0);

private:
  void initVars();
  uint8_t pin, mode;
  bool prev_state, current_state;
  uint32_t counter;
};