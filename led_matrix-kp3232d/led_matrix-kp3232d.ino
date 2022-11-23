#define MATRIX_ROW (16)
#define MATRIX_COL (32)

static inline void ctrl_show(uint8_t line)
{
  // Set output enable to high.
  PORTD |= (B10000000);
  // Set line select.
  PORTB  = (PORTB & ~(B00001111)) | (line & (B00001111));
  // Set latch to high.
  PORTD |= (B01000000);
  // Set output enable and latch to low.
  PORTD &= ~(B11000000);
}

static inline void ctrl_push(uint8_t rgb1, uint8_t rgb2)
{
  // Set color1, color2.
  PORTC  = (PORTC & ~(B00111111)) | ((((rgb1 & (B00000111)) << 3) | (rgb2 & (B00000111))));
  // Set clock to high.
  PORTD |= (B00100000);
  // Set clock to low.
  PORTD &= ~(B00100000);
}

ISR (TIMER1_COMPA_vect)
{
  for (uint8_t i = 0; MATRIX_ROW > i; i++)
  {
    for (uint8_t j = 0; MATRIX_COL > j; j++)
    {
      ctrl_push(i, j);
    }

    ctrl_show(i);
  }
}

void setup()
{
  // Set output mode.
  // D#08: A, D#09: B, D#10: C, D#11: D
  DDRB |= (B00001111);
  // A#00: R2, A#01: G2, A#02: B2, A#03: R1, A#04: G1, A#05: B1
  DDRC |= (B00111111);
  // D#05: CLK, D#06: STB, D#07: OE
  DDRD |= (B11100000);

  // Set initial output.
  // All low.
  PORTB &= ~(B00001111);
  // All low.
  PORTC &= ~(B00111111);
  // OE is high, others is low.
  PORTD = (PORTD & ~(B01100000)) | (B10000000);

  // Initialize serial.
  Serial.begin(9600);

  // Initialize timer.
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCCR1A |= 0;              // CTC mode
  TCCR1B |= (B00001010);    // Dividend ratio to 1/8.
  OCR1A   = 8333;           // 240Hz
  TIMSK1 |= (1 << OCIE1A);
}

void loop()
{

}
