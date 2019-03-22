#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "sort_procedures.h"

void merge_sort_openmp(
  double* A,   
  int p,      
  int r,
  int level      
){
/*++++++++++++++++ executable statements ++++++++++++++++*/
  if (p < r) {
		#define  max_level 2

    level++;

    int q1 = (p + r) / 2;
    
		/* 
			task - generating tasks to be executed by threads
			final - if level > max_level stop generating new tasks and execute immediately
			default - every used variable must be explicitly declared
			firstprivate - private variables of task with an initial value assigned
		*/
		#pragma omp task final (level > max_level) default (none) firstprivate (A, p, r, q1, level) 
		{
			merge_sort_openmp (A, p, q1, level);
		}

		#pragma omp task final (level > max_level) default (none) firstprivate (A, p, r, q1, level) 
    {
      merge_sort_openmp (A, q1 + 1, r, level);
    }

		/*
			taskwait - waiting for the completion of all tasks
		*/
		#pragma omp taskwait  

    merge(A, p, q1, r);
  }
  
  return;
}

void merge_sort_openmp_2(
  double* A,   
  int p,      
  int r,
  int level      
){

/*++++++++++++++++ executable statements ++++++++++++++++*/

  if (p < r) {
    
    printf ("thread %d, level %d\n", omp_get_thread_num(), level);

    level++;

    int q1 = (p + r) / 2;
    
		#define level_max 3

		#pragma omp task final (level > level_max) default (none) firstprivate (A, p, r, q1, level) 
			{
				if (omp_in_final () ) quick_sort (A, p, q1);
				else merge_sort_openmp_2 (A, p, q1, level);
			}

		#pragma omp task final( level > level_max ) default(none) firstprivate(A,p,r,q1,level) 
			{
				if(omp_in_final()) quick_sort(A,q1+1,r);
				else merge_sort_openmp_2(A,q1+1,r,level);
			}

		#pragma omp taskwait  

    merge(A,p,q1,r);
    
  }
  
  return;
}


void merge_sort_openmp_4(
  double* A,   
  int p,      
  int r      
){
/*++++++++++++++++ executable statements ++++++++++++++++*/

  if(p<r){

    int q1=(p+r)/2;

		/*
			Permission to nest parallelism
		*/
    omp_set_nested(1);
    
		/*
			parallel sections - each section can be executed in parallel
		*/
		#pragma omp parallel sections default(none) firstprivate(A,p,r,q1)
    {
    	// section
		#pragma omp section
      {
				int q2 = (p+q1)/2;
	
				/*
					block of nested sections inside a single section
				*/
				#pragma omp parallel sections default(none) firstprivate(A,p,r,q1,q2)
				{
					// nested section
					#pragma omp section
					{
						quick_sort(A,p,q2);
					}
	  
					#pragma omp section
					{
						quick_sort(A,q2+1,q1);
					}  
				}
	
				merge(A,p,q2,q1);
			}

			#pragma omp section
			{
	
				int q2 = (q1+1+r)/2;
	
				#pragma omp parallel sections default(none) firstprivate(A,p,r,q1,q2)
				{
	  
					#pragma omp section
					{
						quick_sort(A,q1+1,q2);
					}
	  
					#pragma omp section
					{
						quick_sort(A,q2+1,r);
					}
				}
				merge(A,q1+1,q2,r);
			}
		}
		merge(A,p,q1,r);
	}
  return;
}


