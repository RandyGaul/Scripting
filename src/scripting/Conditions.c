// Copyright (C) 2013 Randy Gaul
// All rights reserved.
// This code is for illustration purposes to be studied in
// conjunction with online slideshows. Do not use any of
// this code in your project. You must write every character
// in your own projects from scratch. Trust me, you don't
// actually WANT to use any of this code in your project.

#include "Precompiled.h"

int Always( Condition *self )
{
  return 1;
}

void ReadParamsAlways( FILE *fp, Condition *self )
{
}

int TimeElapsed( Condition *self )
{
  return GetElapsed( ) >= self->var1;
}

void ReadParamsTimeElapsed( FILE *fp, Condition *self )
{
  fscanf( fp, "%d%*c", &self->var1 );
}
