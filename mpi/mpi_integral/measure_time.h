/******************************************************************************
File measure_time.h - procedures of time measurement for different OS

Procedures using standard functions C:

Procedury wykorzystujace funkcje standardowe C:
  time_C - returns CPI time in seconds from start time or -1 if clock() is not
           correctly implemented in system

UNIX procedures:
  initialize_time - initialize time measurement
  print_time      - measures and prints CPU and clock time from initialization
  time_CPU        - prints CPU time from initialization
  time_clock      - prints clock time from initialization

Usage: according to the interface in this file
******************************************************************************/

#ifndef _measure_time_
#define _measure_time_


/*---------------------------------------------------------
initialize_time - initiates the measurement
---------------------------------------------------------*/
void initialize_time();


/*---------------------------------------------------------
  time_C - returns CPI time in seconds from start time or -1 if clock() is not
           correctly implemented in system
---------------------------------------------------------*/
double time_C();

/*---------------------------------------------------------
  time_clock - the procedure returns the clock time in seconds 
               from the moment of initiation (as the number of double precision) 
---------------------------------------------------------*/
double time_clock();

/*---------------------------------------------------------
  time_CPU - the procedure returns the CPU time in seconds since the 
             initiation (as the number of double precision)
 ---------------------------------------------------------*/
double time_CPU();

/*---------------------------------------------------------
 print_time - measurement and printout of CPU time and clock time 
              in seconds from the time measurement initiation
 ---------------------------------------------------------*/
void print_time();


#endif
