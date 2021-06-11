#include "common.h"
#include "quiz.h"
#include "admin.h"
#include "login.h"

struct Quizlist quizlist;
struct User userlist[max_users];
struct User currentuser;
struct Question question[max_quizes][max_q_per_quiz][max_alternative_q];   //Questions and their alternatives
struct Response response[max_users][max_quizes][max_q_per_quiz][max_alternative_q];   //Responses (index should be user ID)
struct Quizes_attempted quizes_attempted[max_users][max_quizes];    //attempts related to a quiz are stored at quiz’s Id.

int login_status;
int no_of_currentusers;
char taglist[max_tags][13];
time_t start=0, current=0, last;

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

void wait_for_enter() {
  char a[1];
  smart_fgets(a, 1, stdin);
}

void  multiline_input(char *arr,int len) {      //takes multiple lines from user.user needs to press enter 2 times to end input session. len >2 always.
    int lastindex = 0;
    
    for (int index = 0; index < len; index++)
    {
       arr[index] = getchar();
       if(index == 0){
           if(arr[0]== '\n'){
               printf("Empty input try agian!\n");
               multiline_input(arr,len);
               break;
           }
       }
       if(index >0){
            if( arr[index] == '\n' && arr[index-1] =='\n'){
                arr[index] = '\0';
                break;
            }
       }
       lastindex ++;
    }
    if(lastindex == len){
        clearBuf();
        printf("No.of characters exceeded the limit try again!\n");
        multiline_input(arr,len);
    }
}
