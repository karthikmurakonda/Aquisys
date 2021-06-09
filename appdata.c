#include "common.h"
#include "appdata.h"

void appdata_save(int all) {
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
	// Save common data
	fwrite(&quizlist.no_of_quizes,sizeof(int),1,datafile);
	fwrite(&quizlist.quiz, sizeof(struct Quiz), quizlist.no_of_quizes, datafile);
	for (int i = 0; i < quizlist.no_of_quizes; ++i) {
		for (int j = 0; j < quizlist.quiz[i].no_of_questions; ++j) {
			fwrite(question[i][j], sizeof(struct Question), max_alternative_q, datafile);
		}
	}
	fwrite(&no_of_currentusers,sizeof(int),1,datafile);
	fwrite(taglist,sizeof(taglist),1,datafile);
	fclose(datafile);

	//Save userdata
	if (all) {
		// Save all users data
		for (int i = 0; i < no_of_currentusers; ++i) {
			save_userdata(i);
		}
	}
	else {
		save_userdata(currentuser.ID);
	}
}

void appdata_read() {
	FILE *datafile;
	FILE *userdata;

	// Read common appdata
	// Open the datafile
	datafile = fopen(".appdata.dat", "r");

	// Check if open
	if (datafile == NULL) {
		printf("Is this the first time you have started the quiz application?\n[Answer 'y' for yes and 'n' for no]\n");
		char com;
		scanf("%c", &com);
		clearBuf();
		if (com=='y'||com=='Y') {
			//Make default appdata
		    for (int  i = 0; i < max_tags; i++) {
        		strcpy(taglist[i],"");
    		}
    	    strcpy(userlist[0].username,"student");
		    strcpy(userlist[0].password,"1");
		    userlist[0].type=0;
		    strcpy(userlist[1].username,"admin");
		    strcpy(userlist[1].password,"1");
		    userlist[1].type=1;
		    quizlist.no_of_quizes = 0;
			no_of_currentusers = 2;
		    appdata_save(1);
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
		// Read common data
		fread(&quizlist.no_of_quizes,sizeof(int),1,datafile);
		fread(&quizlist.quiz, sizeof(struct Quiz), quizlist.no_of_quizes, datafile);
		for (int i = 0; i < quizlist.no_of_quizes; ++i) {
			for (int j = 0; j < quizlist.quiz[i].no_of_questions; ++j) {
				fread(question[i][j], sizeof(struct Question), max_alternative_q, datafile);
			}
		}
		fread(&no_of_currentusers,sizeof(int),1,datafile);
		fread(taglist,sizeof(taglist),1,datafile);
		fclose(datafile);

		// Read all users data
		for (int i = 0; i < no_of_currentusers; ++i) {
			read_userdata(i);
		}
	}
}

void save_userdata(int i) {
	FILE *userdata;
	//Open userdata
	char udatafile[100];
	sprintf(udatafile, ".appdata-%d.dat", i);
	userdata = fopen(udatafile, "w");

	// Check if open
	if (userdata == NULL) {
		printf("\nError!\nCould not open userdata\n");
		exit (1);
	}
	
	fwrite(&userlist[i], sizeof(struct User), 1, userdata);
	fwrite(quizes_attempted[i], sizeof(struct Quizes_attempted), quizlist.no_of_quizes, userdata);
	if (userlist[i].type==0) {
		//If it is student save responces
		for (int j = 0; j < quizlist.no_of_quizes; ++j) {
			for (int k = 0; k < quizlist.quiz[j].no_of_questions; ++k)
			{
				fwrite(response[i][j][k], sizeof(struct Response), max_alternative_q, userdata);
			}
		}
	}
	fclose(userdata);
}

void read_userdata(int i) {
	FILE *userdata;
	//Open userdata
	char udatafile[100];
	sprintf(udatafile, ".appdata-%d.dat", i);
	userdata = fopen(udatafile, "r");

	// Check if open
	if (userdata == NULL) {
		printf("\nError!\nCould not open userdata\n");
		exit (1);
	}

	fread(&userlist[i], sizeof(struct User), 1, userdata);
	fread(quizes_attempted[i], sizeof(struct Quizes_attempted), quizlist.no_of_quizes, userdata);
	if (userlist[i].type==0) {
		//If it is student read responces
		for (int j = 0; j < quizlist.no_of_quizes; ++j) {
			for (int k = 0; k < quizlist.quiz[j].no_of_questions; ++k)
			{
				fread(response[i][j][k], sizeof(struct Response), max_alternative_q, userdata);
			}
		}
	}
	fclose(userdata);
}