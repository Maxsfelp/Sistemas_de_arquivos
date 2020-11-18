#include "fat.h"
#include <stdio.h>

uint16_t fat[4096];

union {
	dir_entry_t dir[CLUSTER_SIZE / sizeof(dir_entry_t)];
	uint8_t data[CLUSTER_SIZE];
} data_cluster;

int init(){
	FILE *fatPart = fopen("fat.part", "wb");

	if(fatPart == NULL){
		printf("Falha ao iniciar a FAT\n");
		return 0;
	}

	uint16_t boot = 0xbbbb;

	for(int i = 0; i < 512; i++)
		fwrite(&boot, sizeof(boot), 1, fatPart);

	fat[0] = 0xfffd;

	for(int i = 1; i <= 8; i++)
		fat[i] = 0xfffe;

	fat[9] = 0xffff;

	for(int i = 10; i <= 4095; i++)
		fat[i] = 0x0000;

	fwrite(fat, sizeof(uint16_t), 4096, fatPart);

	dir_entry_t root[32];
	memset(root, 0, 32*sizeof(dir_entry_t));

	fwrite(root, sizeof(dir_entry_t), 32, fatPart);

	uint8_t t[CLUSTER_SIZE];
	memset(t, 0, CLUSTER_SIZE);

	for(int i = 0; i < 4086; i++)
		fwrite(t, 1, CLUSTER_SIZE, fatPart);

	fclose(fatPart);
	return 1;
}

int load(){
	printf("tudo certo\n");
	return 1;
}

int ls_fat(char *caminho){
	printf("%s\n", caminho);
	return 1;
}