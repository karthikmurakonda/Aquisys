# Aquisys

## Building
The code can be built using the following commands,

### With Make
make

The appdata can be cleaned using,
make clean-appdata

### Without Make
gcc admin.c analytics.c appdata.c login.c main.c nav.c quiz.c time.c -o run

### Prebuilt Executables
Linux: run the included “run” file
Windows: run the included  “run.exe” file

## Default Logins
| Username | Password | Account Type |
| -------- | -------- | ------------ |
|  admin   |    1     |    Admin     |
| student  |    1     |   Student    |

## Usage
### Giving Quiz
 1. Login to student account
 2. Choose to attempt a quiz
 3. Read instructions and start quiz

### View Quiz Analysis
 1. Login to student account
 2. Choose to analyse a quiz

### Making a Quiz
 1. Login to admin account
 2. Go to see or manage quizzes
 3. Choose create a quiz
 4. Follow on screen instructions
 5. Set availibility of quiz as desired

### View Student Responces
 1. Login to admin account
 2. Go to see or manage quizzes
 3. Choose option to view student responces

### Managing Users
 1. Login to admin account
 2. Choose see or add user option
 3. Choose desired option to manage users

## Source Code
Can be found at https://github.com/karthikmurakonda/Aquisys/!