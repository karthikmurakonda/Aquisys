#include "common.h"

void record_time(int a) // for quiz start and end
{   
    if (a==0)
    {
        time(&start);
        last=start;
    }
    else if (a=1)
    {
        time(&current);
    }
}

int autosubmit(int index)
{
    if ((current-start)>=quizlist.quiz[index].max_time)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int cheating() {
    if (current<last) {
        return 1;
    }
    else {
        return 0;
    }
}