#include "common.h"
#include "file.h"

void appdata_save() {
	FILE *datafile;

	//Open the datafile
	datafile = fopen(".appdata.dat", "w");

	//Check if open
	if (datafile == NULL)
	{
		printf("\nError 2.1: Could not open appdata\n");
		exit (1);
	}

	fwrite(&quizlist, sizeof(struct Quizlist), 1, datafile);
	fwrite(&userlist, sizeof(struct User), max_users, datafile);
}

void appdata_read() {
	FILE *datafile;

	//Open the datafile
	datafile = fopen(".appdata.dat", "r");

	//Check if open
	if (datafile == NULL)
	{
		printf("\nError 2.1: Could not open appdata\n");
		exit (1);
	}

	fread(&quizlist, sizeof(struct Quizlist), 1, datafile);
	fread(&userlist, sizeof(struct User), max_users, datafile);
}