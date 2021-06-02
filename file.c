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
	fwrite(&quizlist.no_of_quizes,sizeof(int),1,datafile);
	
	fwrite(&quizlist.quiz, sizeof(struct Quiz), quizlist.no_of_quizes, datafile);

	fwrite(&userlist, sizeof(struct User), max_users, datafile);
	fclose(datafile);
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
	fread(&quizlist.no_of_quizes,sizeof(int),1,datafile);
	fread(&quizlist.quiz, sizeof(struct Quiz), quizlist.no_of_quizes, datafile);
	fread(&userlist, sizeof(struct User), max_users, datafile);
	fclose(datafile);
}