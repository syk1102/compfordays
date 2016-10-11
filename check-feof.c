#include <stdio.h>

int checkfeof() 
{
	FILE *fp;
	int c;

	fp = fopen("file.txt", "r");
	if(fp == NULL) {
		perror("Error in opening file");
		return(-1);
	}
	//do {
	//	c = fgetc(fp);
	//	if (feof(fp)) {
	//		break;
	//	}
	//	printf("%c", c);
	//} while (1);

	while (!feof(fp)) {
		c = fgetc(fp);
		
		printf("%c", c);
	}

	fclose(fp);
	return(0);
}