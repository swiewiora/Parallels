/******************************************************************************
File measure_time.c - procedures of time measurement for different OS

Procedures using standard functions C:

Procedury wykorzystujace funkcje standardowe C:
  time_C - returns CPI time in seconds from start time or -1 if clock() is not
           correctly implemented in system

UNIX procedures:
  init_time - initialize time measurement
  print_time      - measures and prints CPU and clock time from initialization
  time_CPU        - prints CPU time from initialization
  time_clock      - prints clock time from initialization

Usage: according to measure_time.h
******************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>

/* interface */
#include "measure_time.h"

/* static variables for repeated use of measurement procedures */
static clock_t ct;
static struct rusage rp;
static struct timeval tp;
static struct timezone tzp;

/*---------------------------------------------------------
  time_C - returns CPI time in seconds from start time or -1 if clock() is not
           correctly implemented in system
---------------------------------------------------------*/
double time_C()
{        
  clock_t time;

  time = clock();

  if(time==-1) return( (double) time);
  else return ( (double) time / (double) CLOCKS_PER_SEC );
}

/*---------------------------------------------------------
init_time - initiates the measurement of time by giving 
                  initial values to the structures tp, tzp and rp
---------------------------------------------------------*/
void init_time()
{
  ct = clock();
  getrusage(RUSAGE_SELF, &rp);
  gettimeofday(&tp,&tzp);
}


/*---------------------------------------------------------
  time_clock - the procedure returns the clock time in seconds 
               from the moment of initiation (as the number of double precision) 
---------------------------------------------------------*/
double time_clock()
{ 
  
  struct timeval tk;
  struct timezone tzp;
  double daytime;
  
  gettimeofday(&tk, &tzp);
  
  daytime=(tk.tv_usec-tp.tv_usec)/1e6+tk.tv_sec-tp.tv_sec;
  
  return(daytime);
}

/*---------------------------------------------------------
  time_CPU - the procedure returns the CPU time in seconds since the 
             initiation (as the number of double precision)
 ---------------------------------------------------------*/
double time_CPU()
{ 
  
  struct rusage rk;
  double cputime;
  
  getrusage(RUSAGE_SELF, &rk);
  
  cputime = (rk.ru_utime.tv_usec-rp.ru_utime.tv_usec)/1e6;
  cputime += rk.ru_utime.tv_sec-rp.ru_utime.tv_sec;
  
  return(cputime);
}

/*---------------------------------------------------------
 print_time - measurement and printout of CPU time and clock time 
              in seconds from the time measurement initiation
 ---------------------------------------------------------*/
void print_time()
{ 
  
  clock_t time;
  struct rusage rk;
  struct timeval tk;
  double stdtime, cputime,daytime;
  
  time = clock();
  getrusage(RUSAGE_SELF, &rk);
  gettimeofday(&tk, &tzp);
  
  stdtime = (double) (time - ct) / (double)  CLOCKS_PER_SEC ;

  cputime = ( rk.ru_utime.tv_usec - rp.ru_utime.tv_usec ) / 1.0e6 ;
  cputime += rk.ru_utime.tv_sec - rp.ru_utime.tv_sec;
  
  daytime = ( tk.tv_usec - tp.tv_usec ) / 1.0e6 + tk.tv_sec - tp.tv_sec ;
  
  printf("czas standardowy = %lf\n",stdtime);
  printf("czas CPU         = %lf\n",cputime);
  printf("czas zegarowy    = %lf\n",daytime);
  
}
