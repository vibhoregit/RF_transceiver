#define cpu_clk 8000000L
uint8_t data[3] = {0};
void init_timer1()
{
  TCCR1A = 1<<WGM11;
  TCCR1B = 1<<WGM13|1<<WGM12|1<<CS11|1<<CS10;
  ICR1 = 0x0100;
  TIMSK1 = 0;
}

void init_adc()
{
  ADMUX = 1<<REFS0|1<<ADLAR;
  ADCSRA = 1<<ADEN|1<<ADPS2|1<<ADPS1|1<<ADPS0;
}

void init_gpio()
{
  DDRB |= 1<<PB1;
  DDRD  = 0;
  PORTD = 1<<PB2|1<<PB3|1<<PB4;  
}

void rf_transmit(uint8_t *ptr,uint8_t len)
{
  while();
}

uint8_t adc_getval(uint8_t channel)
{
  uint8_t val = 0;
  ADMUX &= ~(0x0F);
  ADMUX |= (0x07&channel);
  ADCSRA|= 1<<ADSC;
  while(ADCSRA &(1<<ADIF) == 0);
  ADCSRA|= 1<<ADIF;
  val = ADCH;
  return ADCH;  
}
int main()
{
  cli();
  init_timer1();
  init_gpio();
  init_adc();
  while(1)
  {
    data[0] = adc_getval(0);
    data[1] = adc_getval(1);
    data[2] = (PIND&0b00011100)<<3 + 8;
    rf_transmit(data,len);
  }
 }

