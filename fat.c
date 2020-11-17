#include "fat.h"

uint16_t fat[4096];

union {
	dir_entry_t dir[CLUSTER_SIZE / sizeof(dir_entry_t)];
	uint8_t data[CLUSTER_SIZE];
} data_cluster;

int init(){
	FILE *fat = fopen("fat.part", "wb");
	return 1;
}

int load(){
	return 1;
}