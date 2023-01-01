/*
 * Frequency Meter.cpp
 *
 * Created: 15/07/2022 3:59:25 PM
 * Author : aryan
 */ 

# define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#define LCD_data PORTB
#define ctrl PORTD
#define en PD2
#define rw PD1
#define rs PD0
void LCD_cmd(unsigned char cmd);
void init_LCD (void);
void LCD_write(unsigned char data);
void LCD_write_string();
unsigned int press;
int main (void)
{
	int value =0;
	DDRB=0XFF;
	DDRD=0X07;
	unsigned char str[15];
	str[0]='f';
	str[1]='r';
	str[2]='e';
	str[3]='q';
	str[4]='u';
	str[5]='e';
	str[6]='n';
	str[7]='c';
	str[8]='y';
	str[9]=' ';
	str[10]='=';
	str[11]=' ';
	init_LCD();
	for(int i=0;i<12;i++)
	{
		LCD_write(str[i]);
	}
	LCD_cmd(0xc0);
	while(1)
	{
		int count=0;
		TCCR1A =0x01 ;
		while((PINA&0x01) == 0x00) ;
		while((PINA&0x01) == 0x01) ;
		{
			TCNT1 = 0x00;
		}
		while((PINA&0x00) ==0x00);
		while((PINA&0x01) ==0x01);
		{
			value = TCNT1;
		}
	 for (int t=0; value!=0 ; t++)
	 {
		 str[12+t]=value%10;
		 value=value/10;
		 count++;		 
	 }
	 for( int t=0; t<count;t++)
	 {
		 LCD_write(str[12+t]);
		 _delay_ms(5);
	 }
	 
	}
	return 0;
}
void init_LCD(void)
{
	LCD_cmd(0x38);
	_delay_ms(1);

	LCD_cmd(0x38);
	_delay_ms(1);
	LCD_cmd(0x38);
	_delay_ms(1);
	LCD_cmd(0x38);
	_delay_ms(1);
	LCD_cmd(0x38);
	_delay_ms(1);
	LCD_cmd(0x06);
	_delay_ms(1);
	LCD_cmd(0x0c);
	_delay_ms(1);
	LCD_cmd(0x01);
	_delay_ms(1);
	LCD_cmd(0x02);
	_delay_ms(1);
	return ;
}
void LCD_cmd(unsigned char cmd)
{
	PORTB=cmd;
	ctrl=(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl=(0<<rs)|(0<<rw)|(0<<en);
	_delay_ms(5);
	return;
}
void LCD_write(unsigned char data)
{
	PORTB=data;
	ctrl=(1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(1);
	ctrl=(1<<rs)|(0<<rw)|(0<<en);
	_delay_ms(5);
	return;
}
