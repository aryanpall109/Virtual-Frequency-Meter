#define F_CPU 8000000UL

#include<avr/io.h>
 
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#define display PORTD 

 
void command()
{
    
    
	PORTC=PORTC & ~ (1<<0);
	PORTC=PORTC & ~ (1<<1) ;
	PORTC=PORTC  | (1<<2);
	PORTC=PORTC & ~(1<<2);
	_delay_ms(10);

}

void lcd_init()
{
	display = 0x38;
	command();

	display = 0x01;
	command();
    
	display = 0x0C;
	command();

	display = 0x06; 
	command();

	display = 0x80; 
	command();
}

void Display()
{
	

	PORTC=PORTC | (1<<0);
	PORTC=PORTC & ~ (1<<1);
	PORTC=PORTC  | (1<<2);
	PORTC=PORTC & ~(1<<2);
	_delay_ms(10);
}


 
 

int main(void)
{
	double Time=0;
	float value=0;
	float frequency=0;
	int F;
	char i[15];
	char z[15] = "Frequency =";
	DDRD = DDRC = 0xFF;
	DDRB = 0x00;
	 
	 
	lcd_init();  
	
	for (int k=0;k<13;k++)
	{
		display = z[k];
		Display();
	}
	
	while(1)
	{
		  
		TCCR1B=0x01;//Internal Timer On 
		
		
		// NEW CHANGE
		
		while ((PINB&0x01)==0x01); // Read on  Wave T0 . Waiting For HIGH
		while ((PINB&0x01)==0x00); // Read on Wave T0  . Waiting For LOW
		
		TCNT1 = 0x00;
		
	     TCCR0 = 0x06;  // TIMER 0. DEFINE ON FALLING EDGE
		 TCNT0 = 0x00; 
		
	    while ((PINB&0x01)==0x01); // Read on Wave T0  . Waiting For HIGH
		while ((PINB&0x01)==0x00); // Read on Wave T0  . Waiting For LOW
		 
		value = TCNT1;
				  
	   Time = value*0.000000125; // divided by 8Mhz. (Time = value* 1/8000000)
		 
		frequency = 1/Time;  
	    F = frequency;
		  
		sprintf(i, "%d", F);
		
		display = 0x8C;
		command();
			 
		for (int k=0;k<strlen(i)+1; k++)
		{
		  display = i[k];
		  Display();
		}
			
		_delay_ms(200);
		TCCR1B = 0x00;
	}
}  