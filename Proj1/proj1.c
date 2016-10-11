#include <stdio.h>
#include <stdlib.h>
#include "projOne.h"

FILE *source;
char path[200];

void main() {

	printf("Enter the path for file: ");
	gets(path);

	source = fopen(path, "r");
	while (source == NULL)
	{
		perror("FILE OPEN ERROR");
		printf("Enter the path for file: ");
		gets(path);
		source = fopen(path, "r");
	}

	createListingFile(source);

	printf("Source file finished reading. Press any key to exit.");
	getchar();

}