#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Student {
    char Name[40];
    char FatherName[30];
    char Class[10];
    int Roll;
    char Address[100];
    char PhoneNumber[15];
    char Date[12];
} s;

struct User {
    char username[30];
    char password[30];
};

FILE *fp;
long sz = sizeof(s);

// Function Prototypes
void input();
void display();
void Search();
void Modify();
void Delete();
void Sort();
void Search_By_Roll();
void Search_By_Name();
void createAccount();
int login();
void forgetPassword();

int main() {
    int ch;
    int loggedIn = 0;

    FILE *userFile = fopen("users.dat", "ab");
    if (userFile == NULL) {
        printf("Error opening user file!\n");
        return 1;
    }
    fclose(userFile);

    while (!loggedIn) {
        system("cls");
        printf(" < ----------- School Management ----------- >  \n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("3. Forget Password\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar();

        switch (ch) {
            case 0:
                exit(0);
            case 1:
                loggedIn = login();
                break;
            case 2:
                createAccount();
                break;
            case 3:
                forgetPassword();
                break;
            default:
                printf("Invalid Choice\n");
        }
        if (!loggedIn) {
            printf("Press Enter to continue...");
            getchar();
        }
    }

    while (1) {
        system("cls");
        printf(" < ----------- college Management ----------- >  \n");
        printf("1. Take Admission\n");
        printf("2. Student Records\n");
        printf("3. Search\n");
        printf("4. Modify\n");
        printf("5. Delete\n");
        printf("6. Sort By Roll\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar();

        switch (ch) {
            case 0:
                exit(0);
            case 1:
                input();
                break;
            case 2:
                display();
                break;
            case 3:
                Search();
                break;
            case 4:
                Modify();
                break;
            case 5:
                Delete();
                break;
            case 6:
                Sort();
                break;
            default:
                printf("Invalid Choice\n");
        }
        printf("Press Enter to continue...");
        getchar();
    }
    return 0;
}

void createAccount() {
    struct User user;
    printf("Enter a username: ");
    scanf("%s", user.username);
    printf("Enter a password: ");
    scanf("%s", user.password);

    FILE *userFile = fopen("users.dat", "ab");
    if (userFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&user, sizeof(struct User), 1, userFile);
    fclose(userFile);
    printf("Account created successfully!\n");
}

int login() {
    struct User fileUser;
    char username[30], password[30];
    int found = 0;

    printf("\n< ----------- LOGIN REQUIRED ----------- >\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *userFile = fopen("users.dat", "rb");
    if (userFile == NULL) {
        printf("No users found! Please create an account first.\n");
        return 0;
    }

    while (fread(&fileUser, sizeof(struct User), 1, userFile) == 1) {
        if (strcmp(username, fileUser.username) == 0) {
            found = 1;
            if (strcmp(password, fileUser.password) == 0) {
                printf("Login Successful!\n");
                fclose(userFile);
                return 1;
            } else {
                printf("Invalid Password. Please try again.\n");
                fclose(userFile);
                return 0;
            }
        }
    }

    fclose(userFile);
    if (!found) {
        printf("Invalid Username. Please try again.\n");
    }
    return 0;
}
void forgetPassword() {
    struct User fileUser;
    char username[30];
    int found = 0;
    printf("Enter your username: ");
    scanf("%s", username);

    FILE *userFile = fopen("users.dat", "rb");
    if (userFile == NULL) {
        printf("No users found!\n");
        return;
    }

    while (fread(&fileUser, sizeof(struct User), 1, userFile) == 1) {
        if (strcmp(username, fileUser.username) == 0) {
            found = 1;
            printf("Your password is: %s\n", fileUser.password);
            break;
        }
    }
    fclose(userFile);
    if (!found) printf("Username not found.\n");
}

void input() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.Date, myDate);

    fp = fopen("Student.txt", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Clear the input buffer before using fgets() after scanf()
    printf("Enter the Name : ");
    fflush(stdin);
    fgets(s.Name, sizeof(s.Name), stdin);
    s.Name[strcspn(s.Name, "\n")] = 0;  // Debug statement

    printf("Enter Father's Name: ");
    fgets(s.FatherName, sizeof(s.FatherName), stdin);
    s.FatherName[strcspn(s.FatherName, "\n")] = 0;  

    printf("Enter Class: ");
    fgets(s.Class, sizeof(s.Class), stdin);
    s.Class[strcspn(s.Class, "\n")] = 0;

    printf("Enter Roll Number: ");
    scanf("%d", &s.Roll);
    getchar();  // Clear the input buffer after scanf() for Roll number

    printf("Enter Address: ");
    fgets(s.Address, sizeof(s.Address), stdin);
    s.Address[strcspn(s.Address, "\n")] = 0;

    printf("Enter Phone Number: ");
    fgets(s.PhoneNumber, sizeof(s.PhoneNumber), stdin);
    s.PhoneNumber[strcspn(s.PhoneNumber, "\n")] = 0;

    fwrite(&s, sz, 1, fp);
    printf("Record Saved Successfully.\n");
    fclose(fp);
}

void display() {
    fp = fopen("Student.txt", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n< -------- Student Records -------- >\n");
    printf("%-20s %-20s %-10s %-10s %-30s %-15s %s\n", 
           "Name", "Father's Name", "Class", "Roll No", "Address", "Phone", "Date");

    while (fread(&s, sz, 1, fp) == 1) {
        printf("%-20s %-20s %-10s %-10d %-30s %-15s %s\n", 
               s.Name, s.FatherName, s.Class, s.Roll, s.Address, s.PhoneNumber, s.Date);
    }
    fclose(fp);
}

void Modify() {
    int Roll, found = 0;
    printf("Enter Roll To Modify: ");
    scanf("%d", &Roll);

    fp = fopen("Student.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sz, 1, fp) == 1) {
        if (Roll == s.Roll) {
            found = 1;
            printf("Enter New Name: ");
            getchar();
            fgets(s.Name, sizeof(s.Name), stdin);
            s.Name[strcspn(s.Name, "\n")] = 0;

            fseek(fp, -sz, SEEK_CUR);
            fwrite(&s, sz, 1, fp);
            fclose(fp);
            printf("Record Modified Successfully\n");
            return;
        }
    }
    fclose(fp);
    printf("Record Not Found\n");
}

void Delete() {
    int Roll;
    printf("Enter Roll To Delete: ");
    scanf("%d", &Roll);

    FILE *ft = fopen("Temp.txt", "wb");
    fp = fopen("Student.txt", "rb");

    if (fp == NULL || ft == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sz, 1, fp) == 1) {
        if (s.Roll != Roll) fwrite(&s, sz, 1, ft);
    }
    fclose(fp);
    fclose(ft);

    remove("Student.txt");
    rename("Temp.txt", "Student.txt");

    printf("Record Deleted Successfully.\n");
}
// Add `Modify()`, `Delete()`, `Search()`, `Sort()` and other functions (same as in previous code)
void Search() {
    int ch;
    while (1) {
        system("cls");
        printf("< ---------- Search ---------- > \n");
        printf("1 . Search By Roll \n");
        printf("2 . Search By Name \n");
        printf("0 . Back To Main Menu\n");
        printf("Enter Your Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                return;
            case 1:
                Search_By_Roll();
                break;
            case 2:
                Search_By_Name();
                break;
            default:
                printf("Invalid Choice\n");
        }
    }
}

void Search_By_Roll() {
    int Roll, found = 0;
    printf("Enter Roll To Search: ");
    scanf("%d", &Roll);

    fp = fopen("Student.txt", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sz, 1, fp) == 1) {
        if (Roll == s.Roll) {
            found = 1;
            printf("%-20s %-20s %-10s %-10d %-30s %-15s %s\n", s.Name, s.FatherName, s.Class, s.Roll, s.Address, s.PhoneNumber, s.Date);
            break;
        }
    }
    fclose(fp);
    if (!found) printf("Record Not Found\n");
}

void Search_By_Name() {
    char Name[30];
    int found = 0;
    printf("Enter Name To Search: ");
    fflush(stdin);
    fgets(Name, sizeof(Name), stdin);
    Name[strcspn(Name, "\n")] = 0;

    fp = fopen("Student.txt", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sz, 1, fp) == 1) {
        if (strcasecmp(Name, s.Name) == 0) {
            found = 1;
            printf("%-20s %-20s %-10s %-10d %-30s %-15s %s\n", s.Name, s.FatherName, s.Class, s.Roll, s.Address, s.PhoneNumber, s.Date);
            break;
        }
    }
    fclose(fp);
    if (!found) printf("Record Not Found\n");
}
void Sort() {
    int count = 0, i, j;
    struct Student s1[100], temp;

    system("cls");
    printf("< ------------ Sorted By Roll ----------- >\n");
    printf("%-20s %-20s %-10s %-10s %-30s %-15s %s\n", "Name", "Father's Name", "Class", "Roll No", "Address", "Phone", "Date");

    fp = fopen("Student.txt", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    // Read all records into array
    while (fread(&s1[count], sizeof(struct Student), 1, fp) == 1) {
        count++;
    }
    fclose(fp);

    // Sort records by Roll Number
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (s1[i].Roll > s1[j].Roll) {
                temp = s1[i];
                s1[i] = s1[j];
                s1[j] = temp;
            }
        }
    }

    // Display sorted records
    for (i = 0; i < count; i++) {
        printf("%-20s %-20s %-10s %-10d %-30s %-15s %s\n",
               s1[i].Name, s1[i].FatherName, s1[i].Class, s1[i].Roll, s1[i].Address, s1[i].PhoneNumber, s1[i].Date);
    }
}
