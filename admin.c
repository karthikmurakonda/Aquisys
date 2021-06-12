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
            if(response[0][quiz_id][i][alt].status != 'E') {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",i+1,alt+1);
                printf("Marks - %d\n\n",question[quiz_id][i][alt].marks);
                printf("Statement:\n%s\n",question[quiz_id][i][alt].statement);
                printf("Solution:\n%s\n",question[quiz_id][i][alt].solution);
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            }
    }
    }
    printf("press any button to proceed\n");
    wait_for_enter();
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
            if(response < quizes_attempted[i][quiz_id].no_attempts){
                printf("Cann't change becouse few users already attempted more than this number\nType enter to go back");
                wait_for_enter();
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
                    appdata_save(0);
                    wait_for_enter();
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
                        if (question[quiz_id][ques][alt].statement[0] != '\0') alts++; 
                    }
                    if(alts < response) {
                        printf("few alternate questions found at %d question, please go back and add enough alternate questions\nType any key to go back'\n",ques+1);
                        wait_for_enter();
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
                        appdata_save(0);
                        wait_for_enter();
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
            if(response[0][quiz_id][ques_id][alt].status != 'E') {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",ques_id+1,alt+1);
                printf("Marks - %d\n\n",question[quiz_id][ques_id][alt].marks);
                printf("Statement:\n%s\n",question[quiz_id][ques_id][alt].statement);
                printf("Solution:\n%s\n",question[quiz_id][ques_id][alt].solution);
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
            appdata_save(1);
            }
            else if (alts == 5){
                printf("Can't add alt anymore all 5 alts exists");
            }
            preview_question(quiz_id,ques_id);
        }
    else if(res > 0 && res <= alts){
        add_question(quiz_id,ques_id,res-1);
        appdata_save(1);
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
            if(response[0][quiz_Id][qid][i].status != 'E') no_of_alts++;
        }        
        printf("     %d                           %d                   %d\n",qid+1,no_of_alts,question[quiz_Id][qid][0].marks);    
    }
}

void add_question(int quiz_id,int question_id,int alt_id){
    clearscr();
    int resp;
    if (question[quiz_id][question_id][0].marks == 0) {
        printf("Marks of %d question?\n",question_id+1);
        resp = scanf_int(1000,1);
        question[quiz_id][question_id][0].marks = resp;
    }
    for (int ip = 0; ip < max_alternative_q; ip++){
        question[quiz_id][question_id][ip].marks=question[quiz_id][question_id][0].marks;
    }	
    char check='n';
    while(check != 'y'){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~%d.%d~~~~~~~~~~~~~~~~~~~~~~~~\n\n",question_id+1,alt_id+1);
        printf("type statment of %d-alternate for %d question(%d marks)\n\n",alt_id+1,question_id+1,question[quiz_id][question_id][0].marks);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        smart_fgets(question[quiz_id][question_id][alt_id].statement,max_question_length,stdin);
        printf("\nType Solution:\n");
        smart_fgets(question[quiz_id][question_id][alt_id].solution,max_answer_length,stdin);
        printf("\npreview:\n\n%s\n\n",question[quiz_id][question_id][alt_id].statement);
        printf("Solution:\n");
        printf("%s\n\n",question[quiz_id][question_id][alt_id].solution);
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
    for(int user = 0; user<max_users;user++)    response[user][quiz_id][question_id][alt_id].status = 'N';   //changing status from E to N if question is filled.
    question[quiz_id][question_id][alt_id].status = 'N';
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
    if(questart_id == 0){
        for(int tid=0;tid<max_tags;tid++)   quizlist.quiz[quiz_id].tag_ids[tid] = 0;
    }
    for (int i = questart_id; i <= quizlist.quiz[quiz_id].no_of_questions; i++){
        for(int d=0;d <5;d++){
            question[quiz_id][i][d].statement[0] = '\0';
            question[quiz_id][i][d].solution[0] = '\0';
            question[quiz_id][i][d].marks = 0;
            for(int uid = 0;uid < max_users;uid++){
                response[uid][quiz_id][i][d].status = 'E';
                response[uid][quiz_id][i][d].answer[0] = '\0';
                quizes_attempted[uid][quiz_id].attempt[d].result.attempted = 0;
                quizes_attempted[uid][quiz_id].attempt[d].result.correct = 0;
                quizes_attempted[uid][quiz_id].attempt[d].result.incorrect=0;
                quizes_attempted[uid][quiz_id].attempt[d].result.score= 0;
            }
            question[quiz_id][i][d].status = 'E';
        }
    }
}

void addquestions_initial(int questart_id,int quiz_id){
    preveiw_quiz(quiz_id);
    printf("press ENTER to start entering questions\n");
    wait_for_enter();
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
    appdata_save(1);
    edit_questions(quiz_id);

}

void add_instrucion_page(int quiz_id){
    clearscr();
    printf("\nType the instructions :(press enter one time to start a new line and press enter two times to end adding instruction.)\n");
    printf("\n*****************************************************************************************************************************\n");
    multiline_input(quizlist.quiz[quiz_id].instructions,1000);
    clearscr();
    printf("Preveiw :\n");
    printf("\n********************************************************************************************************\n");
    printf("%s",quizlist.quiz[quiz_id].instructions);
    printf("***********************************************************************************************************\n");
    printf("would like to continue?(y/n)");
    char res = takeyorno();
    if(res == 'n'){
        add_instrucion_page(quiz_id);
    }
    appdata_save(0);
    clearscr();
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
        quizlist.quiz[quizlist.no_of_quizes-1].instructions[0] = '\0';    //initializing quiz instructions.
        quizlist.quiz[quizlist.no_of_quizes -1].visible = 0;              //making quiz not visible by default.
        add_instrucion_page(quizlist.no_of_quizes-1);
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
      printf(" %d) [%c] (%d/%d)   ", i+1, response[stu_id][index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][1]].status, quizes_attempted[stu_id][index].attempt[attempt].marks[i] ,question[index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][1]].marks);
    }
    else {
      printf("%d) [%c] (%d/%d)   ", i+1, response[stu_id][index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][1]].status, quizes_attempted[stu_id][index].attempt[attempt].marks[i], question[index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i][1]].marks);
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
  printf("%s's score is %d \n",userlist[stu_id].username,quizes_attempted[stu_id][index].attempt[attempt].result.score);
  printf("No. of correct answers are %d \n",quizes_attempted[stu_id][index].attempt[attempt].result.correct);
  printf("No. of incorrect answers are %d \n\n",quizes_attempted[stu_id][index].attempt[attempt].result.incorrect);
}

void see_response_admin(int stu_id,int i, int index, int attempt) {
  printf("-------------------------------------------\n               %s-%s               \n", quizlist.quiz[index].name,userlist[stu_id].username);
  printf("-------------------------------------------\n             Question %d (%d Marks)\n\n", i, question[index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].marks);
  printf("\nQuestion:\n%s\n\n", question[index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].statement);
  printf("Solution:\n%s\n\n",question[index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].solution);
  printf("Response:\n%s\n\n", response[stu_id][index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].answer);
  printf("Score: %d/%d\n\n", quizes_attempted[stu_id][index].attempt[attempt].marks[i-1], question[index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].marks);
  printf("Time taken : %d (in min)\n",quizes_attempted[stu_id][index].attempt[attempt].time_taken/60);
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
    if (i <quizlist.quiz[index].no_of_questions) {   //next question index is less than equal last question index
      see_response_admin(stu_id, ++i , index, attempt);
    }
    else {                                            //If not go to first question
      see_response_admin(stu_id, 1, index, attempt);
    }
  }
  else if(com =='m'){
      printf("Enter new marks\n");
      int res = scanf_int(question[index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].marks,0);
      if(res != 0 && quizes_attempted[stu_id][index].attempt[attempt].marks[i-1] == 0){
          quizes_attempted[stu_id][index].attempt[attempt].result.correct++;
          quizes_attempted[stu_id][index].attempt[attempt].result.incorrect--;
          response[stu_id][index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].status = 'C';
        }
      if(res == 0 && quizes_attempted[stu_id][index].attempt[attempt].marks[i-1] != 0){
          quizes_attempted[stu_id][index].attempt[attempt].result.correct--;
          quizes_attempted[stu_id][index].attempt[attempt].result.incorrect++;
          response[stu_id][index][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][0]][quizes_attempted[stu_id][index].attempt[attempt].q_bank[i-1][1]].status = 'W';
        }
      quizes_attempted[stu_id][index].attempt[attempt].marks[i-1] = res;
      printf("score changed successfully\nType any character to proceed\n");
      appdata_save(1);
      wait_for_enter();
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
            if(quizes_attempted[i][quiz_id].no_attempts != 0){
                ids[max] = i;
                printf("%d                %s                 %d\n",++max,userlist[i].username,quizes_attempted[i][quiz_id].no_attempts);            
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
            if(quizes_attempted[ids[res-1]][quiz_id].no_attempts == 1){
                admin_Matrix(ids[res-1],quiz_id,0);
                clearscr();
                return;
            }
            else{
                printf("User has attempted this quiz %d times\nType an attempt number to veiw responses(greater number implies recent attempt)\n",quizes_attempted[ids[res-1]][quiz_id].no_attempts);
                int resp = scanf_int(quizes_attempted[ids[res-1]][quiz_id].no_attempts,1);
                clearscr();
                admin_Matrix(ids[res-1],quiz_id,resp-1);
                return;
            }
        }            
    }
    else {
        printf("no one attempted the quiz\nPress ENTER to goback");
        wait_for_enter();
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
        printf("type new marks for question %d(previously %d marks)\n",res,question[quiz_id][res-1][0].marks);
        int res2;
        check = 1;
        int check2 = 0;
	    do {
	        scanf("%d",&res2);
	        clearBuf();
  	        if(res2 >0 ){
                for(int i = 0;i <max_alternative_q;i++) question[quiz_id][res-1][i].marks = res2; 
                appdata_save(0);
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

                for(int id= quiz_id ; id < quizlist.no_of_quizes;id++){         //changes to struct quiz.
                    quizlist.quiz[id] = quizlist.quiz[id+1];    
                }
                for(int stu_id = 0; stu_id < no_of_currentusers;stu_id++){          // changes to array quizzes attempted and responses;
                    for(int id= quiz_id ; id < quizlist.no_of_quizes;id++){
                        quizes_attempted[stu_id][id] = quizes_attempted[stu_id][id+1];
                        for(int ques_id = 0;ques_id< max_q_per_quiz;ques_id++){
                            for(int alt_id= 0;alt_id < max_alternative_q;alt_id++){
                                response[stu_id][id][ques_id][alt_id] = response[stu_id][id+1][ques_id][alt_id];
                            }
                        }
                    }
                }
                quizlist.no_of_quizes--;
                appdata_save(1);
                printf("quiz deleted succesfully\nType any key to go back\n");
                wait_for_enter();
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

void tag_quiz(int quiz_id){
    printf("Type corresponding tag number from above printed taglist to remove tag\n 0 to add a tag\n");
    int response;
    if(response != 0){
    do{
    response = scanf_int(max_tags,0);
    if(taglist[response-1]==""){
        if(quizlist.quiz[quiz_id].tag_ids[response-1]==0);
            printf("Not a valid response try again\n");
            response == -1;
    }
    }while(response==-1);
    }
    if(response==0){
        clearscr();
        printf("Available tags :\n");
        int num = 0;
        for (int i = 0; i < max_tags; i++){
            if(quizlist.quiz[quiz_id].tag_ids[i] == 0) {
                if(taglist[i][0]!= '\0'){
                printf("%d\t%s\n",i+1,taglist[i]);
                num++;
                }
            }
        }
        if(num !=0){
            printf("\nType the corresponding number to add a tag\n");
            int res = scanf_int(max_tags,1);
            if(taglist[res-1][0] != '\0'){
                quizlist.quiz[quiz_id].tag_ids[res-1] = 1;
                printf("Quiz tagged successfully\npress ENTER to continue\n");
                appdata_save(0);
                wait_for_enter();
                admin_quizdetails(quiz_id);
            }
            else{
                printf("Error can't add empty tag try again\npress ENTER to continue\n");
                wait_for_enter();
                admin_quizdetails(quiz_id);
            }
            
        }
        else{
            printf("No tags left to tag\npress ENTER to continue\n");
            wait_for_enter();
            admin_quizdetails(quiz_id);
        }
    }
    else{
        if(quizlist.quiz[quiz_id].tag_ids[response-1]== 1){
        printf("Are you sure to remove %s tag for this quiz?(y/n)\n",taglist[response-1]);
        char resp = takeyorno();
        if(resp == 'y'){
            quizlist.quiz[quiz_id].tag_ids[response-1] = 0;
            printf("Tag removed successfully\npress ENTER to conltinue\n");
            appdata_save(0);
            wait_for_enter();
            admin_quizdetails(quiz_id);
        }
        else{
            admin_quizdetails(quiz_id);
        }
        }
        else{
            printf("Invalid response press ENTER to continue\n");
            wait_for_enter();
            admin_quizdetails(quiz_id);
        }
    }
    
}


void admin_quizdetails(int n){
    clearscr();
    printf("Quiz name : %s\n",quizlist.quiz[n].name);
    printf("\n*****************************************INSTRUCTIONS*********************************************\n");
    printf("%s",quizlist.quiz[n].instructions);
    printf("****************************************************************************************************\n");
    printf("No.of questions %d\n",quizlist.quiz[n].no_of_questions);
    printf("No.of maximum attempts : %d\n",quizlist.quiz[n].no_of_max_attempts);
    printf("\nTags :\n");
    int tagnum = 0,num =0;  //tagnum no tags tagged to this quiz , num is no.of totall tags in system at present.
    for(int ti=0; ti < max_tags;ti++){
        if(taglist[ti] !=""){
            if(quizlist.quiz[n].tag_ids[ti] == 1 ){
                printf("%d)%s\n",ti+1,taglist[ti]);
                tagnum++;
            }
           num ++;
        }
    }
    if(tagnum == 0) printf("(no tags quiz is open for all users)\n");
    if(quizlist.quiz[n].visible == 0){
        printf("Availability :\n%sNot visible to all users%s\n",red, normal);
    }
    else if(quizlist.quiz[n].visible == 1){
        printf("Availability :\n%sOnly Instructions visible%s\n", yellow,normal);
    }
    else if(quizlist.quiz[n].visible == 2){
        printf("Availability :\n%sAvailable to tagged users%s\n", green, normal);
    }
    printf("\nType\n r : to view student responses\n m : To change distrubution of marks\n e : To add questions/edit existing questions \n p : to preview whole question paper\n c : to change maximum number of attempts\n d : to delete this quiz\n t : to manage tags for this quiz\n i : to change instructions \n a : to change availabilityof this quiz\n 0 : to go back to quizzes list\n");
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
        if(quizlist.quiz[n].no_of_students_attempted == 0){
            if(quizlist.quiz[n].visible != 2){
            preveiw_quiz(n);
            change_marks(n);
            return;
            }
            else{
            printf("you can't change max marks of questions when it is available to users change the availability and come back.\ntype enter to continue\n");
            wait_for_enter(); 
            admin_quizdetails(n);
            return;              
            }
        }
        else{
            printf("you can't change max marks of question once after a user submittes the quiz\ntype enter to continue\n");
            wait_for_enter();
            admin_quizdetails(n);
            return;  
        }
       return;
    }
    else if(res == 'a'){
        clearscr();
        printf("Type a corresponding number to change availabilty :\n0 : make quiz invisible\n1 : make only instructions visible\n2 : make users to attempt the quiz\n");
        quizlist.quiz[n].visible = scanf_int(2,0);
        appdata_save(0);
        printf("availability updated successfully\nType ENTER to continue\n");
        wait_for_enter();
        admin_quizdetails(n);
        return;
    }
    else if(res == 'i'){
        add_instrucion_page(n);
        admin_quizdetails(n);
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
    else if(res == 't'){
        if(num !=0){
        tag_quiz(n);
        return;
        }
        else{
            printf("No tags available currently\nTo create a tag first\ntype ENTER to continue.\n");
            wait_for_enter();
            admin_quizdetails(n);
            return;
        }

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
    appdata_read();
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
    else if(res == -1) return;
    else {
        printf("Not a valid response try agian\n");
        res = -2;
    }

	}while(res <-1 || res> quizlist.no_of_quizes );

}

void delete_user(int id){
    if(id != 0){
        printf("are you sure to delete this user?(y/n)\n");
        char res = takeyorno();
        if(res == 'y'){
            int auth = authenticate();
            if(auth == 1){
                for (int mem = id; mem < no_of_currentusers-1; mem++){
                    userlist[mem] = userlist[mem+1];        //have to change responses too
                    for (int quiz_id = 0; quiz_id < quizlist.no_of_quizes; quiz_id++)
                    {
                        quizes_attempted[mem][quiz_id] = quizes_attempted[mem+1][quiz_id];
                        for (int ques_id = 0; ques_id < max_q_per_quiz; ques_id++)
                        {
                            for (int alt_id = 0; alt_id < max_alternative_q; alt_id++)
                            {
                                response[mem][quiz_id][ques_id][alt_id] = response[mem+1][quiz_id][ques_id][alt_id];
                            }
                            
                        }
                        
                    }
                    
                }
                no_of_currentusers--;
                appdata_save(1);
                printf("User deleted press any charachter to go back\n");
                wait_for_enter();
                clearscr();
                view_userlist();
                return;
            }
            else{
                clearscr();
                view_user(id);
            }
        }
        else{
            clearscr();
            view_user(id); 
        }
    }
    else{
        printf("you can't able to delete this account by default\npress enter to continue\n");
        wait_for_enter();
        clearscr();
        view_user(id);
    }

}

void rmvtag_user(int id){
    clearscr();
    for (int i = 0; i < max_tags; i++){
        if(userlist[id].tags[i] == 1)   printf("%d.%s\n",i+1,taglist[i]);
    }
    printf("Type the corresponding number to remove the tag\n");
    int response = scanf_int(max_tags,1);
    printf("Are you sure to remove this tag for the user?(y/n)\n");
    char resp = takeyorno();
    if(resp == 'y'){
        userlist[id].tags[response-1] = 0;
        printf("tag removed successfully type ENTER to go back\n");
        appdata_save(1);
        wait_for_enter();
        clearscr();
        view_user(id);
    }
    else{
        clearscr();
        view_user(id);
    }
}

void view_user(int id){
    if(userlist[id].type == 1)  printf("username :\n%s\npassword :\n%s\nType :\nAdmin\n\nType 1 to edit password for this user\n-1 to delete user\n 0 to goback.\n",userlist[id].username,userlist[id].password);
    else if(userlist[id].type == 0) { printf("username :\n%s\npassword :\n%s\nType :\nUser\n\nTags :\n",userlist[id].username,userlist[id].password);
    for (int i = 0; i < max_tags; i++){
        if(userlist[id].tags[i] == 1)   printf("%s\n",taglist[i]);
    }   
    printf("\nType 2 to add tags for this user\nType 1 to edit password for this user\n-1 to delete user\n-2 to a remove tag for the user\n0 to goback.\n");
    }
    int response = scanf_int(2,-2);
    if(response == 1){
        take_password(id);
        clearscr();
        appdata_save(1);
        view_user(id);
    }
    else if(response == 0){
        clearscr();
        view_userlist();
    }
    else if(response == 2){
        tag_user(id);
        clearscr();
        appdata_save(1);
        view_user(id);
    }
    else if (response == -2){
        rmvtag_user(id);
    }
    else{
        delete_user(id);
    }
}

void add_user(){
    printf("Type new Username :\n");
    char resp[16];
    smart_fgets(resp,18,stdin);
    for (int id = 0; id < no_of_currentusers; id++){
        if (strcmp(resp,userlist[id].username)==0){
            printf("This username already exists\ntry again\n");
            add_user();
            return;
        }
    }
    strcpy( userlist[no_of_currentusers].username,resp);
    printf("type account type(0 for user and 1 for admin)\n");
    userlist[no_of_currentusers].type = scanf_int(1,0);
    for(int i = 0;i < max_tags;i++){
        userlist[no_of_currentusers].tags[i] = 0;   //initializing tags for the new user.
    }
    if(taglist[0][0]!= '\0' && userlist[no_of_currentusers].type == 0){
    printf("Add tags for this user?y/n\n");
    char resp = takeyorno();
    if(resp == 'y'){
        tag_user(no_of_currentusers);
    }
    }
    take_password(no_of_currentusers);
    for (int qid = 0; qid < quizlist.no_of_quizes; qid++){
        for (int ques_id = 0; ques_id < quizlist.quiz[qid].no_of_questions; ques_id++){
            for (int alt_id = 0; alt_id < max_alternative_q; alt_id++)
            {
               response[no_of_currentusers][qid][ques_id][alt_id].status = question[qid][ques_id][alt_id].status;
               response[no_of_currentusers][qid][ques_id][alt_id].answer[0] = '\0';
            }
        }
        for(int attempt=0;attempt < quizlist.quiz[qid].no_of_max_attempts;attempt++){
            quizes_attempted[no_of_currentusers][qid].attempt[attempt].result.attempted = 0;
            quizes_attempted[no_of_currentusers][qid].attempt[attempt].result.correct = 0;
            quizes_attempted[no_of_currentusers][qid].attempt[attempt].result.incorrect=0;
            quizes_attempted[no_of_currentusers][qid].attempt[attempt].result.score= 0;      
        }
        quizes_attempted[no_of_currentusers][qid].no_attempts = 0;
    }                
    no_of_currentusers++;   //incrementing no.of current users
    appdata_save(1);
    clearscr();
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
        wait_for_enter();
    }
    else{
        printf("passwords doesn't match please try again\n");
        take_password(id);
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
    appdata_read();
    printf("S.no~~~~~~~Account_type~~~~~~~~Username\n");
    for (int id = 0; id < no_of_currentusers; id++){
        if(userlist[id].type == 1)  printf("%d\t\tAdmin\t\t%s\n",id+1,userlist[id].username);
        else if(userlist[id].type == 0)  printf("%d\t\tUser\t\t%s\n",id+1,userlist[id].username);
    }
    printf("\nType a serial number to view about user\nType 0 to add a user\nType -1 to goback\n");
    int response = scanf_int(no_of_currentusers,-1);
    if (response == -1){
        return;
    }
    else if (response == 0){
        clearscr();
        add_user();
    }
    else{
        clearscr();
        view_user(response-1);

    }
}

void tag_user(int id){
    int tg= 0; // stores no.of available tags currently present.
    int tgu = 0; //stores no.of tags user doesn't have.
    for (int i = 0; i < max_tags; i++){
        if(strcmp(taglist[i], "")!= 0){
            if(userlist[id].tags[i] != 1){
            printf("%d\t\t\t%s\n",i+1,taglist[i]);
            tgu++;
            }
            tg++;
        }
    }
    if(tgu != 0){
        printf("\ntype the corresponding number to tag the user.\n");
        int res = scanf_int(tg,1);
        userlist[id].tags[res-1] = 1;
        printf("Tag added to the user succussefully.\nLike to add one more tag?y/n\n");
        char resp = takeyorno();
        if(resp == 'y'){
            tag_user(id);
        }
        appdata_save(1);
    }
    else{
        printf("User has been tagged by all tags available cannot add anymore type ENTER to continue\n");
        wait_for_enter();
    }
}

void view_tagged(int id){
    int num =0;
    printf("users with %s tag :\n\n",taglist[id]);
    for (int stu = 0; stu < no_of_currentusers; stu++){
        if(userlist[stu].tags[id]== 1){
            printf("%d\t\t%s\n",++num,userlist[stu].username);
        }
    }
    printf("\npress ENTER to go back\n");
    wait_for_enter();
    clearscr();
    manage_tags();
    
}

void delete_tag(int id,int num){ //num is no.of tags present currently.
    printf("Are you sure to delete tag-%s(y/n)\n",taglist[id]);
    char res = takeyorno();
    if(res == 'y'){
        for (int i = id; i < num-1; i++){
            strcpy(taglist[i],taglist[i+1]);   //need to change few more 
         strcpy(taglist[i],taglist[i+1]);   //need to change few more 
            strcpy(taglist[i],taglist[i+1]);   //need to change few more 
            for(int stu_id; stu_id < no_of_currentusers;stu_id++){
                userlist[stu_id].tags[i] == userlist[stu_id].tags[i+1];
            }
            for(int qid = 0; qid < quizlist.no_of_quizes;qid++){
                quizlist.quiz[qid].tag_ids[i] = quizlist.quiz[qid].tag_ids[i+1];
            }
        }
        appdata_save(1);
        taglist[num-1][0] = '\0';
        printf("deleted successfully type ENTER to go back\n");
        wait_for_enter();
        clearscr();
        manage_tags();
    }
    else{
        clearscr();
        manage_tags();
    }
}

void add_tag(int id){
    printf("Type the name of the tag you like to create\n");
    char response[13];
    smart_fgets(response,13,stdin);
    for (int i = 0; i < id; i++)
    {
        if (strcmp(response,taglist[i]) ==0){
            printf("A tag with %s name already exists would you like add another?(y/n)\n",response);
            char res = takeyorno();
            if (res == 'y'){
                add_tag(id);
                return;
            }
            else{
                clearscr();
                manage_tags();
                return;
            }
        }
    }    
    strcpy(taglist[id],response);
    printf("tag created press ENTER to continue\n"); 
    appdata_save(0);
    wait_for_enter();
    clearscr();
    manage_tags();
}

void manage_tags(){
    appdata_read();
    printf("list of tags :\n\n");
    int tg= 0;      // stores no.of available tags currently present.
    for (int id = 0; id < max_tags; id++){
        if(strcmp(taglist[id], "")!= 0){
            printf("%d\t\t\t%s\n",id+1,taglist[id]);
            tg++;
        }
        else if(id == 0)  {
            printf("No tags are present in the system\n");
            break;
            }
        else {
            break;
        }
    }
    printf("\nType corresponding serial number to view the members list bearing the tag\nType 0 to add a tag\nType -1 to go back\nType -2 delete a tag\n");
    int res = scanf_int(tg,-2);
    if(res == -1){
        return;
    }
    else if(res == -2){
        printf("Type the number of tag you wish to delete\n");
        int resp = scanf_int(tg,1);
        delete_tag(resp-1,tg);
    }
    else if(res == 0){
        if(tg < max_tags){
        clearscr();
        add_tag(tg);
        }
        else{
            printf("Can't add tags anymore limit(%d) reached\npress ENTER\n",max_tags);
            wait_for_enter();
            clearscr();
            manage_tags();
        }
    }
    else{
        clearscr();
        view_tagged(res-1);
    }
}

void welcomepage_admin(){
    int quit = 0;
    do{
    appdata_read();
    for (int quiz_id = 0; quiz_id < quizlist.no_of_quizes; quiz_id++){  //reads no_of students attempts from user files.
        int res = 0;
        for (int i = 0; i < no_of_currentusers; i++){
            if(quizes_attempted[i][quiz_id].no_attempts!=0){
            res++;
            }
        }
        quizlist.quiz[quiz_id].no_of_students_attempted = res;
    }
    appdata_save(0);
    clearscr();
    printf("Welcome %s!\n\n",currentuser.username);
    printf("What would you like to do?\n");
    printf("- See or manage quizzes (Enter q)\n");
    printf("- see or add users (a)\n");
    printf("- see or add tags(t)\n");
    printf("- Log out (Enter l)\n");
    printf("- Change password (Enter c)\n");
    printf("- Reload (Enter r)\n");

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
        quit = 1;
    }
    else if(x == 'a'){
        clearscr();
        view_userlist();
    }
    else if(x == 't'){
        clearscr();
        manage_tags();
    }
    else if(x == 'c'){
        change_password();
        quit = 1;
    }
    else if(x == 'r'){
        quit = 0;
    } 
    else{
        printf("Invalid response try again(y or q)\n");
    }
    }while (x!='l'&&x!='q'&&x!='t'&&x!= 'a'&& x!='c' && x != 'r');
    }while(quit==0);
}
