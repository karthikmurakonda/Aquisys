#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_users 10
#define max_quizes 10
#define max_answer_length 200
#define max_question_length 700
#define max_alternative_q 5
#define max_q_per_quiz 200
#define max_tags 5
     
struct Result {
    int attempted;
    int correct;
    int incorrect;
    int score;
};

struct Attempt {
    int q_bank[max_q_per_quiz][2];      //Stores randomised q_bank for this attempt, first index is Q. No. other is Q alternative
    int marks[max_q_per_quiz];          //Stores marks obtained for each answer (As per q_bank)
    struct Result result;
    int time_taken;                     //In seconds
};                                      //quiz id is index of that quiz in quiz array.

struct Quizes_attempted {
    int no_attempts;              //current no. of attempts of this quiz by user (1 to 5)
    struct Attempt attempt[5];    //attribute is attempt no. (0 to 4)
};

struct  User {
    char username[16];
    char password[16];
    int ID;                                           // Unique ID of each user
    int type;                                         // 0 (student) or 1 (admin)
    int tags[max_tags];                               // 0 or 1 at a tag id index. 1 -> user has that tag.
    struct Quizes_attempted quizes_attempted[max_quizes];    //attempts related to a quiz are stored at quiz’s Id.   
}; 

struct Response {
   char answer[max_answer_length];  //Answer given by user
   char status;                     //initialize it to ‘N’ when creating a quiz.
};                                  //'N' for new 'U' for unattempted 'S' for seen and 'A' for attempted

struct Question {
   char statement[2000];
   char solution[max_answer_length];      //Correct answer given by teacher
   int marks;
};

struct Quiz {
    char name[100];
    int no_of_questions;
    int no_of_students_attempted;                       //Number of students attempted in total
    int no_of_max_attempts;
    int attempt_list[max_users];                        //Stores number of times users have attempted the quiz (index is corresponding user ID)
    int max_time;                                           //In seconds
    int tag_ids[max_tags];       //if 1 in i th place suggests that quiz has a tag with id i. By default a quiz has no tags unless specifies. a quiz with tag_ids array with all 0s mean any user can attempt it.
};        /*nst to quizlist*/

struct Quizlist {
   int no_of_quizes;            //current available no.of quizzes
   struct Quiz quiz[max_quizes];      //all 1000 elements are initialised but “no_of_quizes” decides what to call
};                              /*store quiz*/

extern struct Quizlist quizlist;
extern struct User userlist[max_users];
extern struct User currentuser;
extern int login_status;
extern struct Question question[max_quizes][max_q_per_quiz][max_alternative_q];   //Questions and their alternatives
extern struct Response response[max_users][max_quizes][max_q_per_quiz][max_alternative_q];
extern int no_of_currentusers;  //no.of users currently present in database.
extern char taglist[max_tags][13]; //tag has id. each tag has max 12 characters.all will be initailized to null character while user enters for the first time
extern time_t start, current, last;

// Global functions from project.h
void clearscr(void);
void clearBuf();
void smart_fgets(char *str, int n, FILE *stream);
int scanf_int();

// Global functions from admin.c
void welcomepage_admin();

// Global functions from appdata.c
void appdata_save();
void appdata_read();

// Global functions from login.c
void loginpage(void);

// Global functions from quiz.c
void takeQuiz(int index);

// Global functions from nav.c
void student_nav();

// Global functions from analysis.c
void aMatrix(int index, int attempt);

// Global functions from login.c
void change_password();

// Global functions from time.c
void record_time(int a);
int autosubmit(int index);
int cheating();
