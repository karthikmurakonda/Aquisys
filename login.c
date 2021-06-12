#include "common.h"
#include "login.h"

/*int main()
{
   loginpage();
}*/

int login(){
    appdata_read();
    char c, username[16], password[16];
    int z = 0, id, i, type, status=1;
    int checku, checkp, checkid;
    E:
    printf("\n\n\t\t  Please Login,");
    printf("\n\t\t---------------------------");
    printf("\n\n\t\t  Username: ");
    smart_fgets(username, 16, stdin);
    printf("\n\t\t  Password: ");
    smart_fgets(password, 16, stdin);
    for (i = 0; i < max_users; i++) 
    {
        if (userlist[i].username != 0) 
        {
            checku = strcmp(username, userlist[i].username);
            checkp = strcmp(password, userlist[i].password);
            if (checku == 0 && checkp == 0) 
            {
                currentuser.ID = i;
                strcpy(currentuser.username, userlist[i].username);
                strcpy(currentuser.password, userlist[i].password);
                currentuser.type=userlist[i].type;
                status=0;
                login_status=1;
                clearscr();
                return 1;
            }
            else if (checku == 0 && checkp != 0) 
            {
                printf("\n\n\n\t\t\t%sWrong Password!%s", red, normal);
                printf("\n\n\t\t(Press ENTER to re-login)\n");
                wait_for_enter();
                clearscr();
                goto E;      
            }
        }
    }
    printf("%sNo such user found!%s\npress ENTER to go back\n", red, normal);
    wait_for_enter();
    loginpage();
    return 0;
}

void loginpage() {
    clearscr();
    printf("\n\n\n\t\tWelcome to %sAquisys%s!\n",cyan,normal);
    printf("\n\t\tPress l to login\n\t\tPress q to quit\n");
    char com;
    E:
    com=getchar();
    clearBuf();
    if (com=='l') {
        clearscr();
        if (login()) {
            switch (currentuser.type) {
                case 0:
                    printf("Welcome %s!\n\n", currentuser.username);
                    student_nav();
                    break;
                case 1:
                    welcomepage_admin();
                    break;
                default:
                    printf("%sError!\nInvalid user type%s\n", red, normal);
            }
        }
    }
    else if (com=='q') {
        return;
    }
    else {
        printf("\t%sInvalid option! Please try again,%s\n", red, normal);
        goto E;
    }
}

void change_password(){
    char newpassword[100],conformpassword[100];
    int checkn, np;
    E:
    printf("\n\t\t\t\tEnter your new password\n\t\t\t\t");
    scanf("%s",newpassword);
    printf("\n\t\t\t\tConform your password\n\t\t\t\t");
    scanf("%s",conformpassword);
    clearBuf();
    checkn=strcmp(newpassword,conformpassword);
    if (checkn==0)
    {
        strcpy(userlist[currentuser.ID].password,newpassword);
        printf("\n\t\t\t\tpassword successfully changed");
        printf("\n\n\t\t\t\t  Press ENTER to login again\n");
        appdata_save(0);
        loginpage();
    } 
    else
    {
      printf("\n\t\t\t%sThe password entered is not matching\n\t\t\tpress ENTER to try again,%s", red, normal);
      wait_for_enter();
      goto E;
    }
}