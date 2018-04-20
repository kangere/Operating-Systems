/* ACADEMIC INTEGRITY PLEDGE                                              */
/*                                                                        */
/* - I have not used source code obtained from another student nor        */
/*   any other unauthorized source, either modified or unmodified.        */
/*                                                                        */
/* - All source code and documentation used in my program is either       */
/*   my original work or was derived by me from the source code           */
/*   published in the textbook for this course or presented in            */
/*   class.                                                               */
/*                                                                        */
/* - I have not discussed coding details about this project with          */
/*   anyone other than my instructor. I understand that I may discuss     */
/*   the concepts of this program with other students and that another    */
/*   student may help me debug my program so long as neither of us        */
/*   writes anything during the discussion or modifies any computer       */
/*   file during the discussion.                                          */
/*                                                                        */
/* - I have violated neither the spirit nor letter of these restrictions. */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Signed:_Paul Murage Date:_2/9/2018       */
/*                                                                        */
/*                                                                        */
/* 3460:4/526 BlackDOS2020 kernel, Version 1.01, Spring 2018.             */

void printLogo();
int mod(int,int);
int div(int,int);
void handleInterrupt21(int,int,int,int);

void main()
{
	
	char  buffer[512];
	int i;
	makeInterrupt21();
	for(i = 0; i < 512; i++)
  		buffer[i] = 0;

	buffer[0] = 1; /*Back ground colour*/
	buffer[1] = 10; /*Foregroud colour*/

    interrupt(33,6,buffer,258,0);
    interrupt(33,12,buffer[0] + 1, buffer[1] + 1,0);
    printLogo();
    interrupt(33,2,buffer,30,0);
    interrupt(33,0,buffer,0,0);


    while(1);
}

void printString(char* c, int d)
{
   /* fill this in */
   
   if(d == 1)
   {
      int i = 0;

      while(c[i] != '\0')
      {
         interrupt(23, c[i],0,0,0);
         i++;
      }
   } else if(d == 0){

      int i = 0;

      while(c[i] != '\0')
      {
         char al = c[i];
         char ah = 14;
         int ax = ah * 256 + al;
         interrupt(16, ax,0,0,0);
         i++;
      }
   }


   return;
}

void printLogo()
{
   printString("       ___   `._   ____  _            _    _____   ____   _____ \r\n\0",0);
   printString("      /   \\__/__> |  _ \\| |          | |  |  __ \\ / __ \\ / ____|\r\n\0",0);
   printString("     /_  \\  _/    | |_) | | __ _  ___| | _| |  | | |  | | (___ \r\n\0",0);
   printString("    // \\ /./      |  _ <| |/ _` |/ __| |/ / |  | | |  | |\\___ \\ \r\n\0",0);
   printString("   //   \\\\        | |_) | | (_| | (__|   <| |__| | |__| |____) |\r\n\0",0);
   printString("._/'     `\\.      |____/|_|\\__,_|\\___|_|\\_\\_____/ \\____/|_____/\r\n\0",0);
   printString(" BlackDOS2020 v. 1.01, c. 2018. Based on a project by M. Black. \r\n\0",0);
   printString(" Author(s): Paul Murage & Shriji Shah.\r\n\r\n\0",0);
}

/* MAKE FUTURE UPDATES HERE */
/* VVVVVVVVVVVVVVVVVVVVVVVV */


void readString(char *ch)
{

	int i = 0;
	char al;
  	char ah;
  	int ax;

  	do
    {
      ch[i] = interrupt(22,0,0,0,0);

    	if(ch[i] == '\b')
		{
		  printString("\b \b");
		  if(i > 0)
		    i--;
		}
     	else
		{
		  al = ch[i];
		  ah = 14;
		  ax = ah * 256 + al;
		  interrupt(16,ax,0,0,0);
		  i++;
		}
    }while(ch[i-1] != 13);

  	ch[i - 1] = '\0';
  	
  	printString("\r\n\0",0);
}

void readInt(int *x)
{
	char number[5];

	int i = 0;
  	*x = 0;
  	readString(number);
  	for(; number[i] != 0; i++)
  	{
    	*x = (*x) * 10;
    	*x = (*x) + number[i] - '0';
  	} 
  	printString("\r\n\0",0);
}

int mod(int a, int b)
{
	int x = a;
	while(x>=b) x = x - b;

	return x;
}

int div(int a, int b)
{
	int q =0;
	while(q *b <= a)q++;

	return (q-1);
}

void writeInt(int num)
{
	int temp = num,m;
	char number[6],*d;
	d = number + 5;
	*d = 0;
	d--;
	
	while(temp > 0)
	{
		m = mod(temp,10) ;
		temp = div(temp,10);
		*d = m + 48;	
		d--;
	}

	d++;
	/*reverse number to show right order*/
	


	printString(d,1);
}

void readSector(char * buffer, int sector)
{
	int ah = 2, 
		al = 1,/*number of sectors*/  
		ch, /*Track Number*/
		cl, /*relSecNo*/
		dh,/*HeadNo*/
		dl = 0, /*Device number*/
		ax,cx,dx;

	cl = (mod(sector,18) + 1);
	dh = mod(div(sector,18),2);
	ch = div(sector,36);


	ax = (ah * 256) + al;
	cx = (ch * 256) + cl;
	dx = (dh * 256) + dl;

	interrupt(19,ax,buffer,cx,dx);

}

void writeSector(char * buffer, int sector)
{
	int ah = 2, 
	al = 1,/*number of sectors*/  
	ch, /*Track Number*/
	cl, /*relSecNo*/
	dh,/*HeadNo*/
	dl = 0, /*Device number*/
	ax,cx,dx;

	cl = (mod(sector,18) + 1);
	dh = mod(div(sector,18),2);
	ch = div(sector,36);


	ax = 769;
	cx = (ch * 256) + cl;
	dx = (dh * 256) + dl;

	interrupt(19,ax,buffer,cx,dx);
}

void clearScreen(int bx, int cx)
{

  int i = 0 ;

	for(i = 0; i <= 24; i++)
   {
      printString("\r\n\0",0);
   }
	interrupt(16,512,0,0,0);

	if(bx > 0 && cx > 0)
		interrupt(16,1536,4096 *(bx -1) + 256 *(cx -1),0,6223);
}
/* ^^^^^^^^^^^^^^^^^^^^^^^^ */
/* MAKE FUTURE UPDATES HERE */

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
   
   switch(ax) {  
      case 0: 
         printString(bx,cx);
          break; 
      case 1:
      	readString(bx);	
      	break; 
      case 2:
      	readSector(bx,cx);
      	break; 
      /*case 3: case 4: case 5: 8*/
      case 6: 
      	writeSector(bx,cx);
      break;
      /*case 7: case 8: case 9: case 10: 
      case 11:*/ 
      case 12: 
      	clearScreen(bx,cx);
      break;

      case 13: 
      	writeInt(bx);
      	break;
      
      case 14:
      	readInt(bx);
      	break; 
      /*case 15: */
      default: printString("General BlackDOS error.\r\n\0",0); 
   }  
}