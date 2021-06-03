#include "common.h"
#include "admin.h"
#include "login.h"
#include "analytics.h"

/*int main(){
    welcomepage_admin();
    return 0;
}*/

void preview_all_questions(int quiz_id){     //displays all questions without edit option
    clearscr();
    printf("Quiz name : %s\n",quizlist.quiz[quiz_id].name);
    for (int i = 0; i < quizlist.quiz[quiz_id].no_of_questions; i++){
        for (int alt = 0; alt < max_alternative_q; alt++){
            if(quizlist.quiz[quiz_id].question[i][alt].response[0].status != 'E') {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",i+1,alt+1);
                printf("Marks - %d\n\n",quizlist.quiz[quiz_id].question[i][alt].marks);
                printf("Statement:\n%s\n",quizlist.quiz[quiz_id].question[i][alt].statement);
                printf("Solution:\n%s\n",quizlist.quiz[quiz_id].question[i][alt].solution);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }
    }
    }
    printf("press any button to proceed\n");
    getchar();
    clearBuf();
    admin_quizdetails(quiz_id);
}

void change_max_attempts(int quiz_id){
    clearscr();
    printf("Quiz : %s\n",quizlist.quiz[quiz_id].name);
    printf("Type new max_attempts\n");
    int response;
    response = scanf_int(5,1);
    if (response < quizlist.quiz[quiz_id].no_of_max_attempts){
        for (int i = 0; i < max_users; i++){
            if(response>userlist[i].quizes_attempted[quiz_id].no_attempts){
                printf("Cann't change becouse few users already attempted more than this number\nType enter to go back");
                getchar();
                clearBuf();
                admin_quizdetails(quiz_id);
                return;
            }
        }
        printf("Are you sure to change the maximum attempts from %d to %d?\n",quizlist.quiz[quiz_id].no_of_max_attempts,response);
            char res;
            do{
                scanf("%c",&res);
                clearBuf();
                if(res == 'y' || res == 'Y'){
                    quizlist.quiz[quiz_id].no_of_max_attempts = response;
                    printf("maximum attempts changed successfully, Type enter to continue\n");
                    getchar();
                    clearBuf();
                    admin_quizdetails(quiz_id);
                    return;
                }
                else if(res == 'n' || res == 'N'){
                    admin_quizdetails(quiz_id);   
                    return;
                }
                else printf("Invalid response try again\n");
            }while(1);
    }
    else{
        printf("you are going to increase the number of max attempts for the quiz to make this change you may need to add few more questions\nmake sure that there are sufficient alternate questions by editing question option\n");
        printf("continue?(y/n)\n");
        char res1;
        do{
            scanf("%c",&res1);
            clearBuf();
            if(res1 == 'y' || res1 == 'Y'){
                for (int ques = 0; ques < quizlist.quiz[quiz_id].no_of_questions; ques++){
                    int alts= 0 ;
                    for (int  alt = 0; alt < max_alternative_q; alt++){
                        if (quizlist.quiz[quiz_id].question[ques][alt].statement[0] != '\0') alts++; 
                    }
                    if(alts < response) {
                        printf("few alternate questions found at %d question, please go back and add enough alternate questions\nType any key to go back'\n",ques+1);
                        getchar();
                        clearBuf();
                        admin_quizdetails(quiz_id);
                        return;
                    }
                }
                printf("Are you sure to change the maximum attempts from %d to %d?\n",quizlist.quiz[quiz_id].no_of_max_attempts,response);
                char res;
                do{
                    scanf("%c",&res);
                    clearBuf();
                    if(res == 'y' || res == 'Y'){
                        quizlist.quiz[quiz_id].no_of_max_attempts = response;
                        printf("maximum attempts changed successfully, press any key to continue\n");
                        getchar();
                        clearBuf();
                        admin_quizdetails(quiz_id);
                        return;
                    }
                    else if(res == 'n' || res == 'N'){
                        admin_quizdetails(quiz_id);   
                        return;
                    }
                    else printf("Invalid response try again\n");
                }while(1);
            }
            else if (res1 == 'n'||res1=='N'){
                admin_quizdetails(quiz_id);
                return;
            }
            else printf("not a valid response try again\n");
        }while(1);
    }
}
    

void preview_question(int quiz_id,int ques_id){
    int alts= 0;
    for (int alt = 0; alt < max_alternative_q; alt++){
            if(quizlist.quiz[quiz_id].question[ques_id][alt].response[0].status != 'E') {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",ques_id+1,alt+1);
                printf("Marks - %d\n\n",quizlist.quiz[quiz_id].question[ques_id][alt].marks);
                printf("Statement:\n%s\n",quizlist.quiz[quiz_id].question[ques_id][alt].statement);
                printf("Solution:\n%s\n",quizlist.quiz[quiz_id].question[ques_id][alt].solution);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                alts++;
            }
    }
    printf("\n Type corresponding alt number to edit\notherwise type 0 to add alt questions/solution(you have to rewrite the total question and solution)\n Type -1 to go back to questions page\n");
    int res;
	res = scanf_int(alts,-1);
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
}

void preveiw_quiz(int quiz_Id){
    clearscr();
    printf("Quiz-%s\n\n",quizlist.quiz[quiz_Id].name);
    printf("~~~QUESTION_NO~~~~~~~~~~~~~~~NO.OF_ALTS~~~~~~~~~~~~~~~Marks\n");
    for (int qid = 0; qid <quizlist.quiz[quiz_Id].no_of_questions; qid++){
        int no_of_alts= 0;
        for (int i = 0; i < max_alternative_q; i++){
            if(quizlist.quiz[quiz_Id].question[qid][i].response[0].status != 'E') no_of_alts++;
        }        
        printf("     %d                           %d                   %d\n",qid+1,no_of_alts,quizlist.quiz[quiz_Id].question[qid][0].marks);    
    }
}

void add_question(int quiz_id,int question_id,int alt_id){
    clearscr();
    int resp;
    if (quizlist.quiz[quiz_id].question[question_id][0].marks == 0) {
        printf("Marks of %d question?\n",question_id+1);
        resp = scanf_int(1000,1);
        quizlist.quiz[quiz_id].question[question_id][0].marks = resp;
    }
    for (int ip = 0; ip < max_alternative_q; ip++){
        quizlist.quiz[quiz_id].question[question_id][ip].marks=quizlist.quiz[quiz_id].question[question_id][0].marks;
    }	
    char check='n';
    while(check != 'y'){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",question_id+1,alt_id+1);
        printf("type statment of %d-alternate for %d question(%d marks)\n\n",alt_id+1,question_id+1,quizlist.quiz[quiz_id].question[question_id][0].marks);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        smart_fgets(quizlist.quiz[quiz_id].question[question_id][alt_id].statement,max_question_length,stdin);
        printf("\nType Solution:\n");
        smart_fgets(quizlist.quiz[quiz_id].question[question_id][alt_id].solution,max_answer_length,stdin);
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
    res = scanf_int(quizlist.quiz[quiz_id].no_of_questions,-1);
  	if(res== -1){
          admin_quizdetails(quiz_id);
    }
	else if(res >0 && res <= quizlist.quiz[quiz_id].no_of_questions){
        preview_question(quiz_id,res-1);
	}
    else if(res == 0){   //adding questions.
        printf("Type no.of question to added extra(you can add %d maximum)\n",max_q_per_quiz-quizlist.quiz[quiz_id].no_of_questions);
        int res2=0;
	    res2 = scanf_int(max_q_per_quiz-quizlist.quiz[quiz_id].no_of_questions,0);
  	        if(res2 == 0){
                edit_questions(quiz_id);
                return;
        }
        else if(res2 > 0){
            if (res2 <= max_q_per_quiz-quizlist.quiz[quiz_id].no_of_questions){
            quizlist.quiz[quiz_id].no_of_questions += res2;
            ques_initialize(quizlist.quiz[quiz_id].no_of_questions-res2,quiz_id);
            addquestions_initial(quizlist.quiz[quiz_id].no_of_questions-res2,quiz_id);
            return;
            }
        }
    }

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
    getchar();
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
	while(res <= 0 || res >= max_q_per_quiz){
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
    printf("duration of quiz?(type number in minutes)\n");
    int response =  scanf_int(10000,1);
    quizlist.quiz[i].max_time = response * 60 ;  // in seconds.
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

void admin_Matrix(int stu_id,int index, int attempt) {
  printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
  printf("-------------------------------------------\n          %s's Analysis Matrix             \n\n",userlist[stu_id].username);
  quiz_result_admin(stu_id,index, attempt);
  for (int i = 0; i < quizlist.quiz[index].no_of_questions; ++i) {
    if (i%5==0) {
      printf("\n");
    }
    if (i+1<10) {
      printf(" %d) [%c] (%d/%d)   ", i+1, quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[stu_id].status, userlist[stu_id].quizes_attempted[index].attempt[attempt].marks[i] ,quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][1]].marks);
    }
    else {
      printf("%d) [%c] (%d/%d)   ", i+1, quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][1]].response[stu_id].status, userlist[stu_id].quizes_attempted[index].attempt[attempt].marks[i], quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i][1]].marks);
    }
  }

  printf("\n\nKey:\n[U] Unattempted            (p/q) p Marks Obtained Out of q\n[C] Correct\n[W] Wrong\n");
  printf("\n\nEnter question number you wish to analyse or '0' to exit analytics,\n");
  int num;
  scanf("%d", &num);
  clearBuf();
  if (num==0) {
    clearscr();
    response_admin(index);
  }
  else if (num>0&&num<=quizlist.quiz[index].no_of_questions) {
    clearscr();
    see_response_admin(stu_id,num, index, attempt);
  }
  else {
    clearscr();
    printf("Invalid Input!\n");
    admin_Matrix(stu_id,index, attempt);
  }
}

void quiz_result_admin(int stu_id,int index, int attempt) {
  printf("The details are: \n");
  printf("%s's score is %d \n",userlist[stu_id].username,userlist[stu_id].quizes_attempted[index].attempt[attempt].result.score);
  printf("No. of correct answers are %d \n",userlist[stu_id].quizes_attempted[index].attempt[attempt].result.correct);
  printf("No. of incorrect answers are %d \n\n",userlist[stu_id].quizes_attempted[index].attempt[attempt].result.incorrect);
}

void see_response_admin(int stu_id,int i, int index, int attempt) {
  printf("-------------------------------------------\n               %s-%s               \n", quizlist.quiz[index].name,userlist[stu_id].username);
  printf("-------------------------------------------\n             Question %d (%d Marks)\n\n", i, quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].marks);
  printf("\nQuestion:\n%s\n\n", quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].statement);
  printf("Solution:\n%s\n\n",quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].solution);
  printf("Response:\n%s\n\n", quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].response[stu_id].answer);
  printf("Score: %d/%d\n\n", userlist[stu_id].quizes_attempted[index].attempt[attempt].marks[i-1], quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].marks);
  printf("Time taken : %d (in min)\n",userlist[stu_id].quizes_attempted[index].attempt[attempt].time_taken/60);
  printf("Enter 'e' to exit ,'m' to grade question manually or  'n' to proceed to next question\n");
  char com;
  E:
  com=getchar();
  clearBuf();
  if (com=='e') {
    admin_Matrix(stu_id,index, attempt);
  }
  else if (com=='n') {
    clearscr();
    if (i+1<quizlist.quiz[index].no_of_questions) {   //next question index is less than equal last question index
      see_response_admin(stu_id, ++i , index, attempt);
    }
    else {                                            //If not go to first question
      see_response_admin(stu_id,1, index, attempt);
    }
  }
  else if(com =='m'){
      printf("Enter new marks\n");
      int res = scanf_int(quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].marks,0);
      if(res != 0 && userlist[stu_id].quizes_attempted[index].attempt[attempt].marks[i-1] == 0){
          userlist[stu_id].quizes_attempted[index].attempt[attempt].result.correct++;
          userlist[stu_id].quizes_attempted[index].attempt[attempt].result.incorrect--;
          quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].response[stu_id].status = 'C';

        }
      if(res == 0 && userlist[stu_id].quizes_attempted[index].attempt[attempt].marks[i-1] != 0){
          userlist[stu_id].quizes_attempted[index].attempt[attempt].result.correct--;
          userlist[stu_id].quizes_attempted[index].attempt[attempt].result.incorrect++;
          quizlist.quiz[index].question[userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][0]][userlist[stu_id].quizes_attempted[index].attempt[attempt].q_bank[i-1][1]].response[stu_id].status = 'W';
        }
      userlist[stu_id].quizes_attempted[index].attempt[attempt].marks[i-1] = res;
      printf("score changed successfully\nType any character to proceed\n");
      getchar();
      clearBuf();
      clearscr();
      see_response_admin(stu_id, i,index,attempt);
      return;
  }
  else {
    printf("Invalid option! Please try again,\n");
    goto E;
  }
}

void response_admin(int quiz_id){
    clearscr();
    printf("Quiz name: %s\n",quizlist.quiz[quiz_id].name);
    if (quizlist.quiz[quiz_id].no_of_students_attempted != 0){
        int ids[no_of_currentusers];
        int max =0;
        printf("S.no~~~~~~~~~~~~User name~~~~~~~~~~attempts\n");
        for (int i = 0; i < no_of_currentusers; i++){
            if(userlist[i].quizes_attempted[quiz_id].no_attempts != 0){
                ids[max] = i;
                printf("%d                %s                 %d\n",++max,userlist[i].username,quizlist.quiz[quiz_id].no_of_students_attempted);            
            }
            
        }
        printf("Type corresponding serial number to veiw responses\nType 0 to go back\n");
        int res;
        res = scanf_int(max,0);
        if(res ==0){
            admin_quizdetails(quiz_id);
            return;
        }
        else{
            if(userlist[ids[res]].quizes_attempted[quiz_id].no_attempts == 1){
                admin_Matrix(ids[res],quiz_id,0);
                clearscr();
                return;
            }
            else{
                printf("User has attempted this quiz %d times\nType an attempt number to veiw responses(greater number implies recent attempt)\n",userlist[ids[res]].quizes_attempted[quiz_id].no_attempts);
                int resp = scanf_int(userlist[ids[res]].quizes_attempted[quiz_id].no_attempts,1);
                clearscr();
                admin_Matrix(ids[res],quiz_id,resp-1);
                return;
            }
        }

            
    }

    else {
        printf("no one attempted the quiz\nPress ENTER to goback");
        getchar();
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

void delete_quiz(int quiz_id){
    printf("Are you sure to delete this quiz?(y/n)\n");
    do{
        char res;
        scanf("%c",&res);
        if(res == 'y' || res == 'Y'){

                for(int id= quiz_id ; id < quizlist.no_of_quizes;id++){
                    quizlist.quiz[id] = quizlist.quiz[id+1];
                }
                quizlist.no_of_quizes--;
                printf("quiz deleted succesfully\nType any key to go back\n");
                getchar();
                clearBuf();
                showqlist_admin();
                return;
        }
        else if (res = 'n' || res == 'N'){
            admin_quizdetails(quiz_id);
            return;
        }
        else{
            printf("Invalid response please type again!");
        }
    }while(1);
}


void admin_quizdetails(int n){
    clearscr();
    printf("Quiz name : %s\n",quizlist.quiz[n].name);
    printf("No.of questions %d\n",quizlist.quiz[n].no_of_questions);
    printf("No.of maximum attempts : %d\n",quizlist.quiz[n].no_of_max_attempts);
    printf("Type\n r : to view student responses\n m : To change distrubution of marks\n e : To add questions/edit existing questions \n p : to preview whole question paper\n c : to change maximum number of attempts\n d : to delete this quiz\n 0 : to go back to quizzes list\n");
    char res;
	do {
	scanf("%c",&res);
	clearBuf();
  	if(res=='r'){
        response_admin(n);
        return;
    }
	else if(res == 'e'){
        edit_questions(n);
        return;
	}
    else if(res == 'm'){
        preveiw_quiz(n);
        change_marks(n);
       return;
    }
    else if(res == '0'){
        showqlist_admin();
        return;
    }
    else if(res == 'p'){
        preview_all_questions(n);
        return;
    }
    else if (res == 'c'){
        change_max_attempts(n);
        return;
    }
    else if(res == 'd'){
        printf("Type your password\nType a wrong password to cancel deletion\n");
        char resp[14];
        smart_fgets(resp,14,stdin);
        if(strcmp(currentuser.password,resp) == 0 ){
            delete_quiz(n);
            return;
        }
        else{
            admin_quizdetails(n);
            return;
        }
    }
    
    else printf("Not a valid response try agian\n");
	}while(1);
}

void showqlist_admin(){
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
        return;
	}
    else if(res == -1) welcomepage_admin();
    else {
        printf("Not a valid response try agian\n");
        res = -2;
    }

	}while(res <-1 || res> quizlist.no_of_quizes );

}

void delete_user(int id){
    printf("are you sure to delete this user?(y/n)\n");
    char res = takeyorno();
    if(res == 'y'){
        int auth = authenticate();
        if(auth == 0){
            for (int mem = id; mem < no_of_currentusers; mem++){
                userlist[mem] = userlist[mem+1];
            }
            no_of_currentusers--;
            printf("User deleted press any charachter to go back\n");
            getchar();
            clearBuf();
            clearscr();
            view_userlist();
            return;
        }
        else{
            clearscr();
            view_user(id);
        }
    }

}

void view_user(int id){
    if(userlist[id].type == 1)  printf("username :\n%s\npassword :\n%s\nType :\nAdmin\n\nType 1 to edit password for this user\n-1 to delete user\n 0 to goback.\n",userlist[id].username,userlist[id].password);
    else if(userlist[id].type == 0)  printf("username :\n%s\npassword :\n%s\nType :\nUser\n\nType 1 to edit password for this user\n-1 to delete user\n 0 to goback.\n",userlist[id].username,userlist[id].password);
    int response = scanf_int(1,-1);
    if(response == 1){
        take_password(id);
        clearscr();
        view_user(id);
    }
    else if(response == 0){
        clearscr();
        view_userlist();
    }
    else{
        delete_user(id);
    }
}

void add_user(){
    printf("Type new Username :\n");
    char response[16];
    smart_fgets(response,18,stdin);
    for (int id = 0; id < no_of_currentusers; id++){
        if (strcmp(response,userlist[id].username)==0){
            printf("This username already exists\ntry again\n");
            add_user();
            return;
        }
    }
    strcpy( userlist[no_of_currentusers].username,response);
    printf("type account type(0 for user and 1 for admin\n");
    userlist[no_of_currentusers].type = scanf_int(1,0);
    take_password(no_of_currentusers);
    no_of_currentusers++;
    view_userlist();
}

void take_password(int id){
    printf("Type new password for the user:\n");
    char resp[18];
    smart_fgets(resp,18,stdin);
    printf("conform password:\n");
    char resp2[18];
    smart_fgets(resp2,18,stdin);
    if(strcmp(resp,resp2)==0){
        printf("password created/changed successfully\nType Enter to go back\n");
        strcpy(userlist[id].password,resp);
        getchar();
    } 
    
}

int authenticate(){
    printf("please type your password:\n");
    char resp[18];
    smart_fgets(resp,18,stdin);
    if(strcmp(resp,currentuser.password)==0){
        return 1;
    }
    else{
        printf("wrong password\n Like to try again?(y/n)\n");
        if(takeyorno() == 'y'){
            return authenticate();
        }
        else{
            return 0;
        }

    }
}

char takeyorno(){
    char c;
    scanf("%c",&c);
    clearBuf();
    if(c == 'y' || c == 'Y') return 'y';
    else if(c == 'n' ||c == 'N') return 'n';
    else{
        printf("Invalid response type again(y/n)\n");
        c = takeyorno();
    }
    return c;
}

void view_userlist(){
    printf("S.no~~~~~~~Account_type~~~~~~~~Username\n");
    for (int id = 0; id < no_of_currentusers; id++){
        if(userlist[id].type == 1)  printf("%d\t\tAdmin\t\t%s\n",id+1,userlist[id].username);
        else if(userlist[id].type == 0)  printf("%d\t\tUser\t\t%s\n",id+1,userlist[id].username);
    }
    printf("\nType a serial number to view about user\nType 0 is add a user\nType -1 to goback\n");
    int response = scanf_int(no_of_currentusers,-1);
    if (response == -1){
        welcomepage_admin();
        return;
    }
    else if (response == 0){
        clearscr();
        add_user();
    }
    else{
        view_user(response-1);
    }
}

void manage_tags(){

}

void welcomepage_admin(){
    clearscr();
    printf("Welcome %s!\n\n",currentuser.username);
    printf("What would you like to do?\n");
    printf("- See or manage quizzes (Enter q)\n");
    printf("-see or add users (a)\n");
    printf("- Log out (Enter l)\n");
    printf("- Change password (Enter c)\n");

    int b = 0;
    char x;

    do{
        scanf("%c",&x);
        clearBuf();
    if (x =='q'){
        showqlist_admin();  // goes to quizlist
        }
    else if (x=='l'){
        loginpage();
    }
    else if (x=='c'){
        change_password();
    }
    else if(x = 'a'){
        clearscr();
        view_userlist();
    }
    else if(x = 't'){
        manage_tags();
    }
    else if(x = 'c'){
        
    } 
    else{
        printf("Invalid response try again(y or q)\n");
    }
    }while (x!='l'&&x!='q'&&x!='t'&&x!= 'a'&& x!='c');

}
