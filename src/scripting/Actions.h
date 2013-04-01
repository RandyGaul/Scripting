// Copyright (C) 2013 Randy Gaul
// All rights reserved.
// This code is for illustration purposes to be studied in
// conjunction with online slideshows. Do not use any of
// this code in your project. You must write every character
// in your own projects from scratch. Trust me, you don't
// actually WANT to use any of this code in your project.

#pragma once

struct Action;

typedef void (*ActionCB)( struct Action *self );
typedef void (*ReadActionParams)( FILE *fp, struct Action *self );

typedef struct Action
{
  ActionCB cb;
  struct Action *next;
  int var1, var2;
  cleanup clean;
} Action;

void Print( Action *self );
void ReadParamsPrint( FILE *fp, Action *self );
void CleanupPrint( void *self );
