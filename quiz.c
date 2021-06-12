#include "common.h"
#include "quiz.h"

/*int main() {
	init(0);
	takeQuiz(0);
	return 0;
}*/

void init(int index) {
	char a[4], b[2];
	currentuser.ID=0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < max_alternative_q; ++j) {
			sprintf(a, "%d+", i);
			sprintf(b, "%d", j);
			strcpy(question[index][i][j].statement, strcat(a,b));
			response[currentuser.ID][index][i][j].status=78;
			question[index][i][j].marks=2;
		}
	}
	strcpy(quizlist.quiz[index].name, "Test Quiz-1");
	quizlist.quiz[index].no_of_questions=10;
	quizlist.quiz[index].no_of_max_attempts=1;
} 

void takeQuiz(int index) {
	clearscr();
	//If reattempt is possible
	if (quizes_attempted[currentuser.ID][index].no_attempts<quizlist.quiz[index].no_of_max_attempts) {
		//Set next attempt number
		int attempt=quizes_attempted[currentuser.ID][index].no_attempts;
		//Make quiz
		makeQuiz(index, attempt);
		//Go to quiz matrix
		// record start
		record_time(0);
		qMatrix(index, attempt);
		//Update attempt data
		quizlist.quiz[index].no_of_students_attempted++;
		quizes_attempted[currentuser.ID][index].no_attempts++;
		//Autograde this attempt
		autoGradeAttempt(index, attempt);
		clearscr();
	}
	//If reattempt not possible
	else {
		printf("No more reattempts are allowed!\n\n");
	}
}

void qMatrix(int index, int attempt) {
	printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
	printf("-------------------------------------------\n               Question Matrix             \n\n");
	char color[8];
	for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
		char status=response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status;
		if (status=='U') {
			strcpy(color,yellow);
		}
		else if (status=='S') {
			strcpy(color,cyan);
		}
		else if (status=='A') {
			strcpy(color,green);
		}
		if (i%5==0) {
			printf("\n");
		}
		if (i+1<10) {
			printf(" %d) %s[%c]%s (%d)   ", i+1, color, status, normal, question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks);
		}
		else {
			printf("%d) %s[%c]%s (%d)   ", i+1, color, status, normal, question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks);
		}
	}
	printf("\n\nKey:\n%s[U]%s Unattempted            (p/q) p Marks Obtained Out of q\n", yellow, normal);
	printf("%s[S]%s Seen\n", cyan, normal);
	printf("%s[A]%s Attempted\n", green, normal);
	printf("\n\nEnter question number you wish to view or '0' to submit quiz,\n");
	int num;
	scanf("%d", &num);

	clearBuf();
	if (num==0) {
		printf("\nAre you sure you want to submit the quiz?\nAnswer 'y' for yes and 'n' for no,\n");
		char com;
		scanf("%c", &com);
		clearBuf();
		if (com==110) {                 //If 'n'
			clearscr();
		qMatrix(index, attempt);
	}
		else if (com==121) {            //If 'y'
		//record submit quiz time
		quizes_attempted[currentuser.ID][index].attempt[attempt].time_taken =(current-start);
		clearscr();
		printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
		printf("-------------------------------------------\n");
		printf("Quiz submitted!\nHit ENTER to proceed to main menu,\n");
		wait_for_enter();
	}
		else {            //If not 'n' or y'
			clearscr();
		printf("Invalid Input!\n");
		qMatrix(index, attempt);
	}
}
else if (num>0&&num<=quizlist.quiz[index].no_of_questions) {
	clearscr();
	askQuestion(num-1, index, attempt);
}
else {
	clearscr();
	printf("Invalid Input!\n");
	qMatrix(index, attempt);
}
}

void askQuestion(int i, int index, int attempt) {
	printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
	printf("-------------------------------------------\n             Question %d (%d Marks)\n\n", i+1, question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks);
	printf("Question:\n");
	printf("%s\n\n", question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].statement);
	//Has the question been answered already?
	if (response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status=='A') {
		printf("Your current answer:\n%s\n\n", response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].answer);
		printf("Change the answer (enter # to exit without changing answer):\n");
	}
	else {
		printf("Enter the answer (enter # to exit without answering):\n");
			//Set status to seen
		response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status='S';
	}
	char answer[max_answer_length];
	//Capture answer
	smart_fgets(answer, max_answer_length, stdin);
	// submit time of question
	record_time(1);
	// Check for time discrepancies
	if (cheating()) {
		quizes_attempted[currentuser.ID][index].attempt[attempt].time_taken =(current-start);
		clearscr();
		printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
		printf("-------------------------------------------\n");
		printf("Cheating has been detected!!\nThis answer could not be saved!\n");
		printf("Quiz submitted!\nHit ENTER to proceed to main menu,\n");
		wait_for_enter();
	}
	else {
		//time checker
		if (autosubmit(index)) {
			// Timeout!
			//record submit quiz time
			quizes_attempted[currentuser.ID][index].attempt[attempt].time_taken =(current-start);
			clearscr();
			printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
			printf("-------------------------------------------\n");
			printf("Time out!!\nThis answer could not be saved!\n");
			printf("Quiz submitted!\nHit ENTER to proceed to main menu,\n");
			wait_for_enter();
		}
		else {
			//If # is not the answer
			if (answer[0]!='#') {
				//Update response
				strcpy(response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].answer, answer);
				//Mark as attempted
				response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status='A';
				appdata_save(0);
			}
			clearscr();
			quizNav(i, index, attempt);
		}
	}
}

void quizNav(int i, int index, int attempt) {
	printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
	printf("-------------------------------------------\n");
	char com;
	printf("Would you like to proceed to next question or return to question matrix?\n\nEnter:\n'n' for next question\n'm' for question matrix\n");
	scanf("%c", &com);
	clearBuf();
	if (com==110) {     //'n'
		clearscr();
		if (i+1<quizlist.quiz[index].no_of_questions) {   //next question index is less than equal last question index
			askQuestion(++i, index, attempt);
		}
		else {                                            //If not go to first question
			askQuestion(0, index, attempt);
		}
	}
	else if (com==109) {  //'m'
		clearscr();
	qMatrix(index, attempt);
}
	else {    //neither 'n' nor 'm'
		clearscr();
	printf("Invalid Option!\n");
	quizNav(i, index, attempt);
}
}

int randNum(int lower, int upper) {
	return ((rand()%(upper - lower + 1)) + lower);
}

void makeQuiz(int index, int attempt) {
	int rand;
	if (quizes_attempted[currentuser.ID][index].no_attempts<quizlist.quiz[index].no_of_max_attempts) {
		int q_status[quizlist.quiz[index].no_of_questions];
		for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
			quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]=-1;
			quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]=-1;
			q_status[i]=0;
		}
		//Randomise Question Order
		for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
			//Check random questions until unassigned one is found
			while(quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]==-1) {
				rand=randNum(0,quizlist.quiz[index].no_of_questions-1);
				//If not assigned
				if (q_status[rand]==0) {
					//Assign
					quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]=rand;
					q_status[rand]=1;
				}
			}
		}
		//Go through randomly chosen question order
		for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
			//Run until the alternative is set
			while(quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]==-1) {
				//Generate random alternative number
				rand=randNum(0,max_alternative_q-1);
				//See if this alternative has 'N' status
				if (response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][rand].status=='N') {
					//Set the alternative
					quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]=rand;
					//Set status of this alternative to 'U'
					response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][rand].status='U';
				}
			}
		}
	}
}

void autoGradeAttempt(int index, int attempt) {
	for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {  //Grade individual questions
		//If status is attempted
		if (response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status=='A') {
			//Check if correct
			if (!strcmp(response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].answer, question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].solution)) {
				//Give full marks
				quizes_attempted[currentuser.ID][index].attempt[attempt].marks[i] = question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks;
				//Update result for this attempt
				response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status='C';
				quizes_attempted[currentuser.ID][index].attempt[attempt].result.attempted++;
				quizes_attempted[currentuser.ID][index].attempt[attempt].result.correct++;
				quizes_attempted[currentuser.ID][index].attempt[attempt].result.score += quizes_attempted[currentuser.ID][index].attempt[attempt].marks[i];
			}
			//Otherwise it must be wrong
			else {
				//Give zero marks
				quizes_attempted[currentuser.ID][index].attempt[attempt].marks[i] = 0;
				//Update result for this attempt
				response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status='W';
				quizes_attempted[currentuser.ID][index].attempt[attempt].result.attempted++;
				quizes_attempted[currentuser.ID][index].attempt[attempt].result.incorrect++;
			}
		}
	}
}

void view_instructions(int index) {
	printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
	printf("-------------------------------------------\n\n");
	printf("%s\n\n", quizlist.quiz[index].instructions);
	printf("Attempts: %d/%d\n", quizes_attempted[currentuser.ID][index].no_attempts, quizlist.quiz[index].no_of_max_attempts);
	if (quizlist.quiz[index].visible<=1) {
		printf("\nThis cannot be given currently!\n");
	}
	printf("\nWhat would you like to do?\n");
	if (quizlist.quiz[index].visible>1) {
		printf("- Start the quiz (Enter q)\n");
	}
	printf("- Exit (Enter e)\n");
	char com;
	E:
	scanf("%c",&com);
	clearBuf();
	if (com=='q' && quizlist.quiz[index].visible>1) {
		takeQuiz(index);
	}
	else if (com=='e') {
		return;
	}
	else {
		printf("Invalid option please try again,\n");
		goto E;
	}
}