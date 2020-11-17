#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* entrada de diretorio, 32 bytes cada */
typedef struct {
	uint8_t filename[18];
	uint8_t attributes;
	uint8_t reserved[7];
	uint16_t first_block;
	uint32_t size;
} dir_entry_t;

#define CLUSTER_SIZE 1024

int init();
int load();