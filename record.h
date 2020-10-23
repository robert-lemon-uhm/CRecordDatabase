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
//  FILE:        record.h
//
//  DESCRIPTION:
//    A structure for the datatype 'record'.
//    This is used by the user interface and the database.
//
//
****************************************************************/

/* structures */

struct record
{
    int                 accountno;
    char                name[25];
    char                address[80];
    struct record*      next;
};
