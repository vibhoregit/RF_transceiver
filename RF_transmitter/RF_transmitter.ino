#define cpu_clk 8000000L
uint8_t data[3] = {0};
void init_timer1()
{
  
}

void init_adc()
{
  
}

void init_gpio()
{
  
}

void rf_transmit(uint8_t *ptr,uint8_t len)
{
  
}

uint8_t adc_getval(uint8_t channel)
{
  
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
