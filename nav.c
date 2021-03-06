#include "common.h"

int is_visible(int quiz_id){                 //returns 1 if visible,0 if not.
    int num = 0;
    for (int i = 0; i < max_tags; i++){
        if(quizlist.quiz[quiz_id].tag_ids[i] == 1){     //checks if quiz has a tag.
            if(userlist[currentuser.ID].tags[i] == 1){  //checks if user has the same tag.
                return 1;
            }
            num++;
        }
    }
    if(num == 0){
        return 1;   //case where quiz has no tags and available for all.
    }
    else{
        return 0;
    }
}

void student_nav() {
    appdata_read();
    int arr[max_quizes];
    int quiznum= 0;
    for (int  i = 0; i < quizlist.no_of_quizes; i++) {
        if(is_visible(i)==1 && quizlist.quiz[i].visible>0){
            printf("%d : %s\t\t Attempts-   %d/%d\n",quiznum+1, quizlist.quiz[i].name, quizes_attempted[currentuser.ID][i].no_attempts, quizlist.quiz[i].no_of_max_attempts);
            arr[quiznum] = i;
            quiznum++;
        }
    }
    if (quiznum==0) {
        printf("Sorry no quizes have been assigned yet! Try again later,\n\n");
    }
    
    printf("\nWhat would you like to do?\n");
    if (quiznum!=0) {
        printf("- Attempt a quiz (Enter q)\n");
        printf("- View analysis of a quiz (Enter a)\n");
    }
    printf("- Log out (Enter l)\n");
    printf("- Change password (Enter c)\n");
    printf("- Reload page (Enter r)\n");
    char com;
    E:
    scanf("%c", &com);
    clearBuf();
    if (com=='q' && quiznum!=0) {
        printf("\nPlease choose a quiz to give (enter the quiz number):\n");
        int n = scanf_int(quiznum,1)-1;
        clearscr();
        view_instructions(arr[n]);
        appdata_save(0);
        clearscr();
        student_nav();
    }
    else if (com=='a' && quiznum!=0) {
        printf("\nPlease choose a quiz to analyse (enter the quiz number):\n");
        int q = scanf_int(quiznum,1)-1;
        if (quizes_attempted[currentuser.ID][arr[q]].no_attempts!=0) {
            printf("\nWhich attempt number would you like to analyse?:\n");
            int a = scanf_int(quizes_attempted[currentuser.ID][arr[q]].no_attempts,1)-1;
            clearscr();
            aMatrix(arr[q],a);
        }
        else {
            printf("No attempts available to analyse! Press ENTER to go back,\n");
            wait_for_enter();
            clearscr();
            student_nav();
        }
    }
    else if (com=='l') {
        loginpage();
    }
    else if (com=='c') {
        clearscr();
        change_password();
    }
    else if (com=='r') {
        clearscr();
        student_nav();
    }
    else {
        printf("\n%sInvalid input! Please try again,%s\n", red, normal);
        goto E;
    }
}
