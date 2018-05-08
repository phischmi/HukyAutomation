/*

*/

void setup() {
  // Set 64MHz asynchronus clock mode, if bits not already set by Bootloader
  PLLCSR |= (1 << PLLE);            // PLL Enable
  while(!(PLLCSR & (1 << PLOCK)));  // PLL Lock Detector
  PLLCSR |= (1 << PCKE);            // PCK Enable
  
  // Set PWM frequency to (64MHz / 16) / (199 + 1) = 20KHz
  TCCR1 =   
            (1 << PWM1A)  |   // Pulse Width Modulator A Enable
            (1 << COM1A1) |   // Comparator A Output Mode to OC1x cleared on compare match. Set when TCNT1 = $00; Inverted Output not connected
            (1 << CS12)   |   // Set Prescaler to 0101 = 16
            (1 << CS10);      // Set Prescaler to 0101 = 16
  
  OCR1C = 199;                // Set Top-Value to 199
  OCR1A = 199;                // Set initial value
  
  pinMode(1, OUTPUT);         // Set digital pin 1 (PB1) to OUTPUT
}

void loop() {
  OCR1A = map(analogRead(A2), 0, 851, 0, 199); // 851 equals ~4.2 Volts
}
