//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Common Header ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_users 10
#define max_quizes 10
#define max_answer_length 1000
#define max_alternative_q 5
#define max_q_per_quiz 200

struct Result {
    int attempted;
    int correct;
    int incorrect;
    int score;
};

struct Attempt {
    int q_bank[max_q_per_quiz][2];    //Stores randomised q_bank for this attempt, first index is Q. No. other is Q alternative
    int marks[max_q_per_quiz];        //Stores marks obtained for each answer (As per q_bank)
    struct Result result;
};                                //quiz id is index of that quiz in quiz array.

struct Quizes_attempted {
    int no_attempts;              //current no. of attempts of this quiz by user (1 to 5)
    struct Attempt attempt[5];    //attribute is attempt no. (0 to 4)
};

struct  User {
    char username[100];
    char password[100];
    int ID;                                           // Unique ID of each user
    int type;                                         // 0 (student) or 1 (admin)
    struct Quizes_attempted quizes_attempted[max_quizes];    //attempts related to a quiz are stored at quiz’s Id.   
}; 

struct Response {
   char answer[max_answer_length];  //Answer given by user
   char status;                     //initialize it to ‘N’ when creating a quiz.
};                                  //'N' for new 'U' for unattempted 'S' for seen and 'A' for attempted

struct Question {
   char statement[2000];
   char solution[max_answer_length];      //Correct answer given by teacher
   struct Response response[max_users];   //Responses (index should be user ID)
   int marks;
};

struct Quiz {
    char name[100];
    int no_of_questions;
    int no_of_students_attempted;                       //Number of students attempted in total
    struct Question question[max_q_per_quiz][max_alternative_q];   //Questions and their alternatives
    int no_of_max_attempts;
    int attempt_list[max_users];                        //Stores number of times users have attempted the quiz (index is corresponding user ID)
};        /*nst to quizlist*/

struct Quizlist {
   int no_of_quizes;            //current available no.of quizzes
   struct Quiz quiz[max_quizes] ;      //all 1000 elements are initialised but “no_of_quizes” decides what to call
};                              /*store quiz*/

struct Quizlist quizlist;
struct User userlist[max_users];
struct User currentuser;

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
  char ch;
  fgets(str, n, stream);
  int len = strlen(str);
  if ((strlen(str)>0) && (str[len-1]=='\n')) {      //No input overflow
    str[strlen (str) - 1] = '\0';                   //Get rid of terminating '\n'
  }
  else if (len==n-1) {                              //Input has overflowed
    clearBuf();                                     //Clean Buffer
  }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Admin~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ques_initialize(int questart_id,int quiz_id);
void preveiw_quiz(int quiz_Id);
void addquiz();
void change_marks(int quiz_id);
void response_admin(int quiz_id);
void showqlist_admin();
void welcomepage_admin();
void add_extra_questions();
void edit_questions(int quiz_id);
void preveiw_quiz(int quiz_Id);
void addquestions_initial(int questart_id,int quiz_id);
void add_question(int quiz_id,int qustion_no,int alt);
void preview_question(int quiz_id,int ques_id);
void admin_quizdetails(int n);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Quiz ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void init(int index);

void qMatrix(int index, int attempt);
void askQuestion(int i, int index, int attempt);
void quizNav(int i, int index, int attempt);
void makeQuiz(int index, int attempt);
void takeQuiz(int index);
void autoGradeAttempt(int index, int attempt);
int randNum(int upper, int lower);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Admin_functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void preview_question(int quiz_id,int ques_id){
    int alts= 0;
    for (int alt = 0; alt < max_alternative_q; alt++){
            if(quizlist.quiz[quiz_id].question[ques_id][alt].response[0].status == 'N') {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",ques_id+1,alt+1);
                printf("Marks - %d\n\n",quizlist.quiz[quiz_id].question[ques_id][alt].marks);
                printf("Statement:\n%s\n",quizlist.quiz[quiz_id].question[ques_id][alt].statement);
                printf("Solution:\n%s\n",quizlist.quiz[quiz_id].question[ques_id][alt].solution);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                alts++;
            }
    }
    printf("\n Type corresponding alt number to edit\notherwise type 0 to add alt questions\n Type -1 to go back to questions page\n");
    int res;
	do {
	scanf("%d",&res);
	clearBuf();
  	if(res==0){
            if(alts != 5){
            add_question(quiz_id,ques_id,alts);
            }
            else if (alts == 5){
                printf("Can't add alt anymore all 5 alts exists");
            }
            preview_question(quiz_id,ques_id);
        }
	else if(res > 0 && res <= alts){
        add_question(quiz_id,ques_id,res-1);
        preview_question(quiz_id,ques_id);
	}
    else if (res == -1) {
        edit_questions(quiz_id);
    }
    else printf("Not a valid response try agian\n");
	}while(res < 0 && res >alts);
}

void preveiw_quiz(int quiz_Id){
    clearscr();
    printf("Quiz-%s\n\n",quizlist.quiz[quiz_Id].name);
    printf("~~~QUESTION_NO~~~~~~~~~~~~~~~NO.OF_ALTS~~~~~~~~~~~~~~~Marks\n");
    for (int qid = 0; qid <quizlist.quiz[quiz_Id].no_of_questions; qid++){
        int no_of_alts= 0;
        for (int i = 0; i < max_alternative_q; i++){
            if(quizlist.quiz[quiz_Id].question[qid][i].response[0].status == 'N') no_of_alts++;
        }        
        printf("     %d                           %d                   %d\n",qid+1,no_of_alts,quizlist.quiz[quiz_Id].question[qid][0].marks);    
    }
}

void add_question(int quiz_id,int question_id,int alt_id){
    clearscr();
        int resp;
	    while(quizlist.quiz[quiz_id].question[question_id][0].marks == 0) {
        printf("Marks of %d question?\n",question_id+1);
        scanf("%d",&resp);
        clearBuf();
  	    if(resp >0){
            quizlist.quiz[quiz_id].question[question_id][0].marks = resp;
        }
        else printf("Not a valid response try agian\n");
        }
        for (int ip = 0; ip < max_alternative_q; ip++){
            quizlist.quiz[quiz_id].question[question_id][ip].marks=quizlist.quiz[quiz_id].question[question_id][0].marks;
        }
        
	
    char check='n';
    while(check != 'y'){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",question_id+1,alt_id+1);
        printf("type statment of %d-alternate for %d question(%d marks)\n\n",alt_id+1,question_id+1,quizlist.quiz[quiz_id].question[question_id][0].marks);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        smart_fgets(quizlist.quiz[quiz_id].question[question_id][alt_id].statement,2000,stdin);
        printf("\nType Solution:\n");
        smart_fgets(quizlist.quiz[quiz_id].question[question_id][alt_id].solution,1000,stdin);
        printf("\npreview:\n\n%s\n\n",quizlist.quiz[quiz_id].question[question_id][alt_id].statement);
        printf("Solution:\n");
        printf("%s\n\n",quizlist.quiz[quiz_id].question[question_id][alt_id].solution);
        printf("continue(y/n)? or rewrite this question?\n");
        char res;
        do {
            scanf("%c",&res);
            clearBuf();
            if(res=='y'||res=='Y'){
                check = 'y';
            }
            else if(res == 'n' || res == 'N') continue;
            else printf("Not a valid response try agian\n");
        }while(res != 'y'&& res != 'Y' && res!= 'n'&&res!='N');
    }
    for(int user = 0; user<max_users;user++)    quizlist.quiz[quiz_id].question[question_id][alt_id].response[user].status = 'N';   //changing status from E to N if question is filled.
}

void edit_questions(int quiz_id){
    preveiw_quiz(quiz_id);
    printf("Type ques_number to preview,edit or add alternate question numbers\nType 0 to create questions\nType -1 to exit\n");
    int res;
	do {
	scanf("%d",&res);
	clearBuf();
  	if(res== -1){
          admin_quizdetails(quiz_id);
    }
	else if(res >0 && res <= quizlist.quiz[quiz_id].no_of_questions){
        preview_question(quiz_id,res-1);
	}
    else if(res == 0){  //adding questions.
        printf("Type no.of question to added extra(you can add %d maximum)\n",200-quizlist.quiz[quiz_id].no_of_questions);
        int res2=0;
	    do {
	        scanf("%d",&res2);
	            clearBuf();
  	        if(res2 == 0){
            continue;
        }
	        else if(res2 > 0){
                if (res2 <= 200-quizlist.quiz[quiz_id].no_of_questions){
                quizlist.quiz[quiz_id].no_of_questions += res2;
                ques_initialize(quizlist.quiz[quiz_id].no_of_questions-res2,quiz_id);
                addquestions_initial(quizlist.quiz[quiz_id].no_of_questions-res2,quiz_id);
                return;
                }
                else{
                     printf("too many questions");
                     res2 = -1;
                }
	    }
            else printf("Not a valid response try agian\n");
	    }while(res2< 0);
    }
    else printf("Not a valid response try agian\n");
	}while(res <-1 || res> quizlist.quiz[quiz_id].no_of_questions);


}

void ques_initialize(int questart_id,int quiz_id){
    for (int i = questart_id; i <= quizlist.quiz[quiz_id].no_of_questions; i++){
        for(int d=0;d <5;d++){
            quizlist.quiz[quiz_id].question[i][d].statement[0] = '\0';
            quizlist.quiz[quiz_id].question[i][d].solution[0] = '\0';
            quizlist.quiz[quiz_id].question[i][d].marks = 0;
            for(int uid = 0;uid < max_users;uid++){
                quizlist.quiz[quiz_id].question[i][d].response[uid].status = 'E';
                quizlist.quiz[quiz_id].question[i][d].response[uid].answer[0] = '\0';
                userlist[uid].quizes_attempted[quiz_id].attempt[d].result.attempted = 0;
                userlist[uid].quizes_attempted[quiz_id].attempt[d].result.correct = 0;
                userlist[uid].quizes_attempted[quiz_id].attempt[d].result.incorrect=0;
                userlist[uid].quizes_attempted[quiz_id].attempt[d].result.score= 0;
            }

        }
    }
}

void addquestions_initial(int questart_id,int quiz_id){
    preveiw_quiz(quiz_id);
    printf("press ENTER to start entering questions\n");
    clearBuf();
    for (int i = questart_id; i < quizlist.quiz[quiz_id].no_of_questions; i++){
        clearscr();
        printf("%s\n",quizlist.quiz[quiz_id].name);
        for (int alt = 0; alt <quizlist.quiz[quiz_id].no_of_max_attempts ; alt++){
            add_question(quiz_id,i,alt);                  
        }

        int diff = max_alternative_q - quizlist.quiz[quiz_id].no_of_max_attempts;
        char res2 = 'y';
        while(diff > 0 && res2 != 'n'){
            printf("You can still add(optional) %d no.of alternate questions would like to continue?(y/n)",diff);
 
            do {
	        scanf("%c",&res2);
	        clearBuf();
            if(res2 == 'y' || res2 == 'Y'){
                add_question(quiz_id,i,5-diff);
                diff--;
            }
            else if ( res2 == 'n'||res2 =='N'){
                diff == 0;
                res2 = 'n';
            }
            else printf("not a valid input\n");

	    }while(res2 != 'y'&& res2 != 'Y'  && res2!= 'n'&&res2!='N');
        }   
    }
    edit_questions(quiz_id);

}

void addquiz(){
	quizlist.no_of_quizes = quizlist.no_of_quizes+1;//increasing no.of quizes.
  	int i = quizlist.no_of_quizes - 1;//i is index for quiz array.
	printf("Quiz name?\n");//taking quiz name.
	char x[101];
	smart_fgets(x,101,stdin);
	strcpy(quizlist.quiz[i].name,x);
	quizlist.quiz[i].no_of_students_attempted=0;//initialising to zero.
	//no.of questions.
	printf("no.of questions?(type number between 1 to 200)\n");
	int res;
	scanf("%d",&res);
	clearBuf();
	while(res <= 0 || res >= 200){
		printf("invalid response type again(should be a number in range 1 to 200)\n");
		scanf("%d",&res);
		clearBuf();
	}
	quizlist.quiz[i].no_of_questions = res;
	//no_of_max_attempts part.
	printf("no.of maximum attepts?(type number between 1 to 5)\n");
	scanf("%d",&res);
	clearBuf();
	while(res <= 0 || res >= 6){
		printf("invalid response type again(should be a number in range 1 to 5)\n");
		scanf("%d",&res);
		clearBuf();
	}
	quizlist.quiz[i].no_of_max_attempts = res;
	//conformation.
	printf("you have to add atleast %d questions\nWould you like to continue?(y/n)\n",quizlist.quiz[i].no_of_max_attempts*quizlist.quiz[i].no_of_questions);
	char res2;
	do {
	scanf("%c",&res2);
	clearBuf();
  	if(res2=='y'||res2=='Y'){
        ques_initialize(0,quizlist.no_of_quizes-1);
	  	addquestions_initial(0,i);
    }
	else if(res2=='n'||res2=='N'){
		quizlist.no_of_quizes = quizlist.no_of_quizes-1;
		showqlist_admin();
	}
    else printf("Not a valid response try agian\n");
	}while(res2 != 'n' && res2 != 'y' && res2!= 'N' && res2!='Y');
}

void response_admin(int quiz_id){
    clearscr();
    if (quizlist.quiz[quiz_id].no_of_students_attempted != 0){
    printf("ID~~~~~~~~~~~~User name~~~~~~~~~~attempt_number~~~~~~~~~~~~score\n");
    for (int i = 0; i < max_users; i++){
        for (int atm = 0; atm < userlist[i].quizes_attempted[quiz_id].no_attempts; atm++){
            printf("%d               %s            %d                %d",userlist[i].ID,userlist[i].username,atm+1,userlist[i].quizes_attempted[quiz_id].attempt[atm].result.score);
        }
        
    }
    
    int res;
	do {
	scanf("%d",&res);
	clearBuf();
  	if(res >= 0 && res <max_users*max_alternative_q){
          //abhishek's function
    }
    else printf("Not a valid response try agian\n");
	}while(res < 0 || res >= max_users*max_alternative_q);
    }
    else {
        printf("no one attempted the quiz");
        admin_quizdetails(quiz_id);
    }

}

 void change_marks(int quiz_id){
    printf("Type the question number to change marks of that question\nType 0 to goback\n");
    int res;
int check = 0;
	do {
	scanf("%d",&res);
	clearBuf();
  	if(res == 0  ){
         admin_quizdetails(quiz_id);
         check =1;
    }
	else if(res <= quizlist.quiz[quiz_id].no_of_questions && res >0){
        printf("type new marks for question %d(previously %d marks)\n",res,quizlist.quiz[quiz_id].question[res-1][0].marks);
        int res2;
        check = 1;
        int check2 = 0;
	    do {
	        scanf("%d",&res2);
	        clearBuf();
  	        if(res2 >0 ){
                for(int i = 0;i <max_alternative_q;i++) quizlist.quiz[quiz_id].question[res-1][i].marks = res2; 
            check2 = 1;
            admin_quizdetails(quiz_id);
            }
            else printf("Not a valid response try agian\n");
	    }while(check2 == 0);
	}
    else printf("Not a valid response try agian\n");
	}while(check == 0);
 }

void admin_quizdetails(int n){
    clearscr();
    printf("Quiz name : %s\n",quizlist.quiz[n].name);
    printf("No.of questions %d\n",quizlist.quiz[n].no_of_questions);
    printf("No.of maximum attempts : %d\n",quizlist.quiz[n].no_of_max_attempts);
    printf("Type\n r : to view student responses\n m : To change distrubution of marks\n e : To add questions/edit existing questions \n 0 : to go back to quizzes list\n");
    char res;
    int dm = 0;
	do {
	scanf("%c",&res);
	clearBuf();
  	if(res=='r'){
        response_admin(n);
        dm = 1;
    }
	else if(res == 'e'){
        edit_questions(n);
        dm = 1;
	}
    else if(res == 'm'){
        preveiw_quiz(n);
        change_marks(n);
        dm = 1;
    }
    else if(res == '0'){
        showqlist_admin();
        dm = 1;
    }
    else printf("Not a valid response try agian\n");
	}while(dm != 1);
}

void showqlist_admin() {
    clearscr();
    printf("type a number to veiw/edit quiz or type '0' to create a quiz\npress '-1' to go back to welcome page\n" );
    for (int  i = 0; i < quizlist.no_of_quizes; i++)   printf("%d : %s\t no.of students attempted   %d\n",i+1,quizlist.quiz[i].name,quizlist.quiz[i].no_of_students_attempted);
    printf("0 : Create a quiz\n");
    int res;
    do {
	scanf("%d",&res);
	clearBuf();
  	if(res==0){
          addquiz();
    }
	else if(res>0 && res <= quizlist.no_of_quizes){
        admin_quizdetails(res-1);
	}
    else if(res == -1) welcomepage_admin();
    else {
        printf("Not a valid response try agian\n");
        res = -2;
    }

	}while(res <-1 || res> quizlist.no_of_quizes );

}

void welcomepage_admin(){
    clearscr();
    printf("Welcome %s!\npress y to see quizlist or add one\npress q to logout and goback to login page\n",currentuser.username);
    int b = 0;
    char x;

    do{
        scanf("%c",&x);
        clearBuf();
    if (x =='y'){
        showqlist_admin();
        }
    else if (x=='q'){
       /*bharghav's function */
    }
    else{
        printf("Invalid response try again(y or q)\n");
    }
    }while (x!='y'&&x!='q');

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Quiz Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void init(int index) {
  char a[4], b[2];
  currentuser.ID=0;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < max_alternative_q; ++j) {
      sprintf(a, "%d,", i);
      sprintf(b, "%d", j);
      strcpy(quizlist.quiz[index].question[i][j].statement, strcat(a,b));
      quizlist.quiz[index].question[i][j].response[currentuser.ID].status=78;
    }
  }
  strcpy(quizlist.quiz[index].name, "Test Quiz-1");
  quizlist.quiz[index].no_of_questions=10;
  quizlist.quiz[index].no_of_max_attempts=1;
}

void takeQuiz(int index) {
  //If reattempt is possible
  if (quizlist.quiz[index].attempt_list[currentuser.ID]<quizlist.quiz[index].no_of_max_attempts) {
    //Set next attempt number
    int attempt=quizlist.quiz[index].attempt_list[currentuser.ID];
    //Make quiz
    makeQuiz(index, attempt);
    //Go to quiz matrix
    qMatrix(index, attempt);
    //Update attempt data
    quizlist.quiz[index].no_of_students_attempted++;
    quizlist.quiz[index].attempt_list[currentuser.ID]++;
    currentuser.quizes_attempted[index].no_attempts++;
    //Autograde this attempt
    autoGradeAttempt(index, attempt);
  }
  //If reattempt not possible
  else {
    printf("No more reattempts are allowed!\n");
  }
}

void qMatrix(int index, int attempt) {
  printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
  printf("-------------------------------------------\n               Question Matrix             \n\n");
  for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
    if (i%5==0) {
      printf("\n");
    }
    if (i+1<10) {
      printf(" %d)[%c]   ", i+1, quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].status);
    }
    else {
      printf("%d)[%c]   ", i+1, quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].status);
    }
  }

  printf("\n\nKey:\n[U] Unattempted\n[S] Seen\n[A] Answered\n");
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
      clearscr();
      printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
      printf("-------------------------------------------\n");
      printf("Quiz submitted!\nHit ENTER to proceed to main menu,\n");
      getchar();
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
  printf("-------------------------------------------\n                  Question %d               \n\n", i+1);
  printf("Question:\n");
  printf("%s\n\n", quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].statement);
  printf("Enter the answer (enter ESC key to exit without answering):\n");
  //Capture answer
  smart_fgets(quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].answer, 1000, stdin);
  //Mark as attempted
  quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].status=65;
  //If ESC is answer
  if (quizlist.quiz[index].question[userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].answer[0]==27) {
    //Empty the answer
    strcpy(quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].answer, "");
    //Set status to seen
    quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].status=83;
  }
  clearscr();
  quizNav(i, index, attempt);
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
  if (quizlist.quiz[index].attempt_list[currentuser.ID]<quizlist.quiz[index].no_of_max_attempts) {
    int q_status[quizlist.quiz[index].no_of_questions];
    for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
      currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]=-1;
      currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]=-1;
      q_status[i]=0;
    }
    //Randomise Question Order
    for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
      while(currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]==-1) {
        rand=randNum(0,quizlist.quiz[index].no_of_questions-1);
        if (q_status[i]==0) {
          currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]=rand;
          q_status[i]=1;
        }
      }
    }
    //Go through randomly chosen question order
    for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
      //Run until the alternative is set
      while(currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]==-1) {
        //Generate random alternative number
        rand=randNum(0,max_alternative_q);
        //See if this alternative has 'N' status
        if (quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][rand].response[currentuser.ID].status==78) {
          //Set the alternative
          currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]=rand;
          //Set status of this alternative to 'U'
          quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][rand].response[currentuser.ID].status=85;
        }
      }
    }
  }
}

void autoGradeAttempt(int index, int attempt) {
  for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {  //Grade individual questions
    //If status is attempted
    if (quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].status==65) {
      //Check if correct
      if (strcmp(quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[currentuser.ID].answer, quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].solution)) {
        //Give full marks
        currentuser.quizes_attempted[index].attempt[attempt].marks[i] = quizlist.quiz[index].question[currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][0]][currentuser.quizes_attempted[index].attempt[attempt].q_bank[i][1]].marks;
        //Update result for this attempt
        currentuser.quizes_attempted[index].attempt[attempt].result.attempted++;
        currentuser.quizes_attempted[index].attempt[attempt].result.correct++;
        currentuser.quizes_attempted[index].attempt[attempt].result.score += currentuser.quizes_attempted[index].attempt[attempt].marks[i];
      }
      //Otherwise it must be wrong
      else {
        //Give zero marks
        currentuser.quizes_attempted[index].attempt[attempt].marks[i] = 0;
        //Update result for this attempt
        currentuser.quizes_attempted[index].attempt[attempt].result.attempted++;
        currentuser.quizes_attempted[index].attempt[attempt].result.incorrect++;
      }
    }
  }
}

int main(){
    currentuser.ID = 0;
    quizlist.quiz[0].attempt_list[currentuser.ID] = 0;
    welcomepage_admin();
    takeQuiz(0);
}