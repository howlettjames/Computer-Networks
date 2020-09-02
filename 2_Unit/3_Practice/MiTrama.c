#include <stdio.h>

typedef unsigned char BYTE;

BYTE ones_counter(BYTE t[], BYTE size);
	
int main(void)
{
	//BYTE t[] = {0x83, 0x22, 0x45, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x21, 0xB8, 0x20, 0x90}; //Minúsculas
	BYTE t[] = {0x83, 0x22, 0x45, 0x48, 0x45, 0x4C, 0x4C, 0x4F, 0x21, 0xB4, 0x20, 0x90}; //Mayúsculas
	//BYTE t[] = {0x81, 0x22, 0x45, 0x48, 0x45, 0xB4, 0x20, 0x90}; //Prueba mensaje "HE"
	BYTE idioma[][4] = {"Fr", "Ale", "Ing", "Esp"};
	BYTE grupo[][5] = {"2CM8", "3CM5", "4CV7"};
	BYTE enrutamiento[][13] = {"Estatico", "Estatico", "Dijstra", "Bellmau Ford"};
	BYTE control_flujo[][18] = {"Parar/Esperar", "Parar/Esperar", "Retroceder N", "Rechazo Selectivo"};
	BYTE tam = (t[0] & 63) * 2;
	BYTE i = 0, j = 0, k = 0, l = 0;
	BYTE contador_unos;
	BYTE px = 0x07;
	BYTE crc = 0;
	BYTE nat_begin = 1;
	unsigned short checksum = 0, temp = 0;

	printf("Idioma: %s\n", idioma[t[0] >> 6]);
	printf("Tamano: %d bytes\n", tam);
	printf("IDo: %s No.%d\n", grupo[t[1] >> 6], t[1] & 63);
	printf("IDd: %s No.%d\n", grupo[t[2] >> 6], t[2] & 63);
	printf("Mensaje: ");
	for(i = 3; i < tam + 3; i++)
		printf("%c", t[i]);
	printf("\nEnrutamiento: %s\n", enrutamiento[t[tam + 3] >> 6]);
	printf("Control de Flujo: %s\n", control_flujo[(t[tam + 3] >> 4) & 3]);
	printf("Control de Error: ");
	switch((t[tam + 3] >> 2) & 3)
	{
		case 0:
			printf("Bit Paridad ");
			if(t[tam + 3] & 2)
			{
				printf("Impar -> ");
				contador_unos = ones_counter(t, 4 + tam);
				if(!(contador_unos & 1))
					printf("Trama danada\n");
				else
					printf("Trama correcta\n");
			}
			else
			{
				printf("Par -> ");
				contador_unos = ones_counter(t, 4 + tam);
				if(contador_unos & 1)
					printf("Trama danada\n");
				else
					printf("Trama correcta\n");
			}
		break;
		case 1:
			printf("CRC ");
			if(t[tam + 3] & 2)
			{ 
				printf("2 bytes\n");
			}
			else
			{
				printf("1 byte ");
				crc = 0;
				l = 128;
				for(i = 0; i < 4 + tam; i++)
				{	
					for(j = l, k = 0; j > 0; j = j >> 1)
					{
						if(crc & 128)
						{
							if(t[i] & j)
								crc = (crc << 1) | 1;
							else
								crc = crc << 1;
							k++;

							crc = crc ^ px;
							//printf("CRC: %d\n", crc);
						}
						else
						{
							if(t[i] & j)
								crc = (crc << 1) | 1;
							else
								crc = crc << 1;
							k++;
							l = 128;	

							if((i == (3 + tam)) && k == 8)
								break;

							if((crc & 128) && ((j >> 1) == 0))
							{
								if(t[i + 1] & 128)
									crc = (crc << 1) | 1;
								else
									crc = crc << 1;	

								crc = crc ^ px;
								//printf("CRC: %d\n", crc);
								l = 64;
							}
							else if((crc & 128) && ((j >> 1) != 0))
							{
								j = j >> 1;	
								if(t[i] & j)
									crc = (crc << 1) | 1;
								else
									crc = crc << 1;
								k++;

								crc = crc ^ px;
								//printf("CRC: %d\n", crc);
							}	
						}						
					}
				}
				printf("\nCRC: %.4X\n", crc);
			}
		break;
		case 2:
			printf("Checksum\n");
			checksum = 0;
			temp = 0;

			for(j = 128; j > 0; j >>= 1)
				if(t[0] & j)
					checksum = (checksum << 1) | 1;
				else
					checksum <<= 1;
			for(j = 128; j > 0; j >>= 1)
				if(t[1] & j)
					checksum = (checksum << 1) | 1;
				else
					checksum <<= 1;

			//printf("Checksum: %4X\n", checksum);
			for(i = 2; i < 4 + tam; i++)
			{
				for(j = 128; j > 0; j >>= 1)
					if(t[i] & j)
						temp = (temp << 1) | 1;
					else
						temp <<= 1;
				i++;
				for(j = 128; j > 0; j >>= 1)
					if(t[i] & j)
						temp = (temp << 1) | 1;
					else
						temp <<= 1;

				if(((checksum >> 12) + (temp >> 12)) > 15)
					checksum += 1;	
				//printf("Temp: %4X\n", temp);
				checksum += temp;	
				//printf("Checksum: %4X\n", checksum);
				//printf("\n");
			}
			checksum = ~checksum;
			printf("Checksum: %4X\n", checksum);	
		break;
		case 3:
			printf("~\n");
		break;
	}
	return 0;
}

BYTE ones_counter(BYTE t[], BYTE size)
{
	BYTE contador_unos = 0;

	for(BYTE i = 0; i < size; i++)
		for(BYTE j = 128; j > 0; j = j >> 1)
			if(t[i] & j)
				contador_unos++;

	return contador_unos;	
}