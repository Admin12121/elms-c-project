#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_REQUESTS 50
#define MAX_ATTEMPTS 3

void addBook();
void viewBooks();
void borrowBook(char username[]);
void displayWelcomePage();
void displayClock();
void registerUser();
void extendLicense();
void getCurrentDatePlusOneMonth(char *expiryDate);
void viewRequests();
void markBookAvailable();

typedef struct
{
    char title[100];
    int available;
    char borrowedBy[50];
    char dueDate[20];
} Book;

typedef struct
{
    char username[50];
    char password[50];
    int isAdmin;
    int isLocked;
    char licenseExpiry[20];
} User;

typedef struct
{
    char title[100];
    char requestedBy[50];
} BookRequest;

Book books[MAX_BOOKS];
User users[MAX_USERS];
BookRequest requests[MAX_REQUESTS];
int bookCount = 0;
int userCount = 0;
int requestCount = 0;

void getCurrentDatePlusOneMonth(char *expiryDate)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tm.tm_mon += 1;
    if (tm.tm_mon > 11)
    {
        tm.tm_mon = 0;
        tm.tm_year += 1;
    }
    strftime(expiryDate, 20, "%Y-%m-%d", &tm);
}

void registerUser()
{
    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    printf("Enter password: ");
    int i = 0;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b' && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else if (ch != '\b')
        {
            users[userCount].password[i++] = ch;
            printf("*");
        }
    }
    users[userCount].password[i] = '\0';
    printf("\n");
    users[userCount].isAdmin = 0;
    users[userCount].isLocked = 0;
    getCurrentDatePlusOneMonth(users[userCount].licenseExpiry);
    userCount++;

    printf("User registered successfully! License valid until: %s\n", users[userCount - 1].licenseExpiry);
}

void extendLicense()
{
    char username[50];
    printf("Enter username to extend license: ");
    scanf("%s", username);
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            getCurrentDatePlusOneMonth(users[i].licenseExpiry);

            printf("License extended for user %s until %s\n", username, users[i].licenseExpiry);
            return;
        }
    }
    printf("User not found!\n");
}

void displayWelcomePage()
{
    const char *logo =
        "\t\t\t      __...--~~~~~-._   _.-~~~~~--...__  \n"
        "\t\t\t    //               `V'               \\\\    \n"
        "\t\t\t   //                 |                 \\\\   \n"
        "\t\t\t  //__...--~~~~~~-._  |  _.-~~~~~~--...__\\\\  \n"
        "\t\t\t //__.....----~~~~._\\\\ | /_.~~~~----.....__\\\\ \n"
        "\t\t\t====================\\\\|//==================== \n"
        "\t\t\t                    `---`                    \n";

    printf("%s", logo);
}

void addBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        printf("Library is full!\n");
        return;
    }
    printf("Enter book title: ");
    scanf(" %[^\n]", books[bookCount].title);
    books[bookCount].available = 1;
    strcpy(books[bookCount].borrowedBy, "None");
    strcpy(books[bookCount].dueDate, "N/A");
    bookCount++;
    printf("Book added successfully!\n");
}

void viewBooks()
{
    printf("\nAvailable Books:\n");
    for (int i = 0; i < bookCount; i++)
    {
        printf("%s [%s]\n", books[i].title, books[i].available ? "?? Available" : "?? Borrowed");
    }
    printf("\nPress any key to continue...");
    _getch();
}

void borrowBook(char username[])
{
    char bookTitle[100];
    printf("Enter book title to borrow: ");
    scanf(" %[^\n]", bookTitle);

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, bookTitle) == 0 && books[i].available)
        {
            books[i].available = 0;
            strcpy(books[i].borrowedBy, username);
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            tm.tm_mday += 14; // Borrow for 2 weeks
            strftime(books[i].dueDate, 20, "%Y-%m-%d", &tm);
            printf("Book borrowed successfully! Due Date: %s\n", books[i].dueDate);
            return;
        }
    }
    printf("Book not available!\nDo you want to request it? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
        strcpy(requests[requestCount].title, bookTitle);
        strcpy(requests[requestCount].requestedBy, username);
        requestCount++;
        printf("Book requested successfully!\n");
    }
}

void viewRequests()
{
    printf("\nRequested Books:\n");
    for (int i = 0; i < requestCount; i++)
    {
        printf("%s requested by %s\n", requests[i].title, requests[i].requestedBy);
    }
    printf("\nPress any key to continue...");
    _getch();
}

void markBookAvailable()
{
    char bookTitle[100];
    printf("Enter book title to mark as available: ");
    scanf(" %[^\n]", bookTitle);

    for (int i = 0; i < bookCount; i++)
    {
        if (strcmp(books[i].title, bookTitle) == 0)
        {
            books[i].available = 1;
            strcpy(books[i].borrowedBy, "None");
            strcpy(books[i].dueDate, "N/A");
            printf("Book marked as available!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void displayClock()
{
    time_t t;
    struct tm *tm_info;
    char timeString[9];
    time(&t);
    tm_info = localtime(&t);
    strftime(timeString, 9, "%H:%M:%S", tm_info);
    printf("Current Time: %s\n", timeString);
}

void initializeDefaults()
{
    strcpy(books[bookCount].title, "The Great Gatsby");
    books[bookCount].available = 1;
    strcpy(books[bookCount].borrowedBy, "None");
    strcpy(books[bookCount].dueDate, "N/A");
    bookCount++;

    strcpy(books[bookCount].title, "1984");
    books[bookCount].available = 0;
    strcpy(books[bookCount].borrowedBy, "user1");
    strcpy(books[bookCount].dueDate, "2025-03-23");
    bookCount++;

    strcpy(books[bookCount].title, "To Kill a Mockingbird");
    books[bookCount].available = 1;
    strcpy(books[bookCount].borrowedBy, "None");
    strcpy(books[bookCount].dueDate, "N/A");
    bookCount++;

    strcpy(users[userCount].username, "admin");
    strcpy(users[userCount].password, "admin123");
    users[userCount].isAdmin = 1;
    users[userCount].isLocked = 0;
    getCurrentDatePlusOneMonth(users[userCount].licenseExpiry);
    userCount++;

    strcpy(users[userCount].username, "user1");
    strcpy(users[userCount].password, "password1");
    users[userCount].isAdmin = 0;
    users[userCount].isLocked = 0;
    getCurrentDatePlusOneMonth(users[userCount].licenseExpiry);
    userCount++;

    strcpy(users[userCount].username, "user2");
    strcpy(users[userCount].password, "password2");
    users[userCount].isAdmin = 0;
    users[userCount].isLocked = 0;
    getCurrentDatePlusOneMonth(users[userCount].licenseExpiry);
    userCount++;

    strcpy(requests[requestCount].title, "The Catcher in the Rye");
    strcpy(requests[requestCount].requestedBy, "user2");
    requestCount++;
}

int main()
{
    int choice;
    char username[50];
    char password[50];
    int loggedIn = 0;
    int isAdmin = 0;
    int attempts = 0;

    initializeDefaults();

    printf("\n\n");
    displayWelcomePage();
    displayClock();

    while (1)
    {
        if (!loggedIn)
        {
            printf("1. Register\n2. Login\n3. Exit\nEnter choice: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                registerUser();
            }
            else if (choice == 2)
            {
                printf("Enter username: ");
                scanf("%s", username);
                while (1)
                {
                    printf("Enter password: ");
                    int i = 0;
                    char ch;
                    while ((ch = _getch()) != '\r')
                    {
                        if (ch == '\b' && i > 0)
                        {
                            printf("\b \b");
                            i--;
                        }
                        else if (ch != '\b')
                        {
                            password[i++] = ch;
                            printf("*");
                        }
                    }
                    password[i] = '\0';
                    printf("\n");
                    int validUser = 0;
                    for (int i = 0; i < userCount; i++)
                    {
                        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
                        {
                            if (users[i].isLocked)
                            {
                                printf("Account is locked. Please contact admin.\n");
                                validUser = 1;
                                break;
                            }
                            loggedIn = 1;
                            isAdmin = users[i].isAdmin;
                            printf("License valid until: %s\n", users[i].licenseExpiry);
                            validUser = 1;
                            break;
                        }
                    }
                    if (validUser)
                        break;
                    else
                    {
                        printf("Invalid username or password! Please try again.\n");
                        attempts++;
                        if (attempts >= MAX_ATTEMPTS)
                        {
                            for (int i = 0; i < userCount; i++)
                            {
                                if (strcmp(users[i].username, username) == 0)
                                {
                                    users[i].isLocked = 1;
                                    printf("Account locked due to too many failed attempts. Please contact admin.\n");
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            system("cls");
            if (isAdmin)
            {
                printf("Admin Access Granted!\n1. Add Book\n2. View Books\n3. Extend License\n4. View Requests\n5. Mark Book Available\n6. Logout\nEnter choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    addBook();
                    break;
                case 2:
                    viewBooks();
                    break;
                case 3:
                    extendLicense();
                    break;
                case 4:
                    viewRequests();
                    break;
                case 5:
                    markBookAvailable();
                    break;
                case 6:
                    loggedIn = 0;
                    break;
                default:
                    printf("Invalid choice! Logging out...\n");
                    loggedIn = 0;
                    break;
                }
            }
            else
            {
                printf("User Access Granted!\n1. View Books\n2. Borrow Book\n3. Logout\nEnter choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    viewBooks();
                    break;
                case 2:
                    borrowBook(username);
                    break;
                case 3:
                    loggedIn = 0;
                    break;
                default:
                    printf("Invalid choice! Logging out...\n");
                    loggedIn = 0;
                    break;
                }
            }
        }
    }
    return 0;
}