#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	char *comando = (char*)malloc(20*sizeof(char));
	char *caminho = (char*)malloc(200*sizeof(char));
	system("clear");
	while(1){
		printf("Fat-> ");
		scanf("%s %s", comando, caminho);
		if(strcmp(comando, "init") == 0)
			printf("%s %s\n", comando, caminho);

		if(strcmp(comando, "quit") == 0)
			break;
	}

	return 0;
}