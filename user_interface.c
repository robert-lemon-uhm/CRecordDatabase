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
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//    A file containing the user interface used to access the database
//    in database.c.  The user interface collects user input to access
//    database functions.  The user_interface_utility file is used to
//    help gather input.
//
//
****************************************************************/

/* includes */
#include "user_interface.h"

/* global variable */
int debugmode = FALSE;

/*****************************************************************
//
//  FUNCTION NAME: main
//
//  DESCRIPTION:   The main driver for the user interface.  The main function
//                 checks that the proper arguments were used to call the program
//                 before actually initializing the user interface. Also calls 
//                 the readfile and writefile to save the database.
//
//  PARAMETERS:    int argc is the number of arguments.
//                 char *argv[] is an array of the arguent pointers.
//
//  RETURN VALUES: Returns 0
//
****************************************************************/

int main(int argc, char *argv[])
{
    int properCall;
    int recordReturn;
    char debugCall[] = "debug";
    char fileName[] = "recordDatabase.txt";
    struct record * start;

    properCall = TRUE;
    start = NULL;

    /* check for valid number of arguments */

    if ( argc > 2 )
    {
        properCall = FALSE;
    }

    /* check for valid arguments (debug) */

    if ( argc == 2 )
    {
        if ( strcmp(debugCall, argv[1]) != 0 )
        {
            properCall = FALSE;
        }
        else
        {
            debugmode = TRUE;
        }
    }

    /* continue program if properCall is true */

    if ( properCall )
    {

        /* print initial instructions */

        printf("\n===============================================================================\n");
        printf("\nWelcome to the user interface for project1!\n");
        printf("This UI offers 5 methods of accessing and updating the database.\n");
        printf("Each method can be called as many times as needed.\n");
        printf("\n===============================================================================\n\n");

        /* read file to populate database */

        recordReturn = readfile(&start, fileName);

        if ( recordReturn < 1 )
        {
            printf("Database is currently empty.\n");
        }
        else if ( recordReturn == 1 )
        {
            printf("1 record currently in database.\n");
        }
        else
        {
            printf("%d records currently in database.\n", recordReturn);
        }

        /* run program */

        getUserInput(&start);

        /* save current database to file */

        recordReturn = writefile(start, fileName);

        printf("\n===============================================================================\n\n");

        if ( recordReturn == -1 )
        {
            printf("Database could not be saved!\n");
        }
        else if ( recordReturn == 0 )
        {
            printf("No records saved to database file.\n");
        }
        else if ( recordReturn == 1 )
        {
            printf("1 record saved to database file.\n");
        }
        else
        {
            printf("%d records saved to database file.\n", recordReturn);
        }

        /* close program */

        cleanup(&start);

        printf("\n===============================================================================\n");
    }
    else
    {
        printf("\nError: illegal argument\n");
        printf("Available arguments: debug\n\n");
        printf("  ./project1\t\t\truns project1 normally\n");
        printf("  ./project1 debug\t\truns project1 in debug mode (prints function calls)\n\n");
    }

    return 0;
}

/*****************************************************************
//
//  FUNCTION NAME: getUserInput
//
//  DESCRIPTION:   A function that gets the user's input and calls the function that the user chooses.
//                 The user_interface_utility functions are used to gather further input.
//
//  PARAMETERS:    struct record **start points to the location of the first record in the database.
//
//  RETURN VALUES: none
//
****************************************************************/

void getUserInput(struct record **start)
{
    int recordReturn;
    int userInput;
    int accountNo;
    char name[NAME_LENGTH];
    char address[ADDRESS_LENGTH];
    char clearBuffer[100];

    userInput = 0;

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'getUserInput' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tstart: %p\n\n", (void *) start);
        printf("\t====================================\n\n");
    }

    /* get user input */
    while ( userInput != 6 )
    {
        writeMenu();

        scanf("%d", &userInput);
        fgets(clearBuffer, 100, stdin);

        /* process user input */

        switch ( userInput )
        {
            case 1:

                /* addRecord case */

                getAccountNo(&accountNo);
                getName(name, NAME_LENGTH);
                getAddress(address, ADDRESS_LENGTH);
                recordReturn = addRecord(start, accountNo, name, address);

                if ( recordReturn == 0 )
                {
                    printf("\n===============================================================================\n\n");
                    printf("Record successfully added!\n");
                }
                else
                {
                    printf("Record could not be added! Not enough memory!\n");
                }

                break;

            case 2:

                /* printRecord case */

                if ( *start == NULL )
                {
                    printf("\n===============================================================================\n\n");
                    printf("Database is empty!\n");
                }
                else
                {
                    getAccountNo(&accountNo);
                    recordReturn = printRecord(*start, accountNo);

                    if ( recordReturn == 0 )
                    {
                        printf("\nThere are no records with account number %d in the database.\n\n",
                            accountNo);
                    }
                    else if ( recordReturn == 1 )
                    {
                        printf("\nThere is 1 record with account number %d in the database.\n\n",
                            accountNo);
                    }
                    else if ( recordReturn > 1 )
                    {
                        printf("\nThere are %d records with account number %d in the database.\n\n",
                            recordReturn, accountNo);
                    }
                }

                break;

            case 3:

                /* printAllRecords case */

                if ( *start == NULL )
                {
                    printf("\n===============================================================================\n\n");
                    printf("Database is empty!\n");
                }
                else {
                    printAllRecords(*start);
                }

                break;

            case 4:

                /* modifyRecord case */

                if ( *start == NULL )
                {
                    printf("\n===============================================================================\n\n");
                    printf("Database is empty!\n");
                }
                else
                {
                    getAccountNo(&accountNo);
                    getAddress(address, ADDRESS_LENGTH);
                    recordReturn = modifyRecord(*start, accountNo, address);
                    printf("\n===============================================================================\n\n");

                    if ( recordReturn == 0 )
                    {
                        printf("\nThere are no records with account number %d in the database.\n\n",
                            accountNo);
                    }
                    else if ( recordReturn == 1 )
                    {
                        printf("\n1 record with account number %d got modified.\n\n", accountNo);
                    }
                    else if ( recordReturn > 1 )
                    {
                        printf("\n%d records with account number %d got modified.\n\n", recordReturn, accountNo);
                    }
                }

                break;

            case 5:

                /* deleteRecord case */

                if ( *start == NULL )
                {
                    printf("\n===============================================================================\n\n");
                    printf("Database is empty!\n");
                }
                else
                {
                    getAccountNo(&accountNo);
                    recordReturn = deleteRecord(start, accountNo);
                    printf("\n===============================================================================\n\n");

                    if ( recordReturn == 0 )
                    {
                        printf("\nThere are no records with account number %d in the database.\n\n",
                            accountNo);
                    }
                    else if ( recordReturn == 1 )
                    {
                        printf("\n1 record with account number %d got deleted.\n\n", accountNo);
                    }
                    else if ( recordReturn > 1 )
                    {
                        printf("\n%d records with account number %d got deleted.\n\n", recordReturn, accountNo);
                    }
                }

                break;

            case 6:
                break;

            default:
                printf("\n===============================================================================\n\n");
                printf("\nInvalid input!\n\n");
        }
    }
}

