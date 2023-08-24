/*
 * main.c
 *
 * Created: 8/23/2023 4:46:18 PM
 *  Author: Mohamed Hosam
 */ 

#include <xc.h>
#include <avr/io.h>
#include <avr/delay.h>

//Defining LCD PINS

#define LCD_data PORTB	//Port B is selected as data port
#define rs PD2     //Register select signal is connected to port D pin 2
#define rw PD1     //Read/Write signal is connected to port D pin 1
#define en PD0     //Enable signal is connected to port D pin 0

void lcd_init(void);    //initialize LCD initialization function
void lcd_write(unsigned char data);    //function to write character on LCD
void lcd_cmd(unsigned char cmd);    //function to send commands to LCD

int main(void)
{
    while(1)
    {
        DDRB = 0xff;
		DDRD = 0xff;
		
		lcd_init(); //initialize LDC
		_delay_ms(100);
		
		lcd_cmd(0x0c);	//display on, cursor off
		_delay_ms(100);
		
		for (uint8_t i =0; i < 4; i++)
		{
			lcd_write(' ');
			_delay_ms(1);
		}
	//**********************************//	
		lcd_write('M');
		_delay_ms(100);
		lcd_write('o');
		_delay_ms(100);
		lcd_write('h');
		_delay_ms(100);
		lcd_write('a');
		_delay_ms(100);
		lcd_write('m');
		_delay_ms(100);
		lcd_write('e');
		_delay_ms(100);
		lcd_write('d');
		_delay_ms(100);
		
		lcd_cmd(0xc0);  //go to 2nd line
		_delay_ms(100);
		
		for (uint8_t x=0; x<6; x++)
		{
			lcd_write(' ');
			_delay_ms(1);
		}
		lcd_write('2');
		_delay_ms(100);
		lcd_write('0');
		_delay_ms(100);
		lcd_write('0');
		_delay_ms(100);
		lcd_write('1');
		_delay_ms(1000);
	}
	
}

void lcd_init(void)
{
	lcd_cmd(0x38);	//initialization of 16x2 LCD in 8-bit mode
	_delay_ms(1);
	lcd_cmd(0x01);	//clear display
	_delay_ms(1);
	lcd_cmd(0x02);  //return home
	_delay_ms(1);
	lcd_cmd(0x06);  //auto increment cursor
	_delay_ms(1);
	lcd_cmd(0x80);  //cursor at home position
}

void lcd_cmd(unsigned char cmd)
{
	LCD_data = cmd;	//sending command LCD
	PORTD &= ~(1<<rs);	//RS is set to 0
	PORTD &= ~(1<<rw);  //RW is set to 0
	PORTD |= (1<<en);  //Enable is set to 1
	_delay_ms(2);
	PORTD &= ~(1<<en);  //Enable is set to 0
}

void lcd_write(unsigned char data)
{
	LCD_data = data;
	PORTD |= (1<<rs);  //Make the RS pin High
	PORTD &= ~(1<<rw);  //Make the RW pin Low
	PORTD |= (1<<en);  //Enable is set to 1
	_delay_ms(2);
	PORTD &= ~(1<<en);  //Enable is set to 0
}
