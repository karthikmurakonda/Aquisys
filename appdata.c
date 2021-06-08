#include "common.h"

void appdata_save() {
	FILE *datafile;

	//Open the datafile
	datafile = fopen(".appdata.dat", "w");

	//Check if open
	if (datafile == NULL)
	{
		printf("\nError!\nCould not open appdata\n");
		exit (1);
	}

	printf("Saving data...\n");
	fwrite(&quizlist.no_of_quizes,sizeof(int),1,datafile);
	fwrite(&quizlist.quiz, sizeof(struct Quiz), quizlist.no_of_quizes, datafile);
	for (int i = 0; i < quizlist.no_of_quizes; ++i) {
		for (int j = 0; j < quizlist.quiz[i].no_of_questions; ++j) {
			fwrite(question[i][j], sizeof(struct Question), max_alternative_q, datafile);
		}
	}
	fwrite(&no_of_currentusers,sizeof(int),1,datafile);
	for (int i = 0; i < no_of_currentusers; ++i) {
		for (int j = 0; j < quizlist.no_of_quizes; ++j) {
			for (int k = 0; k < quizlist.quiz[j].no_of_questions; ++k)
			{
				fwrite(response[i][j][k], sizeof(struct Response), max_alternative_q, datafile);
			}
		}
	}
	fwrite(&userlist, sizeof(struct User), no_of_currentusers, datafile);
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
			//Make default appdata
		    strcpy(userlist[0].username,"student");
		    strcpy(userlist[0].password,"1");
		    userlist[0].type=0;
		    strcpy(userlist[1].username,"admin");
		    strcpy(userlist[1].password,"1");
		    userlist[1].type=1;
		    quizlist.no_of_quizes = 0;
			no_of_currentusers = 2;
		    appdata_save();
			//Then try again
			appdata_read();
		}
		else if (com=='n'||com=='N') {
			printf("Error!\nAppdata not found");
			exit(1);
		}
		else {
			printf("Invalid option!\nPlease try again,");
			appdata_read();
		}
	}
	else {
		fread(&quizlist.no_of_quizes,sizeof(int),1,datafile);
		fread(&quizlist.quiz, sizeof(struct Quiz), quizlist.no_of_quizes, datafile);
		for (int i = 0; i < quizlist.no_of_quizes; ++i) {
			for (int j = 0; j < quizlist.quiz[i].no_of_questions; ++j) {
				fread(question[i][j], sizeof(struct Question), max_alternative_q, datafile);
			}
		}
		fread(&no_of_currentusers,sizeof(int),1,datafile);
		for (int i = 0; i < no_of_currentusers; ++i) {
			for (int j = 0; j < quizlist.no_of_quizes; ++j) {
				for (int k = 0; k < quizlist.quiz[j].no_of_questions; ++k)
				{
					fread(response[i][j][k], sizeof(struct Response), max_alternative_q, datafile);
				}
			}
		}
		fread(&userlist, sizeof(struct User), no_of_currentusers, datafile);
		fclose(datafile);
	}
}
