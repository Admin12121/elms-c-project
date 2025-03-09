#include <stdio.h>
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

int main(){

    
    return 0;
}