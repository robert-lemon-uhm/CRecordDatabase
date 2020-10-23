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
//  FILE:        database.h
//
//  DESCRIPTION:
//    A header file for the database.c file.  It includes the stdio, stdlib
//    string, and record header files, a global variable for debugging,
//    and the prototypes of the database functions.
//
//
****************************************************************/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

/* defines */
#define FALSE 0
#define TRUE 1
#define NAME_LENGTH 25
#define ADDRESS_LENGTH 80

/* global variables */
extern int debugmode;

/* prototypes */
int addRecord(struct record **, int, char[], char[]);
int printRecord(struct record *, int);
void printAllRecords(struct record *);
int modifyRecord(struct record *, int, char[]);
int deleteRecord(struct record **, int);
int readfile(struct record **, char[]);
int writefile(struct record *, char[]);
void cleanup(struct record **);

