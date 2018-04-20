int comp(char*,char*);
int isUpper(char);

void main()
{
	char buffer[512];
	
	interrupt(33,2,buffer,258,0);
  	interrupt(33,12,buffer[0]+1,buffer[1]+1,0);

	
  	while(1)
  	{
  		char *input;
  		int i = 0, j = 0;
  		char command[512];

  		interrupt(33,0,"\n\rblackdos ~(__^>\0",0,0);

  		/*read text*/
  		interrupt(33,1,input,0,0);

  		/*check commands inputed*/
  		if(comp(input,"boot\0"))
  		{
  			interrupt(33,11,0,0,0);
  			continue;
  			
  			
  		}
  		else if(comp(input,"cls\0"))
  		{
  			interrupt(33,12,buffer[0]+1,buffer[1]+1,0);
  			continue;
  			
  		}
  		else if(comp(input,"help\0"))
  		{
  			char buffer[1024];
  			int size;
  			interrupt(33,3,"Manual\0",buffer,&size);
  			interrupt(33,0,buffer,0,0);
  			continue;
  		}
  		else if(comp(input,"dir\0"))
  		{

  			char buffer[512];
  			char file[10];
  			int start,end,k=0;
  			i = 0;

  			interrupt(33,2,buffer,257,0);

  			
  			while(i < 512)
  			{
  				k = 0;
  				start = i;
  				end = start + 8;

  				for(;start < end; ++start)
  				{
  					if(buffer[start] == 0)
  						break;

  					file[k] = buffer[start];
  					k++;
  				}

  				if(k == 0)
  				{
  					i+=32;
  					continue;
  				}

  				file[k] = '\0';
    			

    			if(!isUpper(file[0]))
    			{
    				interrupt(33,0,"\n\0",0,0);
    				interrupt(33,0,file,0,0);
    			}

    			i+=32;

  			}
  			
  			continue;

  		}

  		
  		
		
  		while(i < 512 && input[i] != '\0')
  		{
  			command[i] = input[i];
  			i++;
  		}
  		

  		/*9 letter command*/
  		command[9] = '\0';
  		if(comp(command,"setenv fg\0"))
  		{
  			char buffer[512];
  			int size;

  			char color[10];
  			i = 0;
  			
  			for(j = 9; input[j] != '\0';j++)
  			{
  				if(input[j] != 32)
  				{
  					color[i] = input[j];
  					i++;
  				}
  				
  			}

  			if(i >= 9)
  				color[511] = '\0';
  			else
  				color[i] = '\0';

  			
  			interrupt(33,6,buffer,258,0);
  			interrupt(33,12,buffer[0]+1,color+1,0);

  			continue;
  		}
  		if(comp(command,"setenv bg"))
  		{
  			
  		}


  		/*6 letter command*/
  		command[6] = '\0';
  		if(comp(command,"lprint\0"))
  		{
  			char buffer[12288];
  			int size;

  			char filename[512];
  			i = 0;
  			
  			for(j = 6; input[j] != '\0';j++)
  			{
  				if(input[j] != 32)
  				{
  					filename[i] = input[j];
  					i++;
  				}
  				
  			}

  			if(i >= 511)
  				filename[511] = '\0';
  			else
  				filename[i] = '\0';

  			interrupt(33,0,"\n\0",0,0);
  			interrupt(33,3,filename,buffer,&size);
  			interrupt(33,0,buffer,1,0);
  		}
  		/*5 letter commands*/

  		command[5] = '\0';

  		if(comp(command,"tweet\0"))
  		{
  			char buffer[140];
  			char filename[512];
  			i = 0;
  			
  			for(j = 5; input[j] != '\0';j++)
  			{
  				if(input[j] != 32)
  				{
  					filename[i] = input[j];
  					i++;
  				}
  				
  			}

  			if(i >= 511)
  				filename[511] = '\0';
  			else
  				filename[i] = '\0';

  			interrupt(33,0,"Enter 140 characters to file: \0",0,0);
  			interrupt(33,0,"\n\0",0,0);

  			/*read input to buffer*/
  			interrupt(33,1,buffer,0,0);

  			/*write buffer to file*/
  			interrupt(33,8,filename,buffer,1);
  			
  		}


  		/*4 letter commands*/
  		command[4] = '\0';
  		/*copy command*/
  		if(comp(command,"copy\0"))
  		{
  			
  		}
  		else if(comp(command,"echo\0")) /*echo command*/
  		{
  			
  			char temp[512];
  			i = 0;
  			for(j = 4; input[j] != '\0'; j++)
  			{
  				temp[i] = input[j];
  				i++;
  			}
  			if(i >= 511)
  				temp[511] = '\0';
  			else
  				temp[i] = '\0';

  			interrupt(33,0,"\n\0",0,0);
  			interrupt(33,0,temp,0,0);
  			continue;
  		}
  		/*type command*/
  		if(comp(command,"type\0"))
  		{
  			char buffer[12288];
  			int size;

  			char filename[512];
  			i = 0;
  			
  			for(j = 4; input[j] != '\0';j++)
  			{
  				if(input[j] != 32)
  				{
  					filename[i] = input[j];
  					i++;
  				}
  				
  			}

  			if(i >= 511)
  				filename[511] = '\0';
  			else
  				filename[i] = '\0';

  			if(isUpper(filename[0]))
  			{
  				interrupt(33,0,"\n\0",0,0);
  				interrupt(33,0,"duplicate or invalid file name\0",0,0);
  				continue;
  			}

  			interrupt(33,0,"\n\0",0,0);
  			interrupt(33,3,filename,buffer,&size);
  			interrupt(33,0,"\n\0",0,0);
  			interrupt(33,0,buffer,0,0);

  			continue;
  		}

  		/*3 letter commands*/
  		command[3] = '\0';

  		/*delete file command*/
  		if(comp(command,"del\0"))
  		{
  			/*interrupt(33,0,"\ndel called\0",0,0);*/
  			char filename[512];
  			i = 0;
  			
  			for(j = 3; input[j] != '\0';j++)
  			{
  				if(input[j] != 32)
  				{
  					filename[i] = input[j];
  					i++;
  				}
  				
  			}

  			if(isUpper(filename[0]))
  			{
  				interrupt(33,0,"\n\0",0,0);
  				interrupt(33,0,"duplicate or invalid file name\0",0,0);
  				continue;
  			}

  			if(i >= 511)
  				filename[511] = '\0';
  			else
  				filename[i] = '\0';

  			interrupt(33,7,filename,0,0);
  			continue;

  		}

  		/*run filename command*/
  		if(comp(command,"run\0"))
  		{
  			char filename[512];
  			i = 0;
  			
  			for(j = 3; input[j] != '\0';j++)
  			{
  				if(input[j] != 32)
  				{
  					filename[i] = input[j];
  					i++;
  				}
  			}

  			if(i >= 511)
  				filename[511] = '\0';
  			else
  				filename[i] = '\0';

  			interrupt(33,4,filename,0,0);
  			continue;

  		}


  	}

	while(1);
}

int comp(char* c1, char* c2)
{
   while(*c1 != '\0')
   {
      if(*c1++ != *c2++) return 0;
   }

   return 1;
}

int isUpper(char c)
{
	if(c >= 65 && c <= 90)
		return 1;

	return 0;
}

