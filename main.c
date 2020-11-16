#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	char* comando = (char*)malloc(18*sizeof(char));
	system("clear");
	printf("\n");
	printf("Sistema de arquivo/comando-> ");
	scanf("%s", comando);
	printf("%s\n", comando);
	return 0;
}