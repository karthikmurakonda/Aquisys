#include "common.h"
#include "admin.h"
#include "login.h"

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
    res = scanf_int(max_users*max_alternative_q-1,0);
  	if(res >= 0 && res <max_users*max_alternative_q){
          //abhishek's function
    }
    else printf("Not a valid response try agian\n");
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

void admin_quizdetails(int n){
    clearscr();
    printf("Quiz name : %s\n",quizlist.quiz[n].name);
    printf("No.of questions %d\n",quizlist.quiz[n].no_of_questions);
    printf("No.of maximum attempts : %d\n",quizlist.quiz[n].no_of_max_attempts);
    printf("Type\n r : to view student responses\n m : To change distrubution of marks\n e : To add questions/edit existing questions \n p : to preview whole question paper\n c : to change maximum number of attempts\n 0 : to go back to quizzes list\n");
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
        showqlist_admin();  // goes to quizlist
        }
    else if (x=='q'){
       loginpage();
    }
    else{
        printf("Invalid response try again(y or q)\n");
    }
    }while (x!='y'&&x!='q');

}
