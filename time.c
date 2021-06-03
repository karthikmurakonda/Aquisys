#include<stdio.h>
#include<time.h>
#include "common.h"
#include "time.h"
#include "quiz.h"
void record_timeq(int i, int index, int attempt,char s[15])
{
    if (s=="start")
    {
        time_t strt;
        time(&strt);
        user[currentuser.ID][index][attempt].q_start[i]=strt;
    }
    else if (s=="submit")
    {
        time_t submit;
        time(&submit);
        user[currentuser.ID][index][attempt].q_end[i]=submit;
    }
    
}

void take_time(int index,int attempt,char s[15]) // for quiz start and end
{   
    if (s=="start")
    {
        time_t strt;
        time(&strt);
         user[currentuser.ID][index][attempt].start_time = strt;
    }
    else if (s=="submit")
    {
        time_t submit;
        time(&submit);
        user[currentuser.ID][index][attempt].submittime = submit;
    }    
}

int time_autosubmit(int i,int index,int attempt)
{
    if ( (user[currentuser.ID][index][attempt].start_time-user[currentuser.ID][index][attempt].q_start[i])>=quizlist.quiz[index].max_time)
    {
        userlist[currentuser.ID].quizes_attempted[index].attempt[attempt].time_taken =(user[currentuser.ID][index][attempt].start_time-user[currentuser.ID][index][attempt].q_start[i]);
        return 0;
    }

    if ((user[currentuser.ID][index][attempt].start_time-user[currentuser.ID][index][attempt].q_start[i])<quizlist.quiz[index].max_time)
    {
        return 1;
    }
}