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
//  FILE:        database.c
//
//  DESCRIPTION:
//    A file that contains database functions that modify a database of account records.
//    The records are stored on a struct containing the account number, name, and address.
//    The addRecord, printRecord, printAllRecords, modifyRecord, deleteRecord, readfile,
//    writefile, and cleanup functions create the entire database.
//
//
****************************************************************/

/* includes */
#include "database.h"

/*****************************************************************
//
//  FUNCTION NAME: addRecord
//
//  DESCRIPTION:   A database function that, given an account number, name, and address,
//                 creates a new node that's populated with the parameter information
//                 and links it to the end of the database.  It updates the start
//                 pointer for the database if you add to an empty linked list.
//
//  PARAMETERS:    struct record **start points to the location of the first node (or NULL).
//                 int accountNo is the user-entered account number.
//                 char name[] is the user-entered name.
//                 char address[] is the user-entered address.
//
//  RETURN VALUES: Returns 0 if record added.
//                 Returns -1 if record wasn't added.
//
****************************************************************/

int addRecord(struct record **start, int accountNo, char name[], char address[])
{
    struct record *newNode;
    struct record *tempNode;
    int returnValue;

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE=======================\n\n");
        printf("\t  Entered 'addRecord' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\taccountNo: %d\n", accountNo);
        printf("\t\tname: %s\n", name);
        printf("\t\taddress: %s\n\n", address);
        printf("\t====================================\n\n");
    }

    /* Create a new node */

    returnValue = -1;
    newNode = malloc(sizeof(struct record));

    if (newNode != NULL )
    {
        returnValue = 0;

        (*newNode).accountno = accountNo;
        strcpy((*newNode).name, name);
        strcpy((*newNode).address, address);
        (*newNode).next = NULL;

        /* Update start pointer if list is empty */

        if ( *start == NULL )
        {
            *start = newNode;
        }

        /* Update linked list if not empty */

        else
        {
            tempNode = *start;

            while ( (*tempNode).next != NULL )
            {
                tempNode = (*tempNode).next;
            }

            (*tempNode).next = newNode;
        }
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: printRecord
//
//  DESCRIPTION:   A database function that iterates through the linked list and
//                 prints all records with a given account number.
//
//  PARAMETERS:    struct record *start is the location of first record (or NULL).
//                 int accountNo is the user-entered account number to print.
//
//  RETURN VALUES: Returns -1 if database is empty.
//                 Otherwise, returns the amount of records read (0 or positive int).
//
****************************************************************/

int printRecord(struct record *start, int accountNo)
{
    struct record *node;
    int returnValue;
    int i;

    printf("\n===============================================================================\n\n");

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'printRecord' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\taccountNo: %d\n\n", accountNo);
        printf("\t====================================\n\n");
    }

    /* Initialize variables */

    returnValue = 0;
    node = start;

    /* check if database is empty */

    if ( start == NULL )
    {
        returnValue = -1;
    }

    /* iterate through the databse */

    while ( node != NULL )
    {

        /* print all records with matching account numbers */

        if ( (*node).accountno == accountNo )
        {
            i = 0;

            printf("\nAccount Number: \t%d\nName:\t\t\t%s\nAddress:\t\t",
                (*node).accountno, (*node).name);

            while ( (*node).address[i] != '\0' )
            {
                printf("%c", (*node).address[i]);
                if ( (*node).address[i++] == '\n' )
                {
                    printf("\t\t\t");
                }
            }

            printf("\n\n");

            returnValue++;
        }

        node = (*node).next;
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: printAllRecords
//
//  DESCRIPTION:   A database function that iterates through the entire database and
//                 prints all records.  Prints the amount of records in database, too.
//
//  PARAMETERS:    struct record *start is the location of the first record (or NULL).
//
//  RETURN VALUES: none
//
****************************************************************/

void printAllRecords(struct record *start)
{
    struct record *node;
    int recordCounter;
    int i;

    printf("\n===============================================================================\n\n");

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'printAllRecords' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tnone\n\n");
        printf("\t====================================\n\n");
    }

    /* Print all records in the database */

    recordCounter = 0;
    node = start;

    while ( node != NULL )
    {
        i = 0;

        printf("\nAccount Number: \t%d\nName:\t\t\t%s\nAddress:\t\t",
            (*node).accountno, (*node).name);

        while ( (*node).address[i] != '\0' )
        {
            printf("%c", (*node).address[i]);
            if ( (*node).address[i++] == '\n' )
            {
                printf("\t\t\t");
            }
        }

        printf("\n\n");

        node = (*node).next;
        recordCounter++;
    }

    if ( recordCounter == 1 )
    {
        printf("\nThere is 1 record currently in the database.\n\n");
    }

    else if ( recordCounter > 1 )
    {
        printf("\nThere are %d records currently in the database.\n\n", recordCounter);
    }
}

/*****************************************************************
//
//  FUNCTION NAME: modifyRecord
//
//  DESCRIPTION:   A database function that iterates through the database and updates the
//                 address of all records that match a user-specified account number.
//
//  PARAMETERS:    struct record *start is the location of the first record (or NULL).
//                 int accountNo is the user-specified account number.
//                 char address[] is the user-specified new address.
//
//  RETURN VALUES: Returns -1 if the database is empty.
//                 Otherwise, returns the number of records modified (0 or a positive int).
//
****************************************************************/

int modifyRecord(struct record *start, int accountNo, char address[])
{
    struct record *node;
    int returnValue;

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'modifyRecord' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\taccountNo: %d\n", accountNo);
        printf("\t\taddress: %s\n\n", address);
        printf("\t====================================\n\n");
    }

    /* initialize variables */

    returnValue = 0;
    node = start;

    if ( start == NULL )
    {
        returnValue = -1;
    }

    /* iterate through the database */

    while ( node != NULL )
    {

        /* modify all records with matching account numbers */

        if ( (*node).accountno == accountNo )
        {
            strcpy((*node).address, address);
            returnValue++;
        }

        node = (*node).next;
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: deleteRecord
//
//  DESCRIPTION:   A database function that iterates through the entire database and
//                 deletes all records with a user-specified account number.
//
//  PARAMETERS:    struct record **start points to the location of the first node (or NULL).
//                 int accountNo is the user-specified account number.
//
//  RETURN VALUES: Returns -1 if database is empty.
//                 Otherwise, returns the amount of records deleted (0 or positive int).
//
****************************************************************/

int deleteRecord(struct record **start, int accountNo)
{
    int returnValue;
    struct record *previousNode;
    struct record *currentNode;
    struct record *nextNode;

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'deleteRecord' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\taccountNo: %d\n", accountNo);
        printf("\t====================================\n\n");
    }

    /* initialize all variables */

    returnValue = -1;
    previousNode = NULL;
    currentNode = *start;

    if ( *start != NULL )
    {
        returnValue = 0;
        nextNode = (*currentNode).next;
    }

    /* iterate through entire database */

    while ( currentNode != NULL )
    {

        /* delete record if the account number matches parameter */

        if ( accountNo == (*currentNode).accountno )
        {
            returnValue++;
            free(currentNode);

            /* if head got deleted */

            if ( *start == currentNode )
            {
                *start = nextNode;
            }

            /* if tail got deleted */

            else if ( nextNode == NULL )
            {
                (*previousNode).next = NULL;
            }

            /* if middle got deleted */

            else
            {
                (*previousNode).next = nextNode;
            }
        }

        else
        {
            previousNode = currentNode;
        }

        currentNode = nextNode;

        if ( currentNode != NULL )
        {
            nextNode = (*currentNode).next;
        }

    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: readfile
//
//  DESCRIPTION:   A database function that is run upon successful startup of the
//                 program.  It scans a text file, adding records stored on it to the
//                 database.
//
//  PARAMETERS:    struct record **start points to the location of the first node (or NULL).
//                 char fileName[] is the name of the file to read from.
//
//  RETURN VALUES: Returns -1 if no file found.
//                 Otherwise, returns the amount of records scanned and added (0 or positive int).
//
****************************************************************/

int readfile(struct record **start, char fileName[])
{
    int accountno;
    int continueReading;
    int i;
    int lineNumber;
    int returnValue;

    char ch;

    char address[ADDRESS_LENGTH];
    char name[NAME_LENGTH];

    FILE * file;

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'readfile' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tstart: %p\n", (void *) start);
        printf("\t\tfileName: \"%s\"\n", fileName);
        printf("\t====================================\n\n");
    }

    /* initialize variables */

    continueReading = TRUE;
    lineNumber = 0;
    returnValue = 0;

    if ((file = fopen(fileName, "r")) == NULL)
    {
        returnValue = -1;;
        *start = NULL;
    }

    while (continueReading && returnValue > -1)
    {

        /* process next line in file */

        switch (lineNumber)
        {

            /* get account number */

            case 0:

               if (fscanf(file, "%d", &accountno) != EOF)
               {
                    while ((ch = fgetc(file)) != '\n');
               }
               else
               {
                   continueReading = FALSE;
               }

                break;

            /* get name */

            case 1:

                i = 0;
                ch = fgetc(file);

                while (ch != '\n' && i < NAME_LENGTH - 1)
                {
                    name[i++] = ch;
                    ch = fgetc(file);
                }

                name[i] = '\0';

                if (ch != '\n')
                {
                    while ((ch = fgetc(file)) != '\n');
                }

                break;

            /* get address */

            case 2:

                i = 0;
                ch = fgetc(file);

                while (ch != '!' && i < ADDRESS_LENGTH - 1)
                {
                    address[i++] = ch;
                    ch = fgetc(file);
                }

                address[i] = '\0';

                if (ch != '\n')
                {
                    while ((ch = fgetc(file)) != '\n');
                }

                break;

            default:;
        }

        /* increment numcust */

        if (lineNumber == 2)
        {
            addRecord(start, accountno, name, address);
            returnValue++;
        }

        /* increment line being processed */

        lineNumber = (lineNumber + 1) % 3;

    }

    if (returnValue != -1)
    {
        fclose(file);
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: writefile
//
//  DESCRIPTION:   A database function that is run upon successful completion of the
//                 program.  It writes the current database to a text file to save it.
//
//  PARAMETERS:    struct record *start is the location of the first record (or NULL).
//                 char fileName[] is the name of the file to write to.
//
//  RETURN VALUES: Returns -1 if file cannot be open or made.
//                 Otherwise, returns number of records written to file (0 or positive int).
//
****************************************************************/

int writefile(struct record *start, char fileName[])
{
    int returnValue;
    struct record *node;
    FILE * file;

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'writefile' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tstart: %p\n", (void *) start);
        printf("\t\tfileName: %s\n", fileName);
        printf("\t====================================\n\n");
    }

    returnValue = 0;

    if ((file = fopen(fileName, "w")) == NULL)
    {
        returnValue = -1;
    }
    else
    {
        node = start;

        while ( node != NULL )
        {
            fprintf(file, "%d\n", (*node).accountno);
            fprintf(file, "%s\n", (*node).name);
            fprintf(file, "%s!\n", (*node).address);
            node = (*node).next;
            returnValue++;
        }

        fclose(file);
    }

    return returnValue;
}

/*****************************************************************
//
//  FUNCTION NAME: cleanup
//
//  DESCRIPTION:   A database function that is called after writefile saves the
//                 database.  It frees all space allocated for the records, cleaning
//                 up after the program. It reassigns linked list head to NULL.
//
//  PARAMETERS:    struct record **start points to the location of the first node (or NULL).
//
//  RETURN VALUES: none
//
****************************************************************/

void cleanup(struct record **start)
{
    struct record * currentNode;
    struct record * nextNode;

    /* print debug information for function call */

    if ( debugmode )
    {
        printf("\n\t==DEBUG MODE========================\n\n");
        printf("\t  Entered 'cleanup' function\n\n");
        printf("\t  Parameters:\n");
        printf("\t\tstart: %p\n", (void *) start);
        printf("\t====================================\n\n");
    }

    /* unallocate all allocated heap space */

    currentNode = *start;

    while ( currentNode != NULL )
    {
        nextNode = (*currentNode).next;

        free(currentNode);

        currentNode = nextNode;
    }

    *start = NULL;
}

