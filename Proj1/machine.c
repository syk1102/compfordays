#include <stdio.h>
#include <stdlib.h>
#include "projOne.h"
#define true 1
#define false 0

FILE *listingFile;
FILE *tokenFile;

char sourceString[71] = ""; // because \n is considered single char
int sourceC;
int lineNum;
int frontP;
int backP;

//struct Token token_table[100]; // not very memory efficient
//int token_table[100];
//struct Token *tpos;
//int *tpos;
int tpos = 0;
//tpos = &token_table[0];

void addToken(struct Token *token) { //taking the address of where token is stored, so passes &token
	//*tpos = *token; // value of pointer to token_table now has address to the token 
	//token_table[tpos] = *token;
	tpos++; // next pos of the array
}

struct Token getToken() {
	return token_table[tpos]; 
}

void createListingFile(FILE *source) {

	lineNum = 1;

	listingFile = fopen("listing-file.txt", "w+");
	tokenFile = fopen("token-file.txt", "w+");
	do {

		int pos = 0;
		sourceC = fgetc(source);

		while (!feof(source) && sourceC != '\n') {
			sourceString[pos] = sourceC;
			sourceC = fgetc(source);
			pos++;
		}
		if (feof(source)) {
			break;
		}

		sourceString[pos] = '\0';
		fprintf(listingFile, "%-10d %s\n", lineNum, sourceString);

		machineSupervisor(pos); // lexical analysis on the string
		lineNum++;
	} while (1);

	fprintf(listingFile, "%-10d %s\n", lineNum, "EOF");

	fclose(source);
	fclose(listingFile);
}

int machineSupervisor(int end)
{
	frontP = 0;
	backP = 0;
	
	int nthMachine;
	int lexemeNotFound; // 0 - false, 1 - true
	while (backP != end) {
		nthMachine = 0;
		lexemeNotFound = true;
		do {
			lexemeNotFound = checkForLexeme(nthMachine, end);
			if (lexemeNotFound == false) { // found a lexeme using nthMachine
				backP = frontP; // move the back pointer
			}
			else {
				frontP = backP; // reset the front pointer
			}
		} while (lexemeNotFound);
	}
	return 0;
}

int checkForLexeme(int nthMachine, int end) {
	switch (nthMachine) {
	case 0:
		return wsMachine(end);
	case 1:
		return addOpMachine(end);
	case 2:
		return wsMachine(end);
	case 3:
		return wsMachine(end);

	}
}

/* Handles white space(s) such as: space, tab, newline
returns false if it is whitespace
returns true if it is not whitespace*/
int wsMachine(int end) {
	if (sourceString[frontP] == '\n'
		|| sourceString[frontP] == '\t'
		|| sourceString[frontP] == ' ') {
		frontP += 1;
		while (frontP < end) {
			if (sourceString[frontP] == '\n'
				|| sourceString[frontP] == '\t'
				|| sourceString[frontP] == ' ') {
				frontP += 1;
			}
			else {
				return false;
			}
		}
		return false;
	}
	else {
		return true;
	}
}

/* Handles Addition operators such as: +, -, or*/
int addOpMachine(int end) {
	if (sourceString[frontP] == '+') {
		frontP += 1;
		fprintf(listingFile, "%-10d %s\n", lineNum, "EOF");
		return false;
	}
	else if (sourceString[frontP] == '-') {
		frontP += 1;
		struct Token tok;
		strcpy(tok.token_type, "PLUS");
		tok.attribute = 0;
		addToken(&tok);
		return false;
	}
	else if (sourceString[frontP] == 'o') {
		frontP += 1;
		if (sourceString[frontP] == 'r') {
			frontP += 1;
			return false; // should I check if the char after 'r' is whitespace?
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}