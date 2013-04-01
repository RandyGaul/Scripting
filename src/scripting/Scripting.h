// Copyright (C) 2013 Randy Gaul
// All rights reserved.
// This code is for illustration purposes to be studied in
// conjunction with online slideshows. Do not use any of
// this code in your project. You must write every character
// in your own projects from scratch. Trust me, you don't
// actually WANT to use any of this code in your project.

#pragma once

typedef struct Event
{
  Condition *conditions;
  Action *actions;
  struct Event *next;
  struct Event *prev;
} Event;

Event *EventListBegin( void );
Event *EventListEnd( void );
void InitEventList( void );
int UpdateEventList( void );
int GetElapsed( void );

void AddEventsFromFile( const char *fileName );
int StringsMatch( const char *str1, const char *str2 );
