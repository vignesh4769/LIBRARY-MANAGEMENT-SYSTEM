#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 100
#define MAX_NAME_LENGTH 50


struct Book {
    char title[MAX_NAME_LENGTH];
    int copies;
    int id;
    char author[MAX_NAME_LENGTH];
    int publicationYear;
};

struct Member {
    char name[MAX_NAME_LENGTH];
    int id;
};

struct Loan {
    int bookId;
    int memberId;
    char lendDate[MAX_NAME_LENGTH];
    char returnDate[MAX_NAME_LENGTH];
};

struct Book libraryBooks[MAX_BOOKS];
struct Member libraryMembers[MAX_MEMBERS];
struct Loan libraryLoans[MAX_BOOKS];
int totalBooks = 0;
int totalMembers = 0;
int totalLoans = 0;


void addBook() {
	printf("\n");
    if (totalBooks >= MAX_BOOKS) {
    	printf("\033[0;31m");
        printf("\t\tLibrary is full. Cannot add more books.\n");
        return;
    }

    struct Book newBook;

    printf("Enter the book title: ");
    scanf("%s", newBook.title);

    printf("Enter the number of copies: ");
    scanf("%d", &newBook.copies);

    printf("Enter the book ID: ");
    scanf("%d", &newBook.id);

    printf("Enter the author: ");
    scanf("%s", newBook.author);

    printf("Enter the publication year: ");
    scanf("%d", &newBook.publicationYear);

    libraryBooks[totalBooks++] = newBook;
    
    printf("\033[0;32m");
    printf("Book added successfully.\n");
}

void removeBook() {
	printf("\n");
	
    int bookId;
    int bookIndex = -1;

    printf("Enter the book ID: ");
    scanf("%d", &bookId);

    for (int i = 0; i < totalBooks; i++) {
        if (libraryBooks[i].id == bookId) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
    	printf("\033[0;31m");
        printf("Book not found.\n");
        return;
    }

    for (int i = bookIndex; i < totalBooks - 1; i++) {
        libraryBooks[i] = libraryBooks[i + 1];
    }

    totalBooks--;
    printf("\033[0;32m");
    printf("Book removed successfully.\n");
}

void showBooks() {
	printf("\n");
    if (totalBooks == 0) {
    	printf("\033[0;37m");
        printf("No books available in the library.\n");
        return;
    }

    printf("Books in the library:\n");
    for (int i = 0; i < totalBooks; i++) {
    	printf("\033[0;37m");
        printf("Title: %s\n", libraryBooks[i].title);
        printf("Number of copies: %d\n", libraryBooks[i].copies);
        printf("Book ID: %d\n", libraryBooks[i].id);
        printf("Author: %s\n", libraryBooks[i].author);
        printf("Publication year: %d\n\n", libraryBooks[i].publicationYear);
    }
}

void addMember() {
	printf("\n");
    if (totalMembers >= MAX_MEMBERS) {
        printf("\033[0;31m");
		printf("Library member capacity reached. Cannot add more members.\n");
        return;
    }

    struct Member newMember;

    printf("Enter the member name: ");
    scanf("%s", newMember.name);

    printf("Enter the member ID: ");
    scanf("%d", &newMember.id);

    libraryMembers[totalMembers++] = newMember;
    printf("\033[0;32m");
	printf("Member added successfully.\n");
}
void removeMember() {
	printf("\n");
    int memberId;
    int memberIndex = -1;

    printf("Enter the member ID: ");
    scanf("%d", &memberId);

    for (int i = 0; i < totalMembers; i++) {
        if (libraryMembers[i].id == memberId) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
    	printf("\033[0;31m");
        printf("Member not found.\n");
        return;
    }

    for (int i = memberIndex; i < totalMembers - 1; i++) {
        libraryMembers[i] = libraryMembers[i + 1];
    }

    totalMembers--;
    printf("\033[0;32m");
    printf("Member removed successfully.\n");
}

void showMembers() {
	printf("\n");
    if (totalMembers == 0) {
    	printf("\033[0;37m");
        printf("No members in the library.\n");
        return;
    }

    printf("Members in the library:\n");
    for (int i = 0; i < totalMembers; i++) {
    	printf("\033[0;37m");
        printf("Name: %s\n", libraryMembers[i].name);
        printf("ID: %d\n\n", libraryMembers[i].id);
    }
}

void lendBook() {
	printf("\n");
    int bookId, memberId;
    int bookIndex = -1;
    int memberIndex = -1;

    printf("Enter the book ID: ");
    scanf("%d", &bookId);

    printf("Enter the member ID: ");
    scanf("%d", &memberId);

    for (int i = 0; i < totalBooks; i++) {
        if (libraryBooks[i].id == bookId) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
    	printf("\033[0;31m");
        printf("Book not found.\n");
        return;
    }

    for (int i = 0; i < totalMembers; i++) {
        if (libraryMembers[i].id == memberId) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
    	printf("\033[0;31m");
        printf("Member not found.\n");
        return;
    }

    if (libraryBooks[bookIndex].copies <= 0) {
    	printf("\033[0;31m");
        printf("No copies of the book available.\n");
        return;
    }

    if (totalLoans >= MAX_BOOKS) {
    	printf("\033[0;31m");
        printf("Library loan capacity reached. Cannot lend more books.\n");
        return;
    }

    struct Loan newLoan;

    newLoan.bookId = bookId;
    newLoan.memberId = memberId;

    printf("Enter the lending date: ");
    scanf("%s", newLoan.lendDate);

    // Calculate the return date (15 days after the lending date)
   
    strcpy(newLoan.returnDate, newLoan.lendDate);
    // (Assuming date format: dd-mm-yyyy)
    int day, month, year;
    sscanf(newLoan.returnDate, "%d-%d-%d", &day, &month, &year);
    day += 15;
    if (day > 31) {
        day -= 31;
        month++;
        if (month > 12) {
            month -= 12;
            year++;
        }
    }
    sprintf(newLoan.returnDate, "%02d-%02d-%04d", day, month, year);

    libraryLoans[totalLoans++] = newLoan;

    libraryBooks[bookIndex].copies--;

    printf("\033[0;32m");
    printf("Book lent successfully.\n");
}

void returnBook() {
	printf("\n");
    int bookId, memberId;
    int loanIndex = -1;
    int bookIndex = -1;
    int memberIndex = -1;

    printf("Enter the book ID: ");
    scanf("%d", &bookId);

    printf("Enter the member ID: ");
    scanf("%d", &memberId);

    for (int i = 0; i < totalLoans; i++) {
        if (libraryLoans[i].bookId == bookId && libraryLoans[i].memberId == memberId) {
            loanIndex = i;
            break;
        }
    }

    if (loanIndex == -1) {
    	printf("\033[0;31m");
        printf("No matching loan record found.\n");
        return;
    }

    for (int i = 0; i < totalBooks; i++) {
        if (libraryBooks[i].id == bookId) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
    	printf("\033[0;31m");
        printf("Book not found.\n");
        return;
    }

    for (int i = 0; i < totalMembers; i++) {
        if (libraryMembers[i].id == memberId) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
    	printf("\033[0;31m");
        printf("Member not found.\n");
        return;
    }

    libraryBooks[bookIndex].copies++;

    for (int i = loanIndex; i < totalLoans - 1; i++) {
        libraryLoans[i] = libraryLoans[i + 1];
    }

    totalLoans--;
    printf("\033[0;32m");
    printf("Book returned successfully.\n");
}

void showLoans() {
	printf("\n");
    if (totalLoans == 0) {
    	printf("\033[0;37m");
        printf("No books currently on loan.\n");
        return;
    }
    printf("\033[0;37m");
    printf("Books currently on loan:\n");
    for (int i = 0; i < totalLoans; i++) {
		int bookId = libraryLoans[i].bookId;
        int memberId = libraryLoans[i].memberId;

        int bookIndex = -1;
        int memberIndex = -1;

        for (int j = 0; j < totalBooks; j++) {
            if (libraryBooks[j].id == bookId) {
                bookIndex = j;
                break;
            }
        }

        for (int j = 0; j < totalMembers; j++) {
            if (libraryMembers[j].id == memberId) {
                memberIndex = j;
                break;
            }
        }
        printf("\033[0;37m");
        printf("Book title: %s\n", libraryBooks[bookIndex].title);
		printf("\033[0;37m");
		printf("Member name: %s\n", libraryMembers[memberIndex].name);
        printf("\033[0;37m");
		printf("Member ID : %d\n ",libraryMembers[memberIndex].id);
        printf("\033[0;37m");
		printf("Lending date: %s\n", libraryLoans[i].lendDate);
        printf("\033[0;37m");
		printf("Return date: %s\n\n", libraryLoans[i].returnDate);
    }
}



int main() {
    
	int choice;

    struct Book book1 = {"Introduction to Algorithms", 3, 1, "Ronald L. Rivesten", 2014};
    struct Book book2 = {"Algorithms Unlocked", 5, 2, "Thomas H. Cormen", 2004};
    struct Book book3 = {"The Algorithm Design Manual", 8, 3, "Steven S. Skiena", 2010};
	struct Book book4 = {"Data Structures and Algorithms Made Easy", 6, 4, "Narasimha Karumanchi", 2015};
    libraryBooks[totalBooks++] = book1;
    libraryBooks[totalBooks++] = book2;
    libraryBooks[totalBooks++] = book3;
    libraryBooks[totalBooks++] = book4;

    struct Member member1 = {"SANTHOSH", 182};
    struct Member member2 = {"SIDDHU", 189};
    struct Member member3 = {"MAANYA", 188};
    struct Member member4 = {"THARUN", 216};
    struct Member member5 = {"VARSHINI", 242};
    struct Member member6 = {"HARSHA", 236};
    libraryMembers[totalMembers++] = member1;
    libraryMembers[totalMembers++] = member2;
    libraryMembers[totalMembers++] = member3;
    libraryMembers[totalMembers++] = member4;
    libraryMembers[totalMembers++] = member5;
    libraryMembers[totalMembers++] = member6;

    do {
    	printf("\033[0;36m");
        printf("Library Management System\n");
        printf("1. Add book\n");
        printf("2. Remove book\n");
        printf("3. Show books\n");
        printf("4. Add member\n");
        printf("5. Remove member\n");
        printf("6. Show members\n");
        printf("7. Lend book\n");
        printf("8. Return book\n");
        printf("9. Show loans\n");
        printf("0. Exit\n\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                showBooks();
                break;
            case 4:
                addMember();
                break;
            case 5:
            	removeMember();
				break; 
            case 6:
                showMembers();
                break; 
            case 7:
                lendBook();
                break;
            case 8:
                returnBook();
                break;
            case 9:
                showLoans();
                break;
            case 0:
                printf("Exiting program. see you again..!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");	
        }

        printf("\n");

    } while 
	(choice != 0);



    return 0;
}
