#include "common.h"
#include "quiz.h"
#include "admin.h"
#include "file.h"
#include "login.h"

struct Quizlist quizlist;
struct User userlist[max_users];
struct User currentuser;

int login_status;

void clearscr(void) {
  #ifdef _WIN32
      system("cls");
  #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
      system("clear");
  #else
      #error "OS not supported."
  #endif
}

void clearBuf() {   //Cleans buffer (To be used after scanf)
  char ch;
  while(ch = getchar(), ch != '\n' && ch != EOF);
}

void smart_fgets(char *str, int n, FILE *stream) {  //Alternative to fgets to ensure buffer is clean
  fgets(str, n, stream);
  int len = strlen(str);
  while (str[0]==' ') {                             //Remove any heading whitespaces
    for (int i = 0; i < len; ++i) {
        str[i]=str[i+1];
    }
    len--;
  }
  if ((strlen(str)>1) && (str[len-1]=='\n')) {      //No input overflow
    str[strlen (str) - 1] = '\0';                   //Get rid of terminating '\n'
  }
  else if (len==n-1) {                              //Input has overflowed
    clearBuf();                                     //Clean Buffer
  }
  else if (len<=1) {
      printf("Empty input, please try again!\n");
      smart_fgets(str,n,stream);
  }
}

int scanf_int(int uplimit,int lowlimit){    //upper limit is first arg and lower limit is second arg
    int res;
    int out;
    out = scanf("%d",&res);
    clearBuf();
    if(out == 1){
        if(res <= uplimit && res >= lowlimit)    return res;  //checks whether the input is in range or not.
    }
    printf("\nNot a valid response try again (should be a number between %d and %d)\n",lowlimit,uplimit);
    scanf_int(uplimit,lowlimit);
}

void student_nav() {
  if (quizlist.no_of_quizes!=0) {
    for (int  i = 0; i < quizlist.no_of_quizes; i++) {
        printf("%d : %s\t\t Attempts-   %d/%d\n\n",i+1, quizlist.quiz[i].name, userlist[currentuser.ID].quizes_attempted[i].no_attempts, quizlist.quiz[i].no_of_max_attempts);
    }
    printf("What would you like to do?\n");
    printf("- Attempt a quiz (Enter q)\n");
    printf("- View analysis of a quiz (Enter a)\n");
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
        /* code */
    }
    else {
        printf("\nInvalid input! Please try again,\n");
        goto E;
    }
  }
  else {
    printf("Sorry no quizes have been assigned yet! Try again later,\n\nPress ENTER to exit\n");
    getchar();
    clearBuf();
  }
}