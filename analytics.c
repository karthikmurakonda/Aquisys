#include "common.h"
#include "analytics.h"

/*int main() {
	appdata_read();
  declare_result(0,0);
	//fetch_result(0, 0);
	return 0;
}*/

void aMatrix(int index, int attempt) {
  printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
  printf("-------------------------------------------\n               Analysis Matrix             \n\n");
  quiz_result(index, attempt);
  char color[8];
  for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
    char status=response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].status;
    if (status=='U') {
      strcpy(color,yellow);
    }
    else if (status=='S') {
      strcpy(color,cyan);
    }
    else if (status=='C') {
      strcpy(color,green);
    }
    else if (status=='W') {
      strcpy(color,red);
    }
    if (i%5==0) {
      printf("\n");
    }
    if (i+1<10) {
      printf(" %d) %s[%c]%s (%d/%d)   ", i+1, color, status, normal, quizes_attempted[currentuser.ID][index].attempt[attempt].marks[i] ,question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks);
    }
    else {
      printf("%d) %s[%c]%s (%d/%d)   ", i+1, color, status, normal, quizes_attempted[currentuser.ID][index].attempt[attempt].marks[i], question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks);
    }
  }

  printf("\n\nKey:\n%s[U]%s Unattempted            (p/q) p Marks Obtained Out of q\n", yellow, normal);
  printf("%s[S]%s Seen\n", cyan, normal);
  printf("%s[C]%s Correct\n", green, normal);
  printf("%s[W]%s Wrong\n", red, normal);
  printf("\n\nEnter question number you wish to analyse or '0' to exit analytics,\n");
  int num;
  scanf("%d", &num);
  clearBuf();
  if (num==0) {
    clearscr();
    student_nav();
  }
  else if (num>0&&num<=quizlist.quiz[index].no_of_questions) {
    clearscr();
    analyseQuestion(num-1, index, attempt);
  }
  else {
    clearscr();
    printf("Invalid Input!\n");
    aMatrix(index, attempt);
  }
}

void quiz_result(int index, int attempt) {
  printf("The results are: \n");
  printf("Your score is %d \n",quizes_attempted[currentuser.ID][index].attempt[attempt].result.score);
  printf("No. of correct answers are %d \n",quizes_attempted[currentuser.ID][index].attempt[attempt].result.correct);
  printf("No. of incorrect answers are %d \n\n",quizes_attempted[currentuser.ID][index].attempt[attempt].result.incorrect);
}

void analyseQuestion(int i, int index, int attempt) {
  printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
  printf("-------------------------------------------\n             Question %d (%d Marks)\n\n", i+1, question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks);
  printf("Question:\n");
  printf("%s\n\n", question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].statement);
  printf("Your answer:\n%s\n\n", response[currentuser.ID][index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].answer);
  printf("Correct answer:\n%s\n\n", question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].solution);
  printf("Score: %d/%d\n\n", quizes_attempted[currentuser.ID][index].attempt[attempt].marks[i], question[index][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][0]][quizes_attempted[currentuser.ID][index].attempt[attempt].q_bank[i][1]].marks);
  printf("Time taken : %d:%d\n",quizes_attempted[currentuser.ID][index].attempt[attempt].time_taken/60,quizes_attempted[currentuser.ID][index].attempt[attempt].time_taken%60);
  printf("Enter 'e' to exit or 'n' to proceed to next question\n");
  char com;
  E:
  com=getchar();
  clearBuf();
  if (com=='e') {
    clearscr();
    aMatrix(index, attempt);
  }
  else if (com=='n') {
    clearscr();
    if (i+1<quizlist.quiz[index].no_of_questions) {   //next question index is less than equal last question index
      analyseQuestion(++i, index, attempt);
    }
    else {                                            //If not go to first question
      analyseQuestion(0, index, attempt);
    }
  }
  else {
    printf("Invalid option! Please try again,\n");
    goto E;
  }
}

/*void fetch_result(int index, int attempt)
{ 
  int qno,d;
  printf("Which attempt? \n");
  scanf("%d",&d);
  declare_result(index,d);
  while (index!=-1)
  { 
     printf("Enter the question number: \n");
     scanf("%d",&qno);
     int a=quizes_attempted[currentuser.ID][index].attempt[d].q_bank[qno][0];
     int b=quizes_attempted[currentuser.ID][index].attempt[d].q_bank[qno][0];
     printf("The question is : %s\n",question[index][a][b].statement);
     printf("The solution is : %s\n",question[index][a][b].solution);
     printf("Your answer  is : %s\n",question[index][a][b].response[currentuser.ID].answer);
     int choice;
    printf("Do you want to select another Quiz or Continue? \n");
    printf("press 0 [Quiz] or 1 [Continue] \n");
    scanf("%d",&choice);
    if (choice==0)
    { 
      fetch_result(0, 0);
      break;
    }
    else if(choice==1)
    {
      continue;
    }
  }
}*/
