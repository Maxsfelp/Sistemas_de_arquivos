#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fat.h"

char *get_comando(char *entrada){
	int tam = strlen(entrada);
	char *comando = (char*)malloc(tam*sizeof(char));
	for(int i = 0; i < tam; i++){
		comando[i] = entrada[i];
		if(entrada[i] ==  ' ')
			comando[i] = '\0';
	}
	return comando;
}

char *get_caminho(char *entrada){
	int tam = strlen(entrada);
	int i;
	char *caminho = (char*)malloc(tam*sizeof(char));
	for(i = 0; i < tam; i++){
		if(entrada[i] == ' ')
			break;
	}

	for(int j = i+1; j < tam; j++)
		caminho[j-(i+1)] = entrada[j];
	
	return caminho;
}

int main(int argc, char const *argv[]){
	char *entrada = (char*)malloc(200*sizeof(char));
	char *caminho = (char*)malloc(200*sizeof(char));
	char *comando = (char*)malloc(20*sizeof(char));
	system("clear");
	while(1){
		printf("Fat-> ");
		scanf("%[^\n]s", entrada);
		setbuf(stdin, NULL);
		comando = get_comando(entrada);
		caminho = get_caminho(entrada);
		if(strcmp(comando, "init") == 0)
			init();

		if(strcmp(comando, "load") == 0)
			load();

		if(strcmp(comando, "ls") == 0)
			ls_fat(caminho);

		if(strcmp(comando, "mkdir") == 0)
			printf("ok\n");

		if(strcmp(comando, "create") == 0)
			printf("ok\n");

		if(strcmp(comando, "unlink") == 0)
			printf("ok\n");

		if(strcmp(comando, "write") == 0)
			printf("ok\n");

		if(strcmp(comando, "append") == 0)
			printf("ok\n");

		if(strcmp(comando, "read") == 0)
			printf("ok\n");

		if(strcmp(comando, "quit") == 0)
			break;
	}

	system("clear");

	return 0;
}
