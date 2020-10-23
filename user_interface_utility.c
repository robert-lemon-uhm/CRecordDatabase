/*****************************************************************
//
//  NAME:        Robert Lemon
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 14, 2020
//
//  FILE:        user_interface_utility.c
//
//  DESCRIPTION:
//    A file containing utility functions for gathering the client's
//    account number, name, and address, as well as the function to write the menu.
//    Called by the user interface.
//
//
****************************************************************/

/* includes */
#include "user_interface.h"

/*****************************************************************
//
//  FUNCTION NAME: writeMenu
//
//  DESCRIPTION:   A function that writes the UI menu to the screen.
//
//  PARAMETERS:    none
//
//  RETURN VALUES: none
//
****************************************************************/

void writeMenu()
{
    printf("\n===============================================================================\n\n");

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'writeMenu' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tnone\n\n");
        printf("\t====================================\n\n");
    }

    /* print the menu */

    printf("There are 6 implemented choices, as described below.\n");
    printf("Please input the number corresponding with your choice.\n\n");
    printf("1: Add new record to database\n");
    printf("2: Print record for individual account\n");
    printf("3: Print all records in database\n");
    printf("4: Modify address of an account\n");
    printf("5: Delete an account's record\n");
    printf("6: Quit\n\nInput: ");

}

/*****************************************************************
//
//  FUNCTION NAME: getAccountNo
//
//  DESCRIPTION:   Gets an account number from the user.
//
//  PARAMETERS:    int *accountNo is the pointer to the account number.
//
//  RETURN VALUES: none
//
****************************************************************/

void getAccountNo(int *accountNo)
{
    int gotNumber;
    char clearBuffer[100];

    printf("\n===============================================================================\n");

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'getAccountNo' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tnone\n\n");
        printf("\t====================================\n\n");
    }

    /* print instructions */

    printf("\nPlease enter account number\n");
    printf("  (account numbers are positive integers)\n\n");
    printf("Number: ");

    /* get account number */

    gotNumber = FALSE;
    *accountNo = -1;

    while ( !gotNumber )
    {
        scanf("%d", accountNo);
        fgets(clearBuffer, 100, stdin);

        if ( *accountNo < 1 )
        {
            printf("\nInvalid account number! Please try again\n\nNumber: ");
        }
        else
        {
            gotNumber = TRUE;
        }

    }

}

/*****************************************************************
//
//  FUNCTION NAME: getName
//
//  DESCRIPTION:   Gets the account name from the user.
//
//  PARAMETERS:    char *name is the name string.
//                 int size is the max size of the string.
//
//  RETURN VALUES: none
//
****************************************************************/

void getName(char * name, int size)
{
    int length;
    char ch;
    char clearBuffer[100];

    printf("\n===============================================================================\n");

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'getName' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tnone\n\n");
        printf("\t====================================\n\n");
    }

    /* print instructions */

    printf("\nPlease enter desired account name\n");
    printf("  (Names have a maximum length of %d characters)\n", size - 1);
    printf("  (To submit name, press 'Enter')\n\n");
    printf("Name: ");

    length = 0;

    /* get name */

    while ( (ch = getchar()) != '\n' && length < size - 1 )
    {
        if ( ch != '\t' )
        {
            name[length++] = ch;
        }
    }

    name[length++] = '\0';

    /* check length of input */

    if ( length == size && ch != '\n' )
    {
        fgets(clearBuffer, 100, stdin);

        printf("\nWARNING: Maximum name length reached! Received name:\n\"%s\"\n", name);
        printf("\nWould you like to re-enter the name? (y/n): ");

        do
        {
            ch = getchar();
        }
        while (ch != 'y' && ch != 'n');

        fgets(clearBuffer, 100, stdin);

        /* get name if user wants to retype it */

        if ( ch == 'y' )
        {
            getName(name, size);
        }

    }
}

/*****************************************************************
//
//  FUNCTION NAME: getAddress
//
//  DESCRIPTION:   Gets the account address from the user.
//
//  PARAMETERS:    char *address is the address string.
//                 int size is the max size of the string.
//
//  RETURN VALUES: none
//
****************************************************************/

void getAddress(char * address, int size)
{
    int length;
    char ch;
    char clearBuffer[100];

    printf("\n===============================================================================\n");

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'getAddress' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tnone\n\n");
        printf("\t====================================\n\n");
    }

    /* print instructions */

    printf("\nPlease enter desired account address\n");
    printf("  (Addresses have a maximum of %d characters)\n", size - 1);
    printf("  (To indicate the end of the address, type a '!' then hit ENTER)\n\n");
    printf("Address: ");

    length = 0;

    /* get address */

    while ( (ch = getchar()) != '!' && length < size - 1 )
    {
        address[length++] = ch;

        if ( ch == '\n' )
        {
            printf("         ");
        }
    }

    address[length++] = '\0';

    /* check length of input */

    if ( length ==  size && ch != '!')
    {
        fgets(clearBuffer, 100, stdin);

        printf("\nWARNING: Maximum address length reached! Received address:\n\"%s\"\n", address);
        printf("\nWould you like to re-enter the address? (y/n): ");

        do
        {
            ch = getchar();
        }
        while (ch != 'y' && ch != 'n');

        fgets(clearBuffer, 100, stdin);

        /* get address if user wants to retype it */

        if ( ch == 'y' )
        {
            getAddress(address, size);
        }
    }
}

