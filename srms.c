#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

/* ---------- DATA TYPES ---------- */
typedef struct {
    char username[20];
    char password[20];
    char role[10];
} User;

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

/* ---------- GLOBALS ---------- */
Student students[MAX_STUDENTS];
int studentCount = 0;

/* ---------- FILE HANDLING FUNCTIONS ---------- */
void loadStudentsFromFile() {
    FILE *fp = fopen("students.txt", "r");
    if (!fp) {
        printf("No student file found! Starting fresh.\n");
        return;
    }

    studentCount = 0;
    while (fscanf(fp, "%d %s %f", 
                  &students[studentCount].id, 
                  students[studentCount].name, 
                  &students[studentCount].marks) == 3) 
    {
        studentCount++;
    }

    fclose(fp);
    printf("Student data loaded from file.\n");
}

void saveStudentsToFile() {
    FILE *fp = fopen("students.txt", "w");
    if (!fp) {
        printf("Error saving student file!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(fp, "%d %s %.2f\n",
                students[i].id,
                students[i].name,
                students[i].marks);
    }

    fclose(fp);
}

/* ---------- STUDENT FUNCTIONS ---------- */
void displayStudents() {
    if (studentCount == 0) {
        printf("\nNo students available.\n");
        return;
    }

    printf("\nID\tNAME\t\tMARKS\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%s\t\t%.2f\n", 
                students[i].id, 
                students[i].name, 
                students[i].marks);
    }
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent list is full.\n");
        return;
    }

    Student s;
    printf("\nEnter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    students[studentCount++] = s;
    saveStudentsToFile();

    printf("\nStudent added and saved successfully.\n");
}

int findStudentIndexById(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void searchStudent() {
    int id;
    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    int idx = findStudentIndexById(id);
    if (idx == -1) {
        printf("\nStudent not found.\n");
    } else {
        printf("\nStudent found:\n");
        printf("ID: %d\nName: %s\nMarks: %.2f\n",
               students[idx].id, 
               students[idx].name, 
               students[idx].marks);
    }
}

void updateStudent() {
    int id;
    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    int idx = findStudentIndexById(id);
    if (idx == -1) {
        printf("\nStudent not found.\n");
        return;
    }

    printf("Enter new Name: ");
    scanf("%s", students[idx].name);
    printf("Enter new Marks: ");
    scanf("%f", &students[idx].marks);

    saveStudentsToFile();
    printf("\nStudent updated and saved successfully.\n");
}

void deleteStudent() {
    int id;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    int idx = findStudentIndexById(id);
    if (idx == -1) {
        printf("\nStudent not found.\n");
        return;
    }

    for (int i = idx; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;

    saveStudentsToFile();
    printf("\nStudent deleted and file updated.\n");
}

/* ---------- MENUS FOR ROLES ---------- */
void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("\nLogging out...\n"); break;
            default: printf("\nInvalid choice.\n");
        }
    } while (choice != 6);
}

void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
            case 4: printf("\nLogging out...\n"); break;
            default: printf("\nInvalid choice.\n");
        }
    } while (choice != 4);
}

void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: printf("\nLogging out...\n"); break;
            default: printf("\nInvalid choice.\n");
        }
    } while (choice != 3);
}

void guestMenu() {
    int choice;
    do {
        printf("\n===== GUEST MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: printf("\nLogging out...\n"); break;
            default: printf("\nInvalid choice.\n");
        }
    } while (choice != 2);
}

/* ---------- LOGIN ---------- */
int login(User users[], int n, User *loggedIn) {
    char uname[20], pass[20];

    printf("\n===== Login =====\n");
    printf("Username: ");
    scanf("%s", uname);
    printf("Password: ");
    scanf("%s", pass);

    for (int i = 0; i < n; i++) {
        if (strcmp(uname, users[i].username) == 0 &&
            strcmp(pass, users[i].password) == 0) {
            *loggedIn = users[i];
            return 1;
        }
    }
    return 0;
}

/* ---------- MAIN ---------- */
int main() {
    User users[] = {
        {"admin", "admin5678", "ADMIN"},
        {"staff", "staff5656", "STAFF"},
        {"guest", "guest666", "GUEST"},
        {"user",  "user555",  "USER"}
    };
    int userCount = 4;

    /* Load students from file */
    loadStudentsFromFile();

    while (1) {
        User current;

        if (!login(users, userCount, &current)) {
            printf("\nInvalid username or password. Try again.\n");
            continue;
        }

        printf("\nLogged in as %s (%s)\n", 
               current.username, 
               current.role);

        if (strcmp(current.role, "ADMIN") == 0)
            adminMenu();
        else if (strcmp(current.role, "STAFF") == 0)
            staffMenu();
        else if (strcmp(current.role, "GUEST") == 0)
            guestMenu();
        else
            userMenu();
    }

    return 0;
}