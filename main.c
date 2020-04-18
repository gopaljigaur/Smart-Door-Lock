#include<reg51.h>
#include"delay.h"
#include"lcd.h"
#include"keypad.h"

sbit a1=P2^0; //Servo
sbit a2=P2^1; //NodeMCU door open
sbit a3=P2^2; //NodeMCU password change
void motor();
unsigned char ar[5];
unsigned char temp[5];
unsigned char cc[5]={"ABCCD"}; //Password Reset Passkey
unsigned char com[5]={"00000"}; //Default Passkey
unsigned int f,m=1,p,pc=0;

void main()
{
	unsigned int i;
	lcd_ini();
	while(1)
	{
		a2=1;
		a3=1;
		cmd(0x01);
		lcd_str(" ENTER YOUR");
		cmd(0xc0);
		lcd_str(" PASSWORD");
		
		for(i=0;i<5;i++)
		{
			keypad1();
			ar[i]=c;
			if(i==0)
			{
			  cmd(0x01);
				lcd_display(' ');
			}
			lcd_display('*');
		}
		if(ar[0]==com[0] && ar[1]==com[1] && ar[2]==com[2] && ar[3]==com[3] && ar[4]==com[4])
		{
			m=1;pc=0;
		}
		else if(ar[0]==cc[0] && ar[1]==cc[1] && ar[2]==cc[2] && ar[3]==cc[3] && ar[4]==cc[4])
			{
			m=1;pc=1;
			}
		else
			{
				m=0;pc=0;
			}

		if((m==1)&&(pc==0))
		{
			cmd(0x01);
			lcd_str(" KEY MATCHED");
			cmd(0xc0);
			lcd_str(" ACCESS GRANTED");
			motor();
			p=0;
			delay_fv(1000,100);
		}
		else if((m==1)&&(pc==1))
		{
			cmd(0x01);
		lcd_str(" ENTER OLD");
		cmd(0xc0);
		lcd_str(" PASSWORD");
			for(i=0;i<5;i++)
		{
			keypad1();
			ar[i]=c;
			if(i==0)
			{
			  cmd(0x01);
				lcd_display(' ');
			}
			lcd_display('*');
		}
		if(ar[0]==com[0] && ar[1]==com[1] && ar[2]==com[2] && ar[3]==com[3] && ar[4]==com[4])
		{
			m=1;
		}
		else
		{
			m=0;
		}
		if(m==1){
			cmd(0x01);
			lcd_str(" ENTER NEW");
			cmd(0xc0);
			lcd_str(" PASSWORD");
			p=0;
			for(i=0;i<5;i++)
		{
			keypad1();
			ar[i]=c;
			if(i==0)
			{
				cmd(0x01);
				lcd_display(' ');
			}
			lcd_display('*');
		}
		cmd(0x01);
		lcd_str(" CONFIRM NEW");
			cmd(0xc0);
		lcd_str(" PASSWORD");
			
		for(i=0;i<5;i++)
		{
			keypad1();
			temp[i]=c;
			if(i==0)
			{
				cmd(0x01);
				lcd_display(' ');
			}
			lcd_display('*');
		}
		if(ar[0]==temp[0] && ar[1]==temp[1] && ar[2]==temp[2] && ar[3]==temp[3] && ar[4]==temp[4])
		{
			for(i=0;i<5;i++)
				com[i]=temp[i];
			a3=0;
			cmd(0x01);
		lcd_str(" CHANGING");
			cmd(0xc0);
		lcd_str(" PASSWORD");
			delay_pf(3000);
			cmd(0x01);
		lcd_str(" PASSWORD");
			cmd(0xc0);
		lcd_str(" CHANGED");
			delay_pf(2000);
			a3=1;
		}
		else
		{
			cmd(0x01);
			lcd_str(" PASSWORDS DID");
			cmd(0xc0);
			lcd_str(" NOT MATCH");
		}
	}
		else if(m==0)
		{
			p++; //incorrect attempt++
			cmd(0x01);
			lcd_str(" WRONG PASSWORD");
			cmd(0xc0);
			lcd_str(" ACCESS DENIED");
			delay_fv(1000,100);
			delay_fv(1000,100);
			m=1;
			if(p==4)
			{
					cmd(0x01);
					lcd_str(" TOO MANY");
					cmd(0xc0);
					lcd_str(" WRONG ATTEMPTS");
					while(p==4);
			}
		}
		delay_fv(1000,100);
		m=1;
		}
		else if((m==0)&&(pc==0))
		{
			p++; //incorrect attempt++
			cmd(0x01);
			lcd_str(" WRONG PASSWORD");
			cmd(0xc0);
			lcd_str(" ACCESS DENIED");
			delay_fv(1000,100);
			delay_fv(1000,100);
			m=1;
			if(p==4)
			{
					cmd(0x01);
					lcd_str(" TOO MANY");
					cmd(0xc0);
					lcd_str(" WRONG ATTEMPTS");
					while(p==4);
			}
		}
	}
}

void motor()
{ 
	unsigned int i;
	a2=0;
	  for(i=0;i<80;i++)
	{
   a1=1;
		msdelay(2);
		a1=0;
		msdelay(25);
  }
	delay_fv(1000,280);
	for(i=0;i<70;i++)
	{
   a1=1;
		delay_fv(10,2);
		a1=0;
		msdelay(26);
  }
	a2=1;
}