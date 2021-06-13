#include "common.h"
#include "appdata.h"

void appdata_save(int all) {
	// Save quiz data if admin
	if (currentuser.type==1 || all) {
		save_quizdata();
	}

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
	printf("%sSomeone is writting to the appdata!%s\nIf this error persists try deleting all appdata lock files and restart Aquisys.\n", red, normal);
	while(checklock(0,0));
	clearscr();
	// Open the datafile
	datafile = fopen(".appdata.dat", "rb");

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
    	    strcpy(userlist[0].username,"admin");
		    strcpy(userlist[0].password,"1");
		    userlist[0].type=1;
		    strcpy(userlist[1].username,"student");
		    strcpy(userlist[1].password,"1");
		    userlist[1].type=0;
		    quizlist.no_of_quizes = 0;
			no_of_currentusers = 2;
		    appdata_save(1);
		    clearscr();
			//Then try again
			appdata_read();
		}
		else if (com=='n'||com=='N') {
			printf("%sError!\nAppdata not found\n%sIf this error persists try deleting all appdata files and restart Aquisys.\n", red, normal);
			exit(1);
		}
		else {
			printf("%sInvalid option!\nPlease try again,%s", red, normal);
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
	printf("%sSomeone is writting to the appdata!%s\nIf this error persists try deleting all appdata lock files and restart Aquisys.\n", red, normal);
	while (checklock(1,i));
	clearscr();
	lock(1,i);
	userdata = fopen(udatafile, "wb");

	// Check if open
	if (userdata == NULL) {
		printf("\n%sError!\nCould not open userdata%s\nIf this error persists try deleting all appdata files and restart Aquisys.\n", red, normal);
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
	unlock(1,i);
}

void read_userdata(int i) {
	FILE *userdata;
	//Open userdata
	char udatafile[100];
	sprintf(udatafile, ".appdata-%d.dat", i);
	printf("%sSomeone is writting to the appdata!%s\nIf this error persists try deleting all appdata lock files and restart Aquisys.\n", red, normal);
	while(checklock(1,i));
	clearscr();
	userdata = fopen(udatafile, "rb");

	// Check if open
	if (userdata == NULL) {
		printf("\n%sError!\nCould not open userdata%s\nIf this error persists try deleting all appdata files and restart Aquisys.\n", red, normal);
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

int checklock(int type, int i) {
	// Check if type is common data
	if (type==0) {
		FILE *lock;
		// Check for lock
		lock = fopen(".appdata.dat.lock", "rb");
		if (lock == NULL) {
			return 0;
		}
		else {
			fclose(lock);
			return 1;
		}
	}
	// Check if type is student
	if (type==1) {
		FILE *lock;
		// Check for lock
		char udatafilelock[100];
		sprintf(udatafilelock, ".appdata-%d.dat.lock", i);
		lock = fopen(udatafilelock, "rb");
		if (lock == NULL) {
			return 0;
		}
		else {
			fclose(lock);
			return 1;
		}
	}
}

void lock(int type, int i) {
	// Check if type is common data
	if (type==0) {
		FILE *lock;
		// Make lock
		lock=fopen(".appdata.dat.lock", "wb");
		fclose(lock);
	}
	// Check if type is student
	if (type==1) {
		FILE *lock;
		// Make lock
		char udatafilelock[100];
		sprintf(udatafilelock, ".appdata-%d.dat.lock", i);
		lock=fopen(udatafilelock, "wb");
		fclose(lock);
	}
}

void unlock(int type, int i) {
	// Check if type is common data
	if (type==0) {
		// Delete lock
		remove(".appdata.dat.lock");
	}
	// Check if type is student
	if (type==1) {
		// Delete lock
		char udatafilelock[100];
		sprintf(udatafilelock, ".appdata-%d.dat.lock", i);
		remove(udatafilelock);
	}
}

void save_quizdata() {
	FILE *datafile;

	printf("%sSomeone is writting to the appdata!%s\nIf this error persists try deleting all appdata lock files and restart Aquisys.\n", red, normal);
	while(checklock(0,0));
	clearscr();
	lock(0,0);

	//Open the datafile
	datafile = fopen(".appdata.dat", "wb");

	//Check if open
	if (datafile == NULL)
	{
		printf("\n%sError!\nCould not open appdata%s\nIf this error persists try deleting all appdata files and restart Aquisys.\n", red, normal);
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
	unlock(0,0);
}
