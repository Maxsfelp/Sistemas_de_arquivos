#include "fat.h"

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

	fat[0] = 0xfffd;

	for(int i = 1; i <= 8; i++)
		fat[i] = 0xfffe;

	fat[9] = 0xffff;

	for(int i = 10; i <= 4095; i++)
		fat[i] = 0x0000;

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