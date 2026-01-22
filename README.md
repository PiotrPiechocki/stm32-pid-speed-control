# STM32 PID Speed Control

Projekt przedstawia implementację dyskretnego regulatora PID do regulacji prędkości silnika prądu stałego
z wykorzystaniem mikrokontrolera STM32.

## Funkcjonalności
- Regulacja prędkości silnika DC za pomocą regulatora PID
- Sprzężenie zwrotne z enkodera
- Sterowanie PWM
- Wizualizacja parametrów na wyświetlaczu OLED
- Monitorowanie sygnałów w SWV Line Graph
- Zmiana wartości zadanej w czasie rzeczywistym (Live Expressions)

## Struktura projektu
- `Core/` – logika aplikacji i regulator PID
- `Drivers/` – sterowniki HAL, OLED, CMSIS
- `.ioc` – konfiguracja STM32CubeMX

## Autor
Piotr Piechocki
