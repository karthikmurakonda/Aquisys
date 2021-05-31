#include "common.h"
#include "project.h"
#include "quiz.h"
#include "admin.h"
#include "file.h"
#include "login.h"

int main() {
    appdata_read();

    loginpage();
    switch (currentuser.type) {
        case 0:
            takeQuiz(0);
            break;
        case 1:
            welcomepage_admin();
            break;
        default:
            printf("Error!\nInvalid user type\n");
    }

    //Make User
    /*strcpy(userlist[1].username,"admin");
    strcpy(userlist[1].password,"password");
    userlist[1].type=1;*/

    appdata_save();
    return 0;
}
