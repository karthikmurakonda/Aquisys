#include "common.h"

void student_nav() {
  if (quizlist.no_of_quizes!=0) {
    for (int  i = 0; i < quizlist.no_of_quizes; i++) {
        printf("%d : %s\t\t Attempts-   %d/%d\n\n",i+1, quizlist.quiz[i].name, userlist[currentuser.ID].quizes_attempted[i].no_attempts, quizlist.quiz[i].no_of_max_attempts);
    }
    printf("What would you like to do?\n");
    printf("- Attempt a quiz (Enter q)\n");
    printf("- View analysis of a quiz (Enter a)\n");
    printf("- Log out (Enter l)\n");
    printf("- Change password (Enter c)\n");
    char com;
    E:
    scanf("%c", &com);
    clearBuf();
    if (com=='q') {
        printf("\nPlease choose a quiz to give (enter the quiz number):\n");
        int n = scanf_int(quizlist.no_of_quizes,1)-1;
        takeQuiz(n);
        student_nav();
    }
    else if (com=='a') {
        printf("\nPlease choose a quiz to analyse (enter the quiz number):\n");
        int q = scanf_int(quizlist.no_of_quizes,1)-1;
        if (userlist[currentuser.ID].quizes_attempted[q].no_attempts!=0) {
            printf("\nWhich attempt number would you like to analyse?:\n");
            int a = scanf_int(userlist[currentuser.ID].quizes_attempted[q].no_attempts,1)-1;
            clearscr();
            aMatrix(q,a);
        }
        else {
            printf("No attempts available to analyse! Press ENTER to go back,\n");
            getchar();
            clearscr();
            student_nav();
        }
    }
    else if (com=='l') {
        loginpage();
    }
    else if (com=='c') {
        change_password();
    }
    else {
        printf("\nInvalid input! Please try again,\n");
        goto E;
    }
  }
  else {
    printf("Sorry no quizes have been assigned yet! Try again later,\n\nPress ENTER to exit\n");
    getchar();
    loginpage();
  }
}