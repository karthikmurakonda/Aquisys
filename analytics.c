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
  for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
    if (i%5==0) {
      printf("\n");
    }
    if (i+1<10) {
      printf(" %d) [%c] (%d/%d)   ", i+1, quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].status, userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].marks[i] ,quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].marks);
    }
    else {
      printf("%d) [%c] (%d/%d)   ", i+1, quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].status, userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].marks[i], quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].marks);
    }
  }

  printf("\n\nKey:\n[U] Unattempted            (p/q) p Marks Obtained Out of q\n[C] Correct\n[W] Wrong\n");
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
  printf("Your score is %d \n",userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].result.score);
  printf("No. of correct answers are %d \n",userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].result.correct);
  printf("No. of incorrect answers are %d \n\n",userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].result.incorrect);
}

void analyseQuestion(int i, int index, int attempt) {
  printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
  printf("-------------------------------------------\n             Question %d (%d Marks)\n\n", i+1, quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].marks);
  printf("Question:\n");
  printf("%s\n\n", quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].statement);
  printf("Your answer:\n%s\n\n", quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].answer);
  printf("Score: %d/%d\n\n", userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].marks[i], quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][1]].marks);
  printf("Enter 'e' to exit or 'n' to proceed to next question\n");
  char com;
  E:
  com=getchar();
  clearBuf();
  if (com=='e') {
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
     int a=userlist[currentuser.ID].quizes_attempted[index].attempt[d].q_bank[qno][0];
     int b=userlist[currentuser.ID].quizes_attempted[index].attempt[d].q_bank[qno][0];
     printf("The question is : %s\n",quizlist.quiz[index].question[a][b].statement);
     printf("The solution is : %s\n",quizlist.quiz[index].question[a][b].solution);
     printf("Your answer  is : %s\n",quizlist.quiz[index].question[a][b].response[currentuser.ID].answer);
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