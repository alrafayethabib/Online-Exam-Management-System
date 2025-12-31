#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h> 

int TIME_UP = 0;
int EXAM_RUNNING = 0;

//--------------------------------------------------------
//             QUESTION STRUCTURE DEFINITION 
//--------------------------------------------------------
struct Question {
    char q[200];
    char o1[100];
    char o2[100];
    char o3[100];
    char o4[100];
    int correct;
};

//--------------------------------------------------------
//             FUNCTION PROTOTYPES 
//--------------------------------------------------------

//-------ADMIN SECTION ------------

void admin_register();
void admin_login();
void admin_menu();
void admin_add_teacher();
void admin_remove_teacher();
void view_teacher_list();
void admin_view_students();
void view_questions();
void remove_question();
void remove_student();
void admin_view_questions();
void student_submit_feedback();
void admin_send_notice();

//--------TEACHER SECTION ----------

void teacher_register();
void teacher_login();
void teacher_menu();
void add_question();
void add_student();

//--------STUDENT SECTION ------------

void student_register();
void student_login();
void student_menu();
void take_exam();

//----------All Roles SECTION ----------

void save_result(char user[], int score, int total);
void view_all_results();
void student_view_my_results();
void student_submit_feedback();
void view_all_feedback();
void view_notice();
void view_ranking_simple();

char CURRENT_USER[50] = "";

//--------------------------------------------------------
//             ADMIN REGISTRATION 
//--------------------------------------------------------

void admin_register()
{
    char user[50], pass[50], confirm[50];

    getchar();
    printf("\nEnter Admin Username: ");
    fgets(user, 50, stdin);
    user[strcspn(user, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    printf("Confirm Password: ");
    fgets(confirm, 50, stdin);
    confirm[strcspn(confirm, "\n")] = '\0';

    if(strcmp(pass, confirm) != 0)
    {
        printf("Password mismatch!\n");
        return;
    }

    FILE *fp = fopen("admin.txt", "a");
    if (fp == NULL) {
        printf("Error opening admin file!\n");
        return;
    }

    fprintf(fp, "%s %s\n", user, pass);
    fclose(fp);

    printf("Admin Registered Successfully!\n");
}


//--------------------------------------------------------
//              TEACHER REGISTRATION 
//--------------------------------------------------------

void teacher_register() {
    char user[50], pass[50], confirm[50];

    getchar();
    printf("\nEnter Teacher Username: ");
    fgets(user, 50, stdin);
    user[strcspn(user, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    printf("Confirm Password: ");
    fgets(confirm, 50, stdin);
    confirm[strcspn(confirm, "\n")] = '\0';

    if(strcmp(pass, confirm) != 0) {
        printf("Password does not match!\n");
        return;
    }


    FILE *fp = fopen("teacher.txt", "a");
    if (fp == NULL) {
        printf("Error opening teacher file!\n");
        return;
    }
    fprintf(fp, "%s %s\n", user, pass);
    fclose(fp);

    printf("Teacher Registered Successfully!\n");
}

//--------------------------------------------------------
//              STUDENT REGISTRATION 
//--------------------------------------------------------

void student_register() {
    char username[50], pass[50], confirm[50];

    getchar();
    printf("Enter student username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    printf("Confirm password: ");
    fgets(confirm, 50, stdin);
    confirm[strcspn(confirm, "\n")] = '\0';

    if(strcmp(pass, confirm) != 0) {
        printf("Password does not match!\n");
        return;
    }

    FILE *fp = fopen("student.txt", "a");
    if (fp == NULL) {
        printf("Error opening student file!\n");
        return;
    }
    fprintf(fp, "%s %s\n", username, pass);
    fclose(fp);

    printf("Student registered successfully!\n");
}

//--------------------------------------------------------
//              ADMIN LOGIN (SUNBI)
//--------------------------------------------------------

void admin_login()
{
    char user[50], pass[50], fuser[50], fpass[50];
    int found = 0;

    getchar();
    printf("\nEnter Admin Username: ");
    fgets(user, 50, stdin); 
    user[strcspn(user, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    FILE *fp = fopen("admin.txt", "r");
    if (fp == NULL) {
        printf("No admin registered! Please register first.\n");
        return;
    }

    while (fscanf(fp, "%s %s", fuser, fpass) == 2) {
        if (strcmp(user, fuser) == 0 && strcmp(pass, fpass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found) {
        printf("Admin Login Successful!\n");
        admin_menu();
    } else {
        printf("Invalid admin username or password!\n");
    }
}


//--------------------------------------------------------
//              TEACHER LOGIN 
//--------------------------------------------------------

void teacher_login() {
    char user[50], pass[50], fuser[50], fpass[50];
    int found = 0;

    getchar();
    printf("\nEnter Teacher Username: ");
    fgets(user, 50, stdin);
    user[strcspn(user, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    FILE *fp = fopen("teacher.txt", "r");
    if(fp == NULL) {
        printf("No Teacher Data Found! Please Register first.\n");
        return;
    }

    while(fscanf(fp, "%s %s", fuser, fpass) == 2) {
        if(strcmp(user, fuser) == 0 && strcmp(pass, fpass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if(found) {
        printf("Login Successful!\n");
        teacher_menu();
    } else {
        printf("Invalid Username or Password!\n");
    }
}

//-------------------------------------------------------
//              STUDENT LOGIN 
//--------------------------------------------------------

void student_login() {
    char username[50], pass[50], fileUser[50], filePass[50];
    int found = 0;

    getchar();
    printf("Enter student username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    FILE *fp = fopen("student.txt", "r");
    if(fp == NULL) {
        printf("No student data found! Please Register first.\n");
        return;
    }

    while(fscanf(fp, "%s %s", fileUser, filePass) == 2) {
        if(strcmp(username, fileUser) == 0 && strcmp(pass, filePass) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if(found) {
        printf("Login successful!\n");
        strcpy(CURRENT_USER, username);
        student_menu();
    } else {
        printf("Invalid username or password!\n");
    }
}

//----------------------------------------
//              ADMIN MENU 
//----------------------------------------


void admin_menu() {
    int ch;
    

    while(1) {

        printf("\n========== ADMIN MENU ==========\n");
        printf("1. Add Teacher\n");
        printf("2. Remove Teacher\n");
        printf("3. View Teacher List\n");
        printf("4. View Student List\n");
        printf("5. Remove Student\n");
        printf("6. View All Questions\n");
        printf("7. Remove Question\n");
        printf("8. View Student Results\n");
        printf("9. View Feedback\n");
        printf("10. Send Notice (ALL Students)\n");
        printf("11. View Notice\n");
        printf("12. View Ranking\n");
        printf("13. Logout\n");
        printf("================================\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        getchar();

        switch(ch) {
            case 1:
                admin_add_teacher();
                break;
            case 2:
                admin_remove_teacher();
                break;
            case 3:
                view_teacher_list();
                break;
            case 4:
                admin_view_students();
                break;
            case 5:
                remove_student();
                break;
            case 6:
                admin_view_questions();
                break;
            case 7:
                remove_question();
                break;
            case 8:
                view_all_results();
                break;
            case 9:
                view_all_feedback();
                break;
            case 10:
                admin_send_notice();
                break;
            case 11:
                view_notice();
                break;
            case 12:
                view_ranking_simple();
                break;
            case 13:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}
//--------------------------------------------------------
//              TEACHER MENU 
//--------------------------------------------------------

void teacher_menu() {
    
    int c;
   
    while(1) {
        
        printf("\n========== TEACHER MENU ==========\n");
        printf("1. Add Question\n");
        printf("2. Remove Question\n");
        printf("3. View All Questions\n");
        printf("4. Add Student\n");
        printf("5. Remove Student\n");
        printf("6. View Ranking\n");
        printf("7. View All Results\n");
        printf("8. View All Feedback\n");
        printf("9. View Notice\n");
        printf("10. Logout\n");
        printf("==================================\n");
        printf("Enter Choice: ");
        scanf("%d", &c);
        getchar();


        switch(c) {

            case 1:
                add_question();
                break;

            case 2:
                remove_question();
                break;

            case 3:
                view_questions();
                break;

            case 4:
                add_student();
                break;

            case 5:
                remove_student();
                break;

            case 6: 
                view_ranking_simple(); 
                break;

            case 7: 
                view_all_results(); 
                break;

            case 8: 
                view_all_feedback(); 
                break;

            case 9: 
                view_notice(); 
                break;

            case 10:
                return;

            default:
                printf("\nInvalid Choice!\n");
        }

    }
}

//--------------------------------------------------------
//              STUDENT MENU 
//--------------------------------------------------------

void student_menu() {
    
    int op;

    while(1) {
        printf("1. Take Exam\n");
        printf("2. Retake Exam\n");
        printf("3. View Ranking\n");
        printf("4. View Notice\n");
        printf("5. Submit Feedback\n");
        printf("6. View All Results\n");
        printf("7. View All Feedback\n");
        printf("8. View My Results\n");
        printf("9. Logout\n");

        printf("Enter option: ");
        scanf("%d", &op);
        getchar();   


        switch(op) {

            case 1:
                take_exam();
                break;

            case 2:
                printf("\n--- Retaking Exam ---\n");
                take_exam();
                break;


            case 3:
                view_ranking_simple();
                break;

            case 4:
                view_notice();
                break;

            case 5:
                student_submit_feedback();
                break;

            case 6:
                view_all_results();
                break;

            case 7:
                view_all_feedback();
                break;

            case 8:
                student_view_my_results();
                break;

            case 9:
                return;

            default:
                printf("Invalid option!\n");
        }
    }
}

//--------------------------------------------------------
//              TEACHER ADD QUESTION 
//--------------------------------------------------------

void add_question() {
    FILE *fp = fopen("questions.txt", "a");

    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char q[200], o1[100], o2[100], o3[100], o4[100];
    int correct;

    getchar();
    printf("\nEnter Question: ");
    fgets(q, 200, stdin);
    q[strcspn(q, "\n")] = '\0';

    printf("Option 1: ");
    fgets(o1, 100, stdin);
    o1[strcspn(o1, "\n")] = '\0';

    printf("Option 2: ");
    fgets(o2, 100, stdin);
    o2[strcspn(o2, "\n")] = '\0';

    printf("Option 3: ");
    fgets(o3, 100, stdin);
    o3[strcspn(o3, "\n")] = '\0';

    printf("Option 4: ");
    fgets(o4, 100, stdin);
    o4[strcspn(o4, "\n")] = '\0';

    printf("Correct Option (1-4): ");
    scanf("%d", &correct);

    fprintf(fp, "%s;%s;%s;%s;%s;%d\n", q, o1, o2, o3, o4, correct);
    fclose(fp);

    printf("Question Added Successfully!\n");
}

//--------------------------------------------------------
//           ADMIN VIEW TEACHER LIST 
//--------------------------------------------------------

void view_teacher_list()
{
    FILE *fp = fopen("teacher.txt", "r");
    char user[50], pass[50];
    int i = 1;

    if(fp == NULL)
    {
        printf("No teachers registered!\n");
        return;
    }

    printf("\n------ Teacher List ------\n");
    while(fscanf(fp, "%s %s", user, pass) == 2)
    {
        printf("%d. %s\n", i++, user);
    }

    fclose(fp);
}

//--------------------------------------------------------
//           ADMIN VIEW STUDENT LIST 
//--------------------------------------------------------

void admin_view_students()
{
    FILE *fp = fopen("student.txt", "r");
    char user[50], pass[50];
    int count = 1;

    if(fp == NULL)
    {
        printf("No students found!\n");
        return;
    }

    printf("\n----- STUDENT LIST -----\n");

    while(fscanf(fp, "%s %s", user, pass) == 2)
    {
        printf("%d. %s\n", count, user);
        count++;
    }

    fclose(fp);
}

//--------------------------------------------------------
//        ADMIN VIEW QUESTION LIST 
//--------------------------------------------------------

void admin_view_questions()
{
    FILE *fp = fopen("questions.txt", "r");
    struct Question Q;
    char line[600];
    int i = 1;

    if(fp == NULL)
    {
        printf("No questions found!\n");
        return;
    }

    printf("\n======= QUESTION BANK (ADMIN) =======\n");

    while(fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%199[^;];%99[^;];%99[^;];%99[^;];%99[^;];%d",
               Q.q, Q.o1, Q.o2, Q.o3, Q.o4, &Q.correct);

        printf("\nQ%d: %s\n", i, Q.q);
        printf("1. %s\n", Q.o1);
        printf("2. %s\n", Q.o2);
        printf("3. %s\n", Q.o3);
        printf("4. %s\n", Q.o4);

        i++;
    }

    fclose(fp);

    if(i == 1)
        printf("No questions available!\n");
}


//--------------------------------------------------------
//              VIEW ALL QUESTIONS 
//--------------------------------------------------------

void view_questions() {
    FILE *fp = fopen("questions.txt", "r");
    char line[600];
    int count = 1;
    struct Question Q;

    if(fp == NULL) {
        printf("No Questions Found!\n");
        return;
    }

    printf("\n=========== ALL QUESTIONS ===========\n");

    while(fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;];%d",
               Q.q, Q.o1, Q.o2, Q.o3, Q.o4, &Q.correct);

        printf("%d. %s (Ans: %d)\n", count, Q.q, Q.correct);
        count++;
    }

    fclose(fp);

    if(count == 1)
        printf("No questions available!\n");
}


//--------------------------------------------------------
//              REMOVE QUESTION 
//--------------------------------------------------------

void remove_question() {
    FILE *fp = fopen("questions.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL) {
        printf("No Questions Found!\n");
        return;
    }

    int del, lineNum = 1;
    char buffer[600];

    printf("Enter Question Number to Delete: ");
    scanf("%d", &del);

    while(fgets(buffer, sizeof(buffer), fp)) {
        if(lineNum != del)
            fputs(buffer, temp);
        lineNum++;
    }

    fclose(fp);
    fclose(temp);

    remove("questions.txt");
    rename("temp.txt", "questions.txt");

    printf("Question Removed Successfully!\n");
}


//--------------------------------------------------------
//              ADMIN ADD TEACHER 
//--------------------------------------------------------

void admin_add_teacher()
{
    char user[50], pass[50];

    getchar();
    printf("Enter Teacher Username: ");
    fgets(user, 50, stdin);
    user[strcspn(user, "\n")] = '\0';

    printf("Enter Teacher Password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    FILE *fp = fopen("teacher.txt", "a");
    if (fp == NULL) {
        printf("Error opening teacher file!\n");
        return;
    }
    fprintf(fp, "%s %s\n", user, pass);
    fclose(fp);

    printf("Teacher Added Successfully!\n");
}

//--------------------------------------------------------
//              ADMIN REMOVE TEACHER 
//--------------------------------------------------------

void admin_remove_teacher()
{
    char target[50], user[50], pass[50];

    getchar();
    printf("Enter Teacher Username to Remove: ");
    fgets(target, 50, stdin);
    target[strcspn(target, "\n")] = '\0';

    FILE *fp = fopen("teacher.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;

    while(fscanf(fp, "%s %s", user, pass) == 2)
    {
        if(strcmp(user, target) != 0)
        {
            fprintf(temp, "%s %s\n", user, pass);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("teacher.txt");
    rename("temp.txt", "teacher.txt");

    if(found)
        printf("Teacher Removed Successfully!\n");
    else
        printf("Teacher Not Found!\n");
}


//--------------------------------------------------------
//              ADD STUDENT 
//--------------------------------------------------------

void add_student() {
    char user[50], pass[50];

    getchar();
    printf("Enter Student Username: ");
    fgets(user, 50, stdin);
    user[strcspn(user, "\n")] = '\0';

    printf("Enter Student Password: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = '\0';

    FILE *fp = fopen("student.txt", "a");
    if (fp == NULL) {
        printf("Error opening student file!\n");
        return;
    }
    fprintf(fp, "%s %s\n", user, pass);
    fclose(fp);

    printf("Student Added Successfully!\n");
}


//--------------------------------------------------------
//              REMOVE STUDENT 
//--------------------------------------------------------

void remove_student() {
    FILE *fp = fopen("student.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if(fp == NULL) {
        printf("No Students Found!\n");
        return;
    }

    char user[50], pass[50], target[50];

    getchar();
    printf("Enter Student Username to Remove: ");
    fgets(target, 50, stdin);
    target[strcspn(target, "\n")] = '\0';

    while(fscanf(fp, "%s %s", user, pass) == 2) {
        if(strcmp(user, target) != 0)
            fprintf(temp, "%s %s\n", user, pass);
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    printf("Student Removed Successfully!\n");
}


//--------------------------------------------------------
//               TIMER 
//--------------------------------------------------------

void* timer_thread(void *arg) {
    int seconds = *(int*)arg;

    while (seconds >= 0 && EXAM_RUNNING) {

        int min = seconds / 60;
        int sec = seconds % 60;

        printf("\r[TIMER] Time left: %02d:%02d ", min, sec);
        fflush(stdout);


        sleep(1);
        seconds--;

        if (seconds < 0) {
            TIME_UP = 1;
            EXAM_RUNNING = 0;
            printf("\n\n Time is up!\n");
            break;
        }
    }

    return NULL;
}


//--------------------------------------------------------
//              TAKE EXAM 
//--------------------------------------------------------

void take_exam() {

    TIME_UP = 0;
    EXAM_RUNNING = 1;

    int duration = 120;
    pthread_t tid;

    pthread_create(&tid, NULL, timer_thread, &duration);

    FILE *fp = fopen("questions.txt", "r");
    if(fp == NULL) {
    
    EXAM_RUNNING = 0;

    pthread_join(tid, NULL);
    printf("No questions available!\n");
    return;
}


    struct Question Q;
    char line[600];
    int score = 0, total = 0;

    while (fgets(line, sizeof(line), fp) && EXAM_RUNNING) {

        sscanf(line, "%199[^;];%99[^;];%99[^;];%99[^;];%99[^;];%d",
               Q.q, Q.o1, Q.o2, Q.o3, Q.o4, &Q.correct);

        total++;

        printf("\n\nQ%d: %s\n", total, Q.q);
        printf("1. %s\n", Q.o1);
        printf("2. %s\n", Q.o2);
        printf("3. %s\n", Q.o3);
        printf("4. %s\n", Q.o4);
        printf("5. Skip Question\n");

        printf("\n\nEnter your answer (1-5):\n> ");
        fflush(stdout);


        int choice;
        if (TIME_UP) 
        break;

        scanf("%d", &choice);
        getchar();                          
        printf("\n");                     

        if (TIME_UP) break;

        if(choice == 5) {
            printf("Skipped!\n");
            continue;
        }

        if(choice == Q.correct) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong! Correct answer was: %d\n", Q.correct);
        }
    }

    fclose(fp);
    EXAM_RUNNING = 0;

    pthread_join(tid, NULL);

    printf("\n============================\n");
    printf(" Exam Finished!\n Score: %d / %d\n", score, total);
    printf("============================\n");

save_result(CURRENT_USER, score, total);
}   


//--------------------------------------------------------
//              SAVE RESULT 
//--------------------------------------------------------

void save_result(char user[], int score, int total)
{
    FILE *fp = fopen("results.txt", "a");
    if(fp == NULL) {
        printf("Error: cannot open results.txt\n");
        return;
    }
    fprintf(fp, "%s %d %d\n", user, score, total);
    fclose(fp);
}


//--------------------------------------------------------
//             ATS  VIEW ALL RESULTS 
//--------------------------------------------------------

void view_all_results()
{
    FILE *fp = fopen("results.txt", "r");
    char user[50];
    int score, total;

    if(fp == NULL)
    {
        printf("No results found!\n");
        return;
    }

    printf("\n--- ALL RESULTS ---\n");

    while(fscanf(fp, "%s %d %d", user, &score, &total) != EOF)
    {
        printf("%s - %d/%d\n", user, score, total);
    }

    fclose(fp);
}


//--------------------------------------------------------
//        STUDENT VIEW MY RESULTS 
//--------------------------------------------------------

void student_view_my_results()
{
    FILE *fp = fopen("results.txt", "r");
    char user[50];
    int score, total;
    int found = 0;

    if(fp == NULL)
    {
        printf("No results found!\n");
        return;
    }

    printf("\n--- MY RESULTS (%s) ---\n", CURRENT_USER);

    while(fscanf(fp, "%s %d %d", user, &score, &total) != EOF)
    {
        if(strcmp(user, CURRENT_USER) == 0)
        {
            printf("Score: %d / %d\n", score, total);
            found = 1;
        }
    }

    fclose(fp);

    if(!found) printf("No records for you yet.\n");
}


//--------------------------------------------------------
//         STUDENT SUBMIT FEEDBACK 
//--------------------------------------------------------

void student_submit_feedback()
{
    FILE *fp = fopen("feedback.txt", "a");
    char msg[300];

    if(fp == NULL){
        printf("Cannot open feedback file!\n");
        return;
    }

    getchar();
    printf("Enter your feedback: ");
    fgets(msg, 300, stdin);
    msg[strcspn(msg, "\n")] = '\0';

    fprintf(fp, "%s: %s\n", CURRENT_USER, msg);
    fclose(fp);

    printf("Feedback submitted successfully!\n");
}

//--------------------------------------------------------
//                ATS VIEW FEEDBACK
//--------------------------------------------------------

void view_all_feedback()
{
    FILE *fp = fopen("feedback.txt", "r");
    char line[400];

    if(fp == NULL)
    {
        printf("No feedback found.\n");
        return;
    }

    printf("\n--- ALL FEEDBACK ---\n");

    while(fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}


//--------------------------------------------------------
//                 ADMIN SENT NOTICE
//--------------------------------------------------------

void admin_send_notice()
{
    FILE *fp = fopen("notice.txt", "w"); 
    char msg[300];

    getchar();
    printf("Enter notice (single line): ");
    fgets(msg, 300, stdin);
    msg[strcspn(msg, "\n")] = '\0';

    if(strlen(msg) == 0) {
        printf("Empty notice cancelled.\n");
        if(fp) fclose(fp);
        return;
    }

    if(fp) {
        fprintf(fp, "%s\n", msg);
        fclose(fp);
        printf("Notice sent to ALL students!\n");
    } else {
        printf("Error: cannot open notice.txt\n");
    }
}


//--------------------------------------------------------
//                 TS VIEW NOTICE 
//--------------------------------------------------------

void view_notice()
{
    FILE *fp = fopen("notice.txt", "r");
    char line[300];

    if(fp == NULL)
    {
        printf("No notice available.\n");
        return;
    }

    printf("\n--- NOTICE ---\n");

    while(fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}


//--------------------------------------------------------
//                ATS  VIEW RANKING 
//--------------------------------------------------------

void view_ranking_simple()
{
    FILE *fp = fopen("results.txt", "r");
    char user[50];
    int score, total;

    char users[500][50];
    int highest[500];
    int count = 0;

    if(fp == NULL)
    {
        printf("No ranking data.\n");
        return;
    }

    while(fscanf(fp, "%s %d %d", user, &score, &total) != EOF)
    {
        int found = -1;
        for(int i=0;i<count;i++){
            if(strcmp(users[i], user) == 0){ found = i; break;}
        }

        if(found == -1){
            strcpy(users[count], user);
            highest[count] = score;
            count++;
        } else {
            if(score > highest[found]) highest[found] = score;
        }
    }
    fclose(fp);

    printf("\n--- RANKING (highest score) ---\n");
    for(int i=0;i<count;i++){
        printf("%d. %s - %d\n", i+1, users[i], highest[i]);
    }
}

//--------------------------------------------------------
//                ATS MAIN FUNCTION 
//--------------------------------------------------------

int main() {
    int choice;

    while(1) {
        printf("\n===== EXAM MANAGEMENT SYSTEM =====\n");
        printf("1. Admin Register\n");
        printf("2. Admin Login\n");
        printf("3. Teacher Register\n");
        printf("4. Teacher Login\n");
        printf("5. Student Register\n");
        printf("6. Student Login\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                admin_register();
                break;

            case 2:
                admin_login();
                break;

            case 3:
                teacher_register();
                break;

            case 4:
                teacher_login();
                break;

            case 5:
                student_register();
                break;

            case 6:
                student_login();
                break;

            case 7:
                printf("Exiting system...\n");
                return 0;

            default:
                printf("Invalid option! Try again.\n");
                break;
        }
    }

    return 0;
}


