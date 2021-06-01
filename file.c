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

	printf("Saving data...\n");
	fwrite(&quizlist, sizeof(struct Quizlist), 1, datafile);
	fwrite(&userlist, sizeof(struct User), max_users, datafile);
	fclose(datafile);
}

void appdata_read() {
	FILE *datafile;

	//Open the datafile
	datafile = fopen(".appdata.dat", "r");

	//Check if open
	if (datafile == NULL) {
		printf("Is this the first time you have started the quiz application?\n[Answer 'y' for yes and 'n' for no]\n");
		char com;
		scanf("%c", &com);
		clearBuf();
		if (com=='y'||com=='Y') {
			//Make empty appdata file
			datafile = fopen(".appdata.dat", "w");
			fclose(datafile);
			//Then try again
			appdata_read();
		}
		else if (com=='n'||com=='N') {
			printf("Error!\nAppdata not found!");
			exit(1);
		}
		else {
			printf("Invalid option!\nPlease try again,");
			appdata_read();
		}
	}
	else {
		fread(&quizlist, sizeof(struct Quizlist), 1, datafile);
		fread(&userlist, sizeof(struct User), max_users, datafile);
	}
}