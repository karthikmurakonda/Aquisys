#include "common.h"
#include "project.h"
#include "quiz.h"
#include "admin.h"
#include "file.h"

int main() {
    currentuser.ID = 0;
    appdata_read();
    printf("Choose what to do:\n1: Admin Page\n2: Quiz\n");
    int com = scanf_int(1,2);
    if (com==1) {
        welcomepage_admin();
    }
    else if (com==2) {
        currentuser.ID=0;
        takeQuiz(0);
    }
    appdata_save();
    return 0;
}