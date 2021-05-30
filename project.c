#include "common.h"
#include "project.h"
#include "quiz.h"
#include "admin.h"


int main() {
    currentuser.ID = 0;
    welcomepage_admin();
    takeQuiz(0);
    return 0;
}