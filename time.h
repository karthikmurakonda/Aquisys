#define I 60
struct timetemp
{ 
    int submittime;
    int q_start[I];
    int q_end[I];
    int start_time;
};
#define maxx 500
#define indexx 60
#define attemptt 20
struct timetemp user[maxx][indexx][attemptt];

 