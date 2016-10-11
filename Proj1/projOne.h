#pragma once
#ifndef PROJONE_H_
#define PROJONE_H_

struct Token {
	char token_type[10];
	int attribute;
};

void addToken(struct Token tok);
struct Token getToken(int pos);

void createListingFile(FILE*); 
int machineSupervisor(int);


	
#endif 