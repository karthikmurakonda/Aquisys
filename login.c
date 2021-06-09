#include "common.h"
#include "login.h"

/*int main()
{
   loginpage();
}*/

void login()
{
    login_status=0;
    char c, username[100], password[1000];
    int z = 0, id, i, type, status=1;
    int checku, checkp, checkid;
    printf("\n\n\t\t  Please Login,");
    printf("\n\t\t---------------------------");
    printf("\n\n\t\t  Username: ");
    scanf("%s", username);
    clearBuf();
    printf("\n\t\t  Password: ");
    scanf("%s", password);
    clearBuf();
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
                clearscr();
                switch (currentuser.type) {
                    case 0:
                        printf("Welcome %s!\n\n", currentuser.username);
                        student_nav();
                        break;
                    case 1:
                        welcomepage_admin();
                        break;
                    default:
                        printf("Error!\nInvalid user type\n");
                }
                return;
            }
            else if (checku == 0 && checkp != 0) 
            {
                printf("\n\n\n\t\t\tWRONG PASSWORD!");
                printf("\n\n\t\t\t\t  (Press 'r' to re-login)\n");
                do
                {
                    char res = getchar();
                    clearBuf();
                    if (res == 'r')
                    {
                        clearscr();
                        login();
                        return;
                    }
                    printf("Invalid response try again.\n");         
                }while(1);
            }
            else {
                printf("No such user found!\npress ENTER to go back\n");
                getchar();
                clearBuf();
                loginpage();
                return;
            }
        }
    }
}

void loginpage() {
    clearscr();
    printf("\n\n\n\t\tWelcome to Aquisys!\n");
    printf("\n\t\tPress l to login\n\t\tPress q to quit\n");
    char com;
    E:
    com=getchar();
    clearBuf();
    if (com=='l') {
        clearscr();
        login();
    }
    else if (com=='q') {
        return;
    }
    else {
        printf("\tInvalid option! Please try again,\n");
        goto E;
    }
}

void change_password(){
    char newpassword[100],conformpassword[100];
    int checkn, np;
    printf("\n\t\t\t\tEnter your new password\n");
    scanf("%s",newpassword);
    printf("\n\t\t\t\tConform your password\n");
    scanf("%s",conformpassword);
    clearBuf();
    checkn=strcmp(newpassword,conformpassword);
    if (checkn==0)
    {
        strcpy(userlist[currentuser.ID].password,newpassword);
        printf("\n\t\t\t\tpassword successfully changed");
        printf("\n\n\t\t\t\t  Press ENTER to login again\n");
        loginpage();
    } 
    else
    {
      printf("\n\t\t\tThe password entered is not matching\n\t\t\tpress ENTER to login");
      getchar();
      clearBuf();
      login();
      return;
    }
}