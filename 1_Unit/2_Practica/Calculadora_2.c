#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <math.h>

typedef unsigned char BYTE;

BYTE ones_counter(BYTE mr[], short *flag);

int main(void)
{
	char ch; 
	char byte[3];
	BYTE i = 0, j = 0, contador_unos = 0;
	BYTE ip[4] = {0};
	bool move = true;
	BYTE mr[4] = {0};
	short flag = 0;
	
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
		
		printf("Error: wrong IP\n");	
	}

	jumpmask:
	move = true;
	for(;;)
	{	
		i = 0;
		j = 0;
		printf("Enter a Mask: ");
		while((ch = getchar()) != '\n')
		{
			if(ch == '.')
			{
				if(atoi(byte) < 0 || atoi(byte) > 255)
					move = false;
				else
					mr[j++] = atoi(byte);
				
				i = 0;
				while(i < 3)
					byte[i++] = ' ';
				i = 0;	
			}
			else
				byte[i++] = ch;
		}
		
		mr[j] = atoi(byte); //Guarda mr[3]

 		if(move == true)
			break;
		else
			move = true;
		
		printf("Error: wrong Mask\n");	
	}

	flag = 0;
	if(!(ip[0] & 128))
	{
		contador_unos = ones_counter(mr, &flag);

		if(flag == -1)
		{
			printf("Error wrong Mask.\n");
			printf("\n");
			goto jumpmask;
		}
		if(contador_unos < 8)
		{
			printf("Error wrong Mask: not enough 1's\n");
			printf("\n");

			goto jumpmask;
		}
		if(contador_unos > 30)
		{
			printf("Error wrong Mask: there cannot be more than 30 bits of Mask\n");
			printf("\n");
			goto jumpmask;
		}
		printf("Clase A\n");
		printf("Bits prestados: %d\n", contador_unos - 8);
		printf("Bits Host: %d\n", 32 - contador_unos);
		printf("#Subredes: %.0f\n", pow(2, contador_unos - 8));
		printf("Host/Subred: 2^%d = %.0f\n", 32 - contador_unos, pow(2, 32 - contador_unos));

		printf("IP madre: %d.%d.%d.%d\n", ip[0] & mr[0], ip[1] & mr[1], ip[2] & mr[2], ip[3] & mr[3]);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("IP Broadcast: %d.%d.%d.%d\n", ip[0] | mr[0], ip[1] | mr[1], ip[2] | mr[2], ip[3] | mr[3]);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("Rango de Host: %d.%d.%d.%d - ", ip[0] & mr[0], ip[1] & mr[1], ip[2] & mr[2], (ip[3] & mr[3]) + 1);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("%d.%d.%d.%d\n", ip[0] | mr[0], ip[1] | mr[1], ip[2] | mr[2], (ip[3] | mr[3]) - 1 );

		if((ip[1] & 255) == 0 && (ip[2] & 255) == 0 && (ip[3] & 255) == 0)
			printf("Tipo: Red\n");
		else if((ip[1] & 255) == 255 && (ip[2] & 255) == 255 && (ip[3] & 255) == 255)
			printf("Tipo: Broadcast\n");
		else
			printf("Tipo: Host\n");		
	}	
	else if(!(ip[0] & 64))
	{
		contador_unos = ones_counter(mr, &flag);

		if(flag == -1)
		{
			printf("Error wrong Mask.\n");
			printf("\n");
			goto jumpmask;
		}
		if(contador_unos < 16)
		{
			printf("Error wrong Mask not enough 1's\n");
			printf("\n");
			goto jumpmask;
		}
		if(contador_unos > 30)
		{
			printf("Error wrong Mask: there cannot be more than 30 bits of Mask\n");
			printf("\n");
			goto jumpmask;
		}
		printf("Clase B\n");
		printf("Bits prestados: %d\n", contador_unos - 16);
		printf("Bits Host: %d\n", 32 - contador_unos);
		printf("#Subredes: %.0f\n", pow(2, contador_unos - 16));
		printf("Host/Subred: 2^%d = %.0f\n", 32 - contador_unos, pow(2, 32 - contador_unos));
	
		printf("IP madre: %d.%d.%d.%d\n", ip[0] & mr[0], ip[1] & mr[1], ip[2] & mr[2], ip[3] & mr[3]);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("IP Broadcast: %d.%d.%d.%d\n", ip[0] | mr[0], ip[1] | mr[1], ip[2] | mr[2], ip[3] | mr[3]);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("Rango de Host: %d.%d.%d.%d - ", ip[0] & mr[0], ip[1] & mr[1], ip[2] & mr[2], (ip[3] & mr[3]) + 1);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("%d.%d.%d.%d\n", ip[0] | mr[0], ip[1] | mr[1], ip[2] | mr[2], (ip[3] | mr[3]) - 1);

		if((ip[2] & 255) == 0 && (ip[3] & 255) == 0)
			printf("Tipo: Red\n");
		else if((ip[2] & 255) == 255 && (ip[3] & 255) == 255)
			printf("Tipo: Broadcast\n");
		else
			printf("Tipo: Host\n");		
	}
	else if(!(ip[0] & 32))
	{
		contador_unos = ones_counter(mr, &flag);

		if(flag == -1)
		{
			printf("Error wrong Mask.\n");
			printf("\n");
			goto jumpmask;
		}
		if(contador_unos < 24)
		{
			printf("Error wrong Mask: not enough 1's\n");
			printf("\n");
			goto jumpmask;
		}
		if(contador_unos > 30)
		{
			printf("Error wrong Mask: there cannot be more than 30 bits of Mask\n");
			printf("\n");
			goto jumpmask;
		}
		printf("Clase C\n");
		printf("Bits prestados: %d\n", contador_unos - 24);
		printf("Bits Host: %d\n", 32 - contador_unos);
		printf("#Subredes: %.0f\n", pow(2, contador_unos - 24));
		printf("Host/Subred: 2^%d = %.0f\n", 32 - contador_unos, pow(2, 32 - contador_unos));

		printf("IP madre: %d.%d.%d.%d\n", ip[0] & mr[0], ip[1] & mr[1], ip[2] & mr[2], ip[3] & mr[3]);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("IP Broadcast: %d.%d.%d.%d\n", ip[0] | mr[0], ip[1] | mr[1], ip[2] | mr[2], ip[3] | mr[3]);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("Rango de Host: %d.%d.%d.%d - ", ip[0] & mr[0], ip[1] & mr[1], ip[2] & mr[2], (ip[3] & mr[3]) + 1);
		mr[0] = ~mr[0];
		mr[1] = ~mr[1];
		mr[2] = ~mr[2];
		mr[3] = ~mr[3];
		printf("%d.%d.%d.%d\n", ip[0] | mr[0], ip[1] | mr[1], ip[2] | mr[2], (ip[3] | mr[3]) - 1);
		
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

BYTE ones_counter(BYTE mr[], short *flag)
{
	BYTE contador_unos = 0;
	bool vi_cero = false;

	for(BYTE i = 0; i < 4; i++)
		for(BYTE j = 128; j > 0; j = j >> 1)
		{
			if((mr[i] & j) && vi_cero == true)
			{
				*flag = -1;
				return 0;
			}

			if((mr[i] & j) && vi_cero == false)
				contador_unos++;
			else 
				vi_cero = true;
		}

	return contador_unos;	
}