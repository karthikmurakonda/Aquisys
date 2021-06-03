#include "common.h"
#include "login.h"

/*int main()
{
   loginpage();
}*/

void login()
{
    login_status=0;
    char c, username[100], password[1000],newpassword[100],conformpassword[100];
    int z = 0, id, i, type, status=1,np;
    int checku, checkp, checkid,checkn;
    printf("\n\n\t\t\t\tWELCOME TO LOGIN");
    printf("\n\t\t\t\t---------------------------");
    printf("\n\n\t\t\t\t  ENTER USERNAME: ");
    scanf("%s", username);
    clearBuf();
    printf("\n\n\t\t\t\t  ENTER PASSWORD: ");
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
                clearscr();
                printf("\n\t\tpress 1 to change password\n\t\tpress 2 for navigation page");
                scanf("%d",&np);
                switch(np) 
                {
                    case 1:
                      printf("\n\t\t\t\tEnter your new password\n");
                      scanf("%s ",newpassword);
                      printf("\n\t\t\t\tConform your password\n");
                      scanf("%s ",conformpassword);
                      checkn=strcmp(newpassword,conformpassword);
                      if (checkn==0)
                      {
                          strcpy(userlist[i].password,newpassword);
                          printf("\n\t\t\t\tpassword successfully changed");
                          printf("\n\n\t\t\t\t  Press 'Y' to login again\n\t\t\t\tpress 'C' to continue");
                          do
                          {
                              char res = getchar();
                              clearBuf();
                              if (res == 'y' || res == 'Y')
                              {
                                  login();
                                  return;
                              }
                              else if (res=='C'|| res == 'c')
                              {
                                  currentuser.ID = i;
                                  strcpy(currentuser.username, userlist[i].username);
                                  strcpy(currentuser.password, userlist[i].password);
                                  currentuser.type=userlist[i].type;
                                  status=0;
                                  login_status=1;
                                  clearscr();
                                  return;
                              }
                              
                         }while(1);
                      } 
                      else
                      {
                          printf("\n\t\t\tThe password entered is not matching\n\t\t\tpress ENTER to login");
                          getchar();
                          login();
                          return;
                      }
                    break;
                    case 2:
                      clearscr();
                      currentuser.ID = i;
                      strcpy(currentuser.username, userlist[i].username);
                      strcpy(currentuser.password, userlist[i].password);
                      currentuser.type=userlist[i].type;
                      status=0;
                      login_status=1;
                      clearscr();
                      return;
                      break;
                 }
            return;
            }
            else if (checku == 0 && checkp != 0) 
            {
                printf("\n\n\n\t\t\tWRONG PASSWORD");
                printf("\n\n\t\t\t\t  (Press 'Y' to re-login)\n");
                do
                {
                    char res = getchar();
                    clearBuf();
                    if (res == 'y' || res == 'Y')
                    {
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
    clearscr();
    printf("\n\n\n\t\tWELCOME TO QUIZ!\n");
    printf("\n\t\tPress l to login\n\t\tPress q to quit\n");
    char com;
    E:
    com=getchar();
    clearBuf();
    if (com=='l') {
        clearscr();
        login();
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
    else if (com=='q') {
        return;
    }
    else {
        printf("\tInvalid option! Please try again,\n");
        goto E;
    }
}
