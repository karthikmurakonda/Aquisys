#include "project.h"

int main() {
    appdata_read();

    loginpage();

    //Make User
    /*strcpy(userlist[0].username,"s");
    strcpy(userlist[0].password,"1");
    userlist[0].type=0;
    strcpy(userlist[1].username,"a");
    strcpy(userlist[1].password,"1");
    userlist[1].type=1;*/

    appdata_save();
    return 0;
}
