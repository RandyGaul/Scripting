// Copyright (C) 2013 Randy Gaul
// All rights reserved.
// This code is for illustration purposes to be studied in
// conjunction with online slideshows. Do not use any of
// this code in your project. You must write every character
// in your own projects from scratch. Trust me, you don't
// actually WANT to use any of this code in your project.

#include "Precompiled.h"

void Print( Action *self )
{
  printf( "Printing: %s\n", self->var1 );
}

void ReadParamsPrint( FILE *fp, Action *self )
{
  // Read a " character.
  // Then read in a string and assign it to var1 until we find a "
  // character. Then read in (but do not assign) the last " character.
  // Lastly read in (and do not assign) one more character, which should
  // be a newline.
  char c[2056];
  fscanf( fp, "\" %[^\"]\"%*c", c );
  self->var1 = (int)malloc( strlen( c ) + 1 );
  strcpy( (char *)self->var1, c );
}

void CleanupPrint( void *self )
{
  // Free the string allocated in ReadParamsPrint
  free( (void *)((Action *)self)->var1 );
}
