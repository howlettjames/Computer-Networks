#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

typedef unsigned char BYTE;

int main(void)
{
	char ch; 
	char byte[3];
	BYTE i = 0, j = 0;
	BYTE ip[4] = {0};
	bool move = true;
	BYTE mra[4] = {255, 0, 0, 0};
	BYTE mrb[4] = {255, 255, 0, 0};
	BYTE mrc[4] = {255, 255, 255, 0};
	
	for(;;)
	{	
		i = 0;
		j = 0;
		printf("Enter an IP: ");
		while((ch = getchar()) != '\n')
		{
			if(ch == '.')
			{
				if(atoi(byte) < 0 || atoi(byte) > 255)
					move = false;
				else
					ip[j++] = atoi(byte);
				
				i = 0;
				while(i < 3)
					byte[i++] = ' ';
				i = 0;	
			}
			else
				byte[i++] = ch;
		}
		
		ip[j] = atoi(byte); //Guarda ip[3]

 		if(move == true)
			break;
		else
			move = true;
		
		printf("Error: Entrada no valida\n");	
	}
	
	if(!(ip[0] & 128))
	{
		printf("Clase A\n");
		printf("IP madre: %d.%d.%d.%d\n", ip[0] & mra[0], ip[1] & mra[1], ip[2] & mra[2], ip[3] & mra[3]);
		mra[0] = ~mra[0];
		mra[1] = ~mra[1];
		mra[2] = ~mra[2];
		mra[3] = ~mra[3];
		printf("IP Broadcast: %d.%d.%d.%d\n", ip[0] | mra[0], ip[1] | mra[1], ip[2] | mra[2], ip[3] | mra[3]);
		mra[0] = ~mra[0];
		mra[1] = ~mra[1];
		mra[2] = ~mra[2];
		mra[3] = ~mra[3];
		printf("Rango de Host: %d.%d.%d.%d - ", ip[0] & mra[0], ip[1] & mra[1], ip[2] & mra[2], (ip[3] & mra[3]) + 1);
		mra[0] = ~mra[0];
		mra[1] = ~mra[1];
		mra[2] = ~mra[2];
		mra[3] = ~mra[3];
		printf("%d.%d.%d.%d\n", ip[0] | mra[0], ip[1] | mra[1], ip[2] | mra[2], (ip[3] | mra[3]) - 1 );

		if((ip[1] & 255) == 0 && (ip[2] & 255) == 0 && (ip[3] & 255) == 0)
			printf("Tipo: Red\n");
		else if((ip[1] & 255) == 255 && (ip[2] & 255) == 255 && (ip[3] & 255) == 255)
			printf("Tipo: Broadcast\n");
		else
			printf("Tipo: Host\n");		
	}	
	else if(!(ip[0] & 64))
	{
		printf("Clase B\n");
		printf("IP madre: %d.%d.%d.%d\n", ip[0] & mrb[0], ip[1] & mrb[1], ip[2] & mrb[2], ip[3] & mrb[3]);
		mrb[0] = ~mrb[0];
		mrb[1] = ~mrb[1];
		mrb[2] = ~mrb[2];
		mrb[3] = ~mrb[3];
		printf("IP Broadcast: %d.%d.%d.%d\n", ip[0] | mrb[0], ip[1] | mrb[1], ip[2] | mrb[2], ip[3] | mrb[3]);
		mrb[0] = ~mrb[0];
		mrb[1] = ~mrb[1];
		mrb[2] = ~mrb[2];
		mrb[3] = ~mrb[3];
		printf("Rango de Host: %d.%d.%d.%d - ", ip[0] & mrb[0], ip[1] & mrb[1], ip[2] & mrb[2], (ip[3] & mrb[3]) + 1);
		mrb[0] = ~mrb[0];
		mrb[1] = ~mrb[1];
		mrb[2] = ~mrb[2];
		mrb[3] = ~mrb[3];
		printf("%d.%d.%d.%d\n", ip[0] | mrb[0], ip[1] | mrb[1], ip[2] | mrb[2], (ip[3] | mrb[3]) - 1);

		if((ip[2] & 255) == 0 && (ip[3] & 255) == 0)
			printf("Tipo: Red\n");
		else if((ip[2] & 255) == 255 && (ip[3] & 255) == 255)
			printf("Tipo: Broadcast\n");
		else
			printf("Tipo: Host\n");		
	}
	else if(!(ip[0] & 32))
	{
		printf("Clase C\n");
		printf("IP madre: %d.%d.%d.%d\n", ip[0] & mrc[0], ip[1] & mrc[1], ip[2] & mrc[2], ip[3] & mrc[3]);
		mrc[0] = ~mrc[0];
		mrc[1] = ~mrc[1];
		mrc[2] = ~mrc[2];
		mrc[3] = ~mrc[3];
		printf("IP Broadcast: %d.%d.%d.%d\n", ip[0] | mrc[0], ip[1] | mrc[1], ip[2] | mrc[2], ip[3] | mrc[3]);
		mrc[0] = ~mrc[0];
		mrc[1] = ~mrc[1];
		mrc[2] = ~mrc[2];
		mrc[3] = ~mrc[3];
		printf("Rango de Host: %d.%d.%d.%d - ", ip[0] & mrc[0], ip[1] & mrc[1], ip[2] & mrc[2], (ip[3] & mrc[3]) + 1);
		mrc[0] = ~mrc[0];
		mrc[1] = ~mrc[1];
		mrc[2] = ~mrc[2];
		mrc[3] = ~mrc[3];
		printf("%d.%d.%d.%d\n", ip[0] | mrc[0], ip[1] | mrc[1], ip[2] | mrc[2], (ip[3] | mrc[3]) - 1);
		
		if((ip[3] & 255) == 0)
			printf("Tipo: Red\n");
		else if((ip[3] & 255) == 255)
			printf("Tipo: Broadcast\n");
		else
			printf("Tipo: Host\n");		
	}
	else if(!(ip[0] & 16))
	{
		printf("Clase D: Direcciones Multiples\n");
	}
	else
	{
		printf("Clase E: Experimentacion\n");
	}

	return 0;
}
