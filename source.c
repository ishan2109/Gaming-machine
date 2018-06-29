#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#define lcd PORTB
#define rs 0
#define rw 1
#define en 2
#define F_CPU  1000000
unsigned long int a=3;b=4;c;
int key;
int i,ver;
int count;
   // Write your code here
       void lcd_init();
	   void lcd_command(unsigned char);
	   void lcd_data(unsigned char);
	  void lcd_number(unsigned int value);
	   void lcd_string(unsigned char *str);
	   int  random();

	   unsigned char keyscan()
{
		while(1)
	{
	PORTD = 0X0e;
	_delay_ms(5);  /////must for response at porta when key press
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return '0';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return '1';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return '2';}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return '3';}

	PORTD = 0X0d;
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return '4';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return '5';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return '6';}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return '7';}

	PORTD = 0X0b;
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return '8';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return '9';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return 'A';}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return 'B';}

	PORTD = 0X07;
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return 'C';}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return 'D';}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return 'E';}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return 'F';}

	}
}
		int keyscan_num()
{
		while(1)
	{
	PORTD = 0X0e;
	_delay_ms(5);  /////must for response at porta when key press
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return 1;}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return 2;}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return 3;}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return 10;}

	PORTD = 0X0d;
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return 4;}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return 5;}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return 6;}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return 11;}

	PORTD = 0X0b;
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return 7;}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return 8;}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return 9;}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return 12;}

	PORTD = 0X07;
	_delay_ms(5);
	if((PINA&0b00000001)==0){while(!(PINA&0b00000001)); return 13;}
	if((PINA&0b00000010)==0){while(!(PINA&0b00000010)); return 0;}
	if((PINA&0b00000100)==0){while(!(PINA&0b00000100)); return 14;}
	if((PINA&0b00001000)==0){while(!(PINA&0b00001000)); return 15;}
	}
}
	int random()
		    {

				c=(a+b)*5/3;
		        b=c;
				if(c>999)
				    {
					a=2;
				    b=4;
					c=10+ a+ b;
					a=b;
					return c;
					}
					a=b;
				return c;

				}




		void lcd_number(unsigned int value)
{
	unsigned int d=0;
	lcd_command(0x04);	//auto decrement mode

	if(value==0)
	lcd_data(value+48);

	while(value!=0)
	{
	d=value%10;
	lcd_data(d+48);
	value=value/10;
	}
	lcd_command(0x06);	//auto increment mode
}
	   void lcd_init(){
	    lcd_command(0x02);
		   lcd_command(0x28);
		   lcd_command(0x06);
		   lcd_command(0x0c);
	   }

		   void lcd_command(unsigned char com) {
			   lcd = com & 0xF0;
			   //send higher bit
			   lcd &= ~(1<<rs);
			   //rs =0
			   lcd &= ~(1<<rw);
			   //rw=0
			   lcd |=(1<<en);
			   //en =1
			   _delay_ms(1);
			   lcd &= ~(1<<en);
			   //en =0
			   _delay_ms(1);
               lcd = (com<<4) & 0xF0;
			   //send lower bit
			   lcd &= ~(1<<rs);
			   //rs =0
			   lcd &= ~(1<<rw);
			   //rw=0
			   lcd |=(1<<en);
			   //en =1
			   _delay_ms(1);
			   lcd &= ~(1<<en);
			   //en =0
		   }
			   void lcd_data(unsigned char value)
			   {
				   lcd =value & 0xF0;
				   //send higher bit
				   lcd |= (1<<rs);
				   //rs =1
				   lcd &= ~(1<<rw);
				   //rw=0
				   lcd |=(1<<en);
				   //en =1
				   _delay_ms(1);
				   lcd &= ~(1<<en);
				   //en =0
				   _delay_ms(1);
                   lcd =(value<<4) & 0xF0;
				   //send lower bit
				   lcd |= (1<<rs);
				   //rs =1
				   lcd &= ~(1<<rw);
				   //rw=0
				   lcd |=(1<<en);
				   //en =1
				   _delay_ms(1);
				   lcd &= ~(1<<en);
				   //en =0
				   _delay_ms(1);
				   }
	   void lcd_string(unsigned char *str)
				   {
					   char i=0;
					   while(str[i]!='\0')
						   {
							   lcd_data(str[i]);
							   i++;
							   }
					}



   int main()
   {
	   DDRC = 0XFF;
	   while(1)
	   {
			unsigned char d;
			DDRB = 0XFF;
		    DDRA = 0XF0;
	        DDRD = 0XFF;
			PORTA = 0X0F;
			lcd_init();
							lcd_command(0xc0);
							lcd_string("                  ");
		                    lcd_command(0x03);
					        lcd_string("Press Play      ");
		                     lcd_command(0x03);
		                    _delay_ms(1000);


		    if (keyscan_num()==14){
							lcd_command(0x03);
							lcd_string(" Welcome to      ");
							lcd_command(0xc0);
							lcd_string(" THE MEMORY GAME  ");
							lcd_command(0x03);
							_delay_ms(2000);
							lcd_string("Six Numbers will..      ");
							lcd_command(0xc0);
							lcd_string("be flashed now..     ");
							_delay_ms(2000);
							lcd_command(0x03);
							lcd_string("A random number    ");
							lcd_command(0xc0);
							lcd_string("will be asked..     ");
							lcd_command(0x03);
							_delay_ms(2000);
							lcd_command(0x03);
							lcd_string("Enter correct    ");
							lcd_command(0xc0);
							lcd_string("answer for..         ");
							_delay_ms(2000);
							lcd_command(0x03);
							lcd_string("****JACKPOT****       ");
							lcd_command(0xc0);
                            lcd_string("                   ");
							_delay_ms(2000);
							lcd_command(0x03);
							lcd_string(" Ready?        ");
							_delay_ms(1000);
							lcd_command(0x03);
							lcd_string("3...            ");
							_delay_ms(500);
							lcd_command(0x03);
							lcd_string("2..              ");
							_delay_ms(500);
							lcd_command(0x03);
							lcd_string("1.           ");
							_delay_ms(500);
							lcd_command(0x03);
	       					lcd_command(0x0c);
        lcd_string(" ");
		lcd_number(random());
		_delay_ms(500);
        lcd_string("       ");
		if (count==2)
		 ver=c;
        lcd_number(random());
		_delay_ms(500);
		lcd_string("        ");
		if (count==5)
		 ver=c;
		lcd_number(random());
		_delay_ms(500);
		lcd_string("        ");
		if (count==0)
		 ver=c;
		lcd_command(0xc0);
		lcd_string(" ");
		lcd_number(random());
		_delay_ms(500);
        lcd_string("        ");
		if (count==4)
		 ver=c;
        lcd_number(random());
		_delay_ms(500);
		lcd_string("        ");
		if (count==1)
		 ver=c;
		lcd_number(random());
		_delay_ms(500);
		lcd_string("        ");
		if (count==3)
		ver=c;

	    lcd_command(0x03);
		while(count<5)
		{
			if(count==5)
				count=0;
			if(count==0)
			{
	    lcd_string("Enter Third ");
		//lcd_command(0xc0);
		count++;
		break;
			}
			else if(count==1)
			{
		lcd_command(0x03);
	    lcd_string("Enter Fifth ");
		//lcd_command(0xc0);
		count++;
		break;
			}
			else if(count==2)
			{
		lcd_command(0x03);
	    lcd_string("Enter First ");
		//lcd_command(0xc0);
		count++;
		break;
			}
			if(count==3)
			{
		lcd_command(0x03);
	    lcd_string("Enter Sixth ");
		//lcd_command(0xc0);
		count++;
		break;
			}
			else if(count==4)
			{
		lcd_command(0x03);
	    lcd_string("Enter Fourth ");
		//lcd_command(0xc0);
		count++;
		break;
			}
			else if(count==5)
			{
		lcd_command(0x03);
	    lcd_string("Enter Second ");
		//lcd_command(0xc0);
		count++;
		break;
			}
		}
		lcd_command(0xc0);
		lcd_string("Number     ");
		lcd_command(0xc0);
		_delay_ms(1000);
		lcd_command("                          ");
		lcd_command(0x03);
		lcd_string("In three digit   ");
		lcd_command(0xc0);
		lcd_string("form here: ");
		    int hund=keyscan_num();
			while(hund==10 || hund==11 || hund==12 || hund==15)
			{
		    hund=keyscan_num();
			}
			lcd_command(0x14);
			lcd_number(hund);
			lcd_command(0x14);
			int tens=keyscan_num();
			while(tens==10 || tens==11 || tens==12 || tens==15)
			{
		    tens=keyscan_num();
			}
			lcd_command(0x14);
			lcd_number(tens);
			lcd_command(0x14);
			int ones=keyscan_num();
			while(ones==10 || ones==11 || ones==12 || ones==15)
			{
		    ones=keyscan_num();
			}
			lcd_command(0x14);
			lcd_number(ones);
			lcd_command(0x14);
			_delay_ms(1000);
			lcd_command(0x01);

			int num = hund*100 + tens*10 + ones;
			_delay_ms(1000);
			lcd_string("wait...         ");
		    _delay_ms(1000);
			lcd_command(0x03);
			lcd_string("                ");
				if(num==ver){
				lcd_command(0x03);
				lcd_string("  You got it!");
				_delay_ms(1000);
				lcd_command(0xc0);
				lcd_string(" Collect prize");
				PORTA=0xA0;
				PORTC = 0x80;
				_delay_ms(3000);
				PORTC = 0x00;
				_delay_ms(3000);
				PORTA=0x50;
				lcd_command(0x03);
			    lcd_command(0x0c);
				lcd_string("  Thank you  ");
			}
			else
			{
				lcd_command(0x03);
				lcd_string("Sorry! You lost.   ");
				_delay_ms(2000);
			}
		}
	}

	   return 0;
 }
	   
