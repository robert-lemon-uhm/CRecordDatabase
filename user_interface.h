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
//  FILE:        user_interface.h
//
//  DESCRIPTION:
//    The header file for user_interface.c and user_interface_utility.c
//    This includes the database header, as well as function calls for
//    user_interface and user_interface_utility.
//
//
****************************************************************/

/* includes */
#include "database.h"

/* prototypes */
void getUserInput(struct record **);
void writeMenu();
void getAccountNo(int *);
void getName(char *, int);
void getAddress(char *, int);

