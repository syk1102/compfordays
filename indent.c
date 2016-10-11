#include <stdio.h>

int checkindent() {
	FILE *fp;
	int lineNum;

	/*fp = fopen("listing-file.txt", "w+");
	print_with_indent(12, "hello world!");*/

	printf("%-30s %s\n", "init...", "Ok.");
	printf("%-30s %s\n", "start init", "Ok.");
	printf("%-30s %s\n", "what in the world are we doing...", "Ok.");

}

void print_with_indent(int indent, char * string)
{
	printf("%*s" "%s", indent, "", string);
}