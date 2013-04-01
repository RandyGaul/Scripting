// Copyright (C) 2013 Randy Gaul
// All rights reserved.
// This code is for illustration purposes to be studied in
// conjunction with online slideshows. Do not use any of
// this code in your project. You must write every character
// in your own projects from scratch. Trust me, you don't
// actually WANT to use any of this code in your project.

#pragma once

struct Condition;

typedef int (*ConditionCB)( struct Condition *self );
typedef void (*ReadConditionParams)( FILE *fp, struct Condition *self );

typedef struct Condition
{
  ConditionCB cb;
  struct Condition *next;
  int var1, var2;
  cleanup clean;
} Condition;

int Always( Condition *self );
void ReadParamsAlways( FILE *fp, Condition *self );
int TimeElapsed( Condition *self );
void ReadParamsTimeElapsed( FILE *fp, Condition *self );