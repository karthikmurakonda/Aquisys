#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_users 10
#define max_quizes 10
#define max_answer_length 1000
#define max_question_length 2000
#define max_alternative_q 5
#define max_q_per_quiz 200
     
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
};                                      //quiz id is index of that quiz in quiz array.

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
   struct Quiz quiz[max_quizes];      //all 1000 elements are initialised but “no_of_quizes” decides what to call
};                              /*store quiz*/

extern struct Quizlist quizlist;
extern struct User userlist[max_users];
extern struct User currentuser;
extern int login_status;

void clearscr(void);
void clearBuf();
void smart_fgets(char *str, int n, FILE *stream);
int scanf_int();

void welcomepage_admin();

void appdata_save();
void appdata_read();

void loginpage(void);

void takeQuiz(int index);

void student_nav();

void aMatrix(int index, int attempt);