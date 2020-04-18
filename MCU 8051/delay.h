void delay_short()  // short delay
{
	unsigned int i;
	for(i=0;i<100;i++);
}
void delay_ff()  // fully fixed delay
{
    unsigned int i,j;
	
    for(i=0;i<80;i++)
    for(j=0;j<120;j++);
}

void delay_pf(unsigned int x)  // partial variable delay
{
	unsigned int i,j;
	
	for(i=0;i<x;i++)
	for(j=0;j<50;j++);
}

void delay_fv(unsigned int x,y)  // fully variable delay
{
	unsigned int i,j;
		
	for(i=0;i<x;i++)
	for(j=0;j<y;j++);
}


void msdelay(unsigned int time)  // Function for creating delay in milliseconds.
{
    unsigned i,j ;
    for(i=0;i<time;i++)    
    for(j=0;j<83;j++);
}

void servo_delay(int times)     // Creating Delay in multilple of 50us using 8051 Timers
{
    int m;
    for(m=0;m<times;m++)
    {
        TH0=0xFF;
        TL0=0xD2;
        TR0=1;
        while(TF0==0);
        TF0=0;
        TR0=0;
    }
}