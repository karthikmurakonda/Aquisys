#include "common.h"
#include "login.h"

/*int main()
{
   homepage();
}*/

void login() {
    login_status=0;
    char c, username[100], password[1000];
    int z = 0, id, i, type, status=1;
    int checku, checkp, checkid;
    printf("\n\n\t\t\t\tWELCOME TO LOGIN");
    printf("\n\t\t\t\t---------------------------");
    printf("\n\n\t\t\t\t  ENTER USERNAME: ");
    scanf("%s", username);
    printf("\n\n\t\t\t\t  ENTER PASSWORD: ");
    scanf("%s", password);
    for (i = 0; i < max_users; i++) {
        if (userlist[i].username != 0) {
            checku = strcmp(username, userlist[i].username);
            checkp = strcmp(password, userlist[i].password);
            if (checku == 0 && checkp == 0) {
                clearscr();
                currentuser.ID = i;
                strcpy(currentuser.username, userlist[i].username);
                strcpy(currentuser.password, userlist[i].password);
                currentuser.type=userlist[i].type;
                status=0;
                login_status=1;
                clearscr();
                break;
            } else if (checku == 0 && checkp != 0) {
                printf("\n\n\n\t\t\tWRONG PASSWORD");
                printf("\n\n\t\t\t\t  (Press 'Y' to re-login)");
                if (getchar() == 'y' || getchar() == 'Y')
                    login();
            }
        }
        else {
            break;
        }
    }
    if (status) {
        printf("No such user found!\n");
    }
}

void loginpage() {
    int n;
    clearscr();
    printf("\n\n\n\n\n\t\t\t\tWELCOME TO QUIZ");
    printf("\n\t\t\t\t__*_");
    printf("\n\n\n\n\t\t\tPress Enter to proceed...!!\n");
    if (getchar() == 13)
        clearscr();
    clearscr();
    login();
    clearBuf();
    if (login_status) {
        switch (currentuser.type) {
            case 0:
                printf("Welcome to the quiz portal!\n\n");
                student_nav();
                break;
            case 1:
                welcomepage_admin();
                break;
            default:
                printf("Error!\nInvalid user type\n");
        }
    }
}