// Copyright (C) 2013 Randy Gaul
// All rights reserved.
// This code is for illustration purposes to be studied in
// conjunction with online slideshows. Do not use any of
// this code in your project. You must write every character
// in your own projects from scratch. Trust me, you don't
// actually WANT to use any of this code in your project.

#include "Precompiled.h"

struct
{
  Event head;
  Event tail;
} static EventList;

static int elapsed = 0;

int GetElapsed( void )
{
  return elapsed;
}

Event *EventListBegin( void )
{
  return EventList.head.next;
}

Event *EventListEnd( void )
{
  return &EventList.tail;
}

void InitEventList( void )
{
  EventList.head.next = &EventList.tail;
  EventList.head.prev = NULL;
  EventList.tail.prev = &EventList.head;
  EventList.tail.next = NULL;
}

void EventListAdd( Event *e )
{
  EventList.head.next->prev = e;
  e->next = EventList.head.next;

  EventList.head.next = e;
  e->prev = &EventList.head;
}

Event *EventListRemove( Event *e )
{
  Condition *c = e->conditions;
  Action *a = e->actions;
  Event *next = e->next;

  // Remove event from the EventList
  e->next->prev = e->prev;
  e->prev->next = e->next;

  // Free all conditions of this event
  while(c)
  {
    Condition *temp = c;
    if(c->clean)
      c->clean( c ); // Run condition's cleanup
    c = c->next;
    free( temp );
  }
  
  // Free all actions of this event
  while(a)
  {
    Action *temp = a;
    if(a->clean)
      a->clean( a ); // Run action's cleanup
    a = a->next;
    free( temp );
  }

  // Free the event
  free( e );
  return next;
}

int UpdateEventList( void )
{
  Event *e = EventListBegin( );

  // Increment our elapsed timer
  ++elapsed;

  // List is empty
  if(e == EventListEnd( ))
    return 0;

  while(e != EventListEnd( ))
  {
    Condition *c = e->conditions;
    int allConditionsReturnedTrue = 1;

    // Check all the conditions
    while(c)
    {
      if(!c->cb( c ))
      {
        allConditionsReturnedTrue = 0;
        break;
      }

      c = c->next;
    }

    if(allConditionsReturnedTrue)
    {
      Action *a = e->actions;

      // Run all actions
      while(a)
      {
        a->cb( a );
        a = a->next;
      }

      // Remove event from queue
      e = EventListRemove( e );
    }
    else
      e = e->next;
  }

  // List is not empty
  return 1;
}

// NOTE : I suggest cleaning up the following pointer arrays with vtables, or better
//        yet a single global vtable! See GameObject Design lecture for more details.

// Array of condition names
const char *ConditionArray[] = {
  "Always",
  "TimeElapsed",
  NULL,
};

// Array of function pointers for the condition callback
// of each type of condition
const ConditionCB ConditionPtrs[] = {
  Always,
  TimeElapsed,
};

const cleanup ConditionCleanups[] = {
  NULL,
  NULL,
};

// Array of function pointers for reading in the parameters of a certain
// condition
const ReadConditionParams ReadCParamPtrs[] = {
  ReadParamsAlways,
  ReadParamsTimeElapsed,
};

// Array of names of all actions
const char *ActionArray[] = {
  "Print",
  NULL,
};

// Array of function pointers to all action callbacks
const ActionCB ActionPtrs[] = {
  Print,
};

// Array of all functions pointers for reading the parameters
// of the different types of actions.
const ReadActionParams ReadAParamPtrs[] = {
  ReadParamsPrint,
};

const cleanup ActionCleanups[] = {
  CleanupPrint,
};

#define NOT_FOUND -1

// Used to get the index of a condition or action for use
// in the above arrays
int GetArrayIndex( const char **strArray, const char *string )
{
  const char **i = strArray;
  while(*i)
  {
    if(StringsMatch( string, *i ))
      return i - strArray; // index
    ++i;
  }

  return NOT_FOUND;
}

// Adds events to the event list from a file
void AddEventsFromFile( const char *fileName )
{
  char buffer[256];

  FILE *fp = fopen( fileName, "r" );

  Event *e;

  // Read first token
  fscanf( fp, "%s%*c", buffer );

  if(fp)
    while(!feof( fp ))
    {
      // Start a new event
      if(StringsMatch( buffer, "Conditions" ))
      {
        // Malloc a new event
        e = (Event *)malloc( sizeof( Event ) );
        e->actions = NULL;
        e->conditions = NULL;

        // Read in conditions
        for(;;)
        {
          int index;
          Condition *c;
          fscanf( fp, "%s%*c", buffer );

          // Should never hit end of file while reading conditions
          if(feof( fp ))
            assert( NULL );

          index = GetArrayIndex( ConditionArray, buffer );

          // String in buffer did not match any conditions
          if(index == NOT_FOUND)
            break;

          c = (Condition *)malloc( sizeof( Condition ) );

          // Insert condition into event
          c->next = e->conditions;
          e->conditions = c;
          c->cb = ConditionPtrs[index];

          // Read parameters for condition
          ReadCParamPtrs[index]( fp, c );

          // Set cleanup function
          c->clean = ConditionCleanups[index];
        }
      }

      if(StringsMatch( buffer, "Actions" ))
      {
        // Read in actions
        for(;;)
        {
          int index;
          Action *a;
          fscanf( fp, "%s%*c", buffer );

          // Break if we are at end of file
          if(feof( fp ))
            break;

          index = GetArrayIndex( ActionArray, buffer );

          // String in buffer did not match any actions
          if(index == NOT_FOUND)
            break;

          a = (Action *)malloc( sizeof( Action ) );

          // Insert action into event
          a->next = e->actions;
          e->actions = a;
          a->cb = ActionPtrs[index];
          
          // Read parameters for action
          ReadAParamPtrs[index]( fp, a );

          // Set cleanup function
          a->clean = ActionCleanups[index];
        }

        // Insert event into event list
        EventListAdd( e );
      }
    }
}

// Helper to see if two strings match or not
int StringsMatch( const char *str1, const char *str2 )
{
  return strcmp( str1, str2 ) == 0;
}
