#include "common.h"
#include "time.h"

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

/*void check_cheating() {
    if(user[currentuser.ID][index][attempt].q_start[cheat]<user[currentuser.ID][index][attempt].q_start[cheat-1]){
    clearscr();
     //record submit quiz time
      take_time(index,attempt,"submit");
      clearscr();
      printf("-------------------------------------------\n                  %s               \n", quizlist.quiz[index].name);
      printf("-------------------------------------------\n");
      //Save data
      appdata_save();
      printf("Time out!!\n");
      printf("Quiz submitted!\nHit ENTER to proceed to main menu,\n");
      getchar();
    }
}*/