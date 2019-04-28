#define cpu_clk 8000000L
#define packet_len 4
uint8_t data[packet_len] = {0};
void init_timer1()
{
  TCCR1A = 1<<WGM11;
  TCCR1B = 1<<WGM13|1<<WGM12|1<<CS11|1<<CS10;
  ICR1 = 0x010F;
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
  uint8_t i = 0;
  for(i = 0; i < len; i++)
  {
    while(TCNT1 < 0x0100);
    OCR1A = data[i];
  }
  
}


int main()
{
  cli();
  init_timer1();
  init_gpio();
  init_adc();
  data[packet_len-1] = 150;
  Serial.begin(9600);
  /*while(1)
  {
    data[0] = adc_getval(0);
    data[1] = adc_getval(1);
    data[2] = (PIND&0b00011100)<<3 + 8;
    rf_transmit(data,len);
  }*/
  while(1)
  {
    data[0] = map(constrain(analogRead(A0)>>2,120,190),120,190,100,0);
    data[1] = map(constrain(analogRead(A1)>>2,25,155),25,155,0,100);
    Serial.println(data[0]);
    Serial.println(data[1]);
    Serial.println(PIND&0b00011100|0x80,BIN);
    Serial.println("*********");
    rf_transmit(data,packet_len);
    _delay_ms(5);
  }
  
 }

