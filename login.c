#include "common.h"
#include "login.h"

/*int main()
{
   homepage();
}*/

void login() {
    char c, username[100], password[1000];
    int z = 0, id, i, type, status=1;
    int checku, checkp, checkid;
    printf("\n\n\t\t\t\tWELCOME TO LOGIN");
    printf("\n\t\t\t\t---------------------------");
    printf("\n\n\t\t\t\t  ENTER USERNAME: ");
    scanf("%s", username);
    clearBuf();
    printf("\n\n\t\t\t\t  ENTER PASSWORD: ");
    scanf("%s", password);
    clearBuf();
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
                clearscr();
                return;
            }
            else if (checku == 0 && checkp != 0) {
                printf("\n\n\n\t\t\tWRONG PASSWORD");
                printf("\n\n\t\t\t\t  (Press 'Y' to re-login)\n");
                do{
                char res = getchar();
                clearBuf();
                if (res == 'y' || res == 'Y'){
                    login();
                    return;
                }
                printf("Invalid response try again.\n");         
                }while(1);
            }
        }
    }
        printf("No such user found!\npress ENTER to go back\n");
        getchar();
        clearBuf();
        loginpage();
        return;
    }


void loginpage() {
    int n;
    clearscr();
    printf("\n\n\n\n\n\t\t\t\tWELCOME TO QUIZ");
    printf("\n\t\t\t\t__*_");
    printf("\n\n\n\n\t\t\tPress Enter to proceed...!!\n");
    if (getchar() == 13)
        clearscr();
    do{
        printf("\n\n\n\t\t\t1. LOGIN\t\t2. EXIT");
    printf("\n\n\n\t\t\t\tENTER YOUR CHOICE: ");
    scanf("%d", & n);
    switch (n) {
    case 1:
        clearscr();
        login();
        return;
    case 2:
        clearscr();
        exit(1);
        return;
    default:
        printf("\n\n\t\t\tPress Enter to re-Enter the choice");
        if (getchar() == 13)
            clearscr();
    }
    }while(1);
}
