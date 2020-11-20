#include "fat.h"
#include <stdio.h>

static uint16_t fat[4096];

static dir_entry_t root[32];

static uint8_t dadaCluster[CLUSTER_SIZE];

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

	memset(root, 0, 32*sizeof(dir_entry_t));

	fwrite(root, sizeof(dir_entry_t), 32, fatPart);

	memset(dadaCluster, 0, CLUSTER_SIZE);

	for(int i = 0; i < 4086; i++)
		fwrite(dadaCluster, 1, CLUSTER_SIZE, fatPart);

	fclose(fatPart);
	return 1;
}

int load(){
	FILE *fatPart = fopen("fat.part", "rb+");

	if(fatPart == NULL){
		printf("Falha ao iniciar a FAT\n");
		return 0;
	}

	uint8_t dummy[CLUSTER_SIZE];

	fread(dummy, 1, CLUSTER_SIZE, fatPart);

	fread(fat, sizeof(uint16_t), 4096, fatPart);

	fread(root, sizeof(dir_entry_t), 32, fatPart);
	

	return 1;
}

int mkdir(char *caminho){
	int barra = 0;
	int i, b;
	int tam = strlen(caminho);
	dir_entry_t newDir[32];
	memset(newDir, 0, 32*sizeof(dir_entry_t));

	FILE *fatPart = fopen("fat.part", "rb+");

	if(fatPart == NULL){
		printf("Falha ao iniciar a FAT\n");
		return 0;
	}

	for(int j = 0; j < tam; j++)
		if(caminho[j] == '/')
			barra++;

	if(barra <= 1){//diretorio root
		for(i = 0; i < 32; i++)
			if(root[i].first_block == 0)
				break;
		
		char *nome = (char*)malloc(tam*sizeof(char));
		for(int j = 1; j <= tam || j < 19; j++)
			nome[j-1] = caminho[j];

		strcpy(root[i].filename, nome);
		root[i].attributes = 1;

		for(b = 10; b < 4096; b++)
			if(fat[b] == 0x0000){
				fat[b] = 0xfffe;
				break;
			}

		root[i].first_block = b;

		fseek(fatPart, CLUSTER_SIZE, SEEK_SET);
		fwrite(fat, sizeof(uint16_t), 4096, fatPart);

		fseek(fatPart, 8*CLUSTER_SIZE, SEEK_CUR);
		fwrite(root, sizeof(dir_entry_t), 32, fatPart);

		fseek(fatPart, (b-10)*CLUSTER_SIZE, SEEK_CUR);
		fwrite(newDir, sizeof(dir_entry_t), 32, fatPart);

	}else{
		int k = 0;
		char nome[20][18];

		for(int j = 0; j < barra; j++){
			int w = 0;
			for(k = k+1; k < tam; k++){
				if(caminho[k] == '/') break;
				nome[j][w] = caminho[k];
				w++;
			}
		}
	}
	fclose(fatPart);
	return 1;
}

int ls(char *caminho){
	int barra = 0;
	int tam = strlen(caminho);

	for(int j = 0; j < strlen(caminho); j++)
		if(caminho[j] == '/')
			barra++;

	if(barra <= 1){
		printf("Root\n");
		for(int i = 0; i < 32; i++){
			if(root[i].first_block != 0)
				printf(" %s\n", root[i].filename);
		}
	}else{
		int k = 0;
		char nome[20][18];

		for(int j = 0; j < barra; j++){
			int w = 0;
			for(k = k+1; k < tam; k++){
				if(caminho[k] == '/') break;
				nome[j][w] = caminho[k];
				w++;
			}
		}
	}
	return 1;
}