#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	char* comando;
	system("clear");
	printf("\n");
	printf("Sistema de arquivo/comando-> ");
	scanf("%c", &comando);
	printf("%c\n", comando);
	return 0;
}