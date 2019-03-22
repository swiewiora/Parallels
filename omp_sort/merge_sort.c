#include<stdlib.h>
#include<stdio.h>
#include<omp.h>

#include "sort_procedures.h"

void merge_sort_openmp(
  double* A,   
  int p,      
  int r,
  int poziom      
){

/*++++++++++++++++ executable statements ++++++++++++++++*/

  if(p<r){
    
    //printf("watek %d, poziom %d\n", omp_get_thread_num(),poziom);

		#define  max_poziom 2

    poziom++;

    int q1=(p+r)/2;
    
		/* 
			task - generowanie zadañ do realizacji przez w¹tki
			final - jeœli poziom > max_poziom nie s¹ generowane kolejne zadania, tylko s¹ wykonywane od razu
			default - ka¿da wykorzystywana zmienna musi byæ jawnie zadeklarowana
			firstprivate - zmienne prywatne zadania z przepisan¹ wartoœci¹ pocz¹tkow¹
			*/
		#pragma omp task final( poziom>max_poziom ) default(none) firstprivate(A,p,r,q1,poziom) 
		{
			merge_sort_openmp(A,p,q1,poziom);
		}

		#pragma omp task final( poziom>max_poziom ) default(none) firstprivate(A,p,r,q1,poziom) 
    {
      merge_sort_openmp(A,q1+1,r,poziom);
    }

		/*
			taskwait - oczekiwanie na zakoñczenie wszystkich zadañ
		*/
		#pragma omp taskwait  

    scal(A,p,q1,r);
    
  }
  
  return;
}

void merge_sort_openmp_2(
  double* A,   
  int p,      
  int r,
  int poziom      
){

/*++++++++++++++++ executable statements ++++++++++++++++*/

  if(p<r){
    
    printf("watek %d, poziom %d\n", omp_get_thread_num(),poziom);

    poziom++;

    int q1=(p+r)/2;
    
		#define poziom_max 3

		#pragma omp task final( poziom > poziom_max ) default(none) firstprivate(A,p,r,q1,poziom) 
			{
				if(omp_in_final()) sortowanie_szybkie(A,p,q1);
				else merge_sort_openmp_2(A,p,q1,poziom);
			}

		#pragma omp task final( poziom > poziom_max ) default(none) firstprivate(A,p,r,q1,poziom) 
			{
				if(omp_in_final()) sortowanie_szybkie(A,q1+1,r);
				else merge_sort_openmp_2(A,q1+1,r,poziom);
			}

		#pragma omp taskwait  

    scal(A,p,q1,r);
    
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
			Zgoda na zagnie¿d¿anie równoleg³oœci
		*/
    omp_set_nested(1);
    
		/*
			parallel sections - blok sekcji równoleg³ych. Wskazówka dla kompilatora, kolejne sekcje mog¹ byæ wykonywane równolegle
		*/
		#pragma omp parallel sections default(none) firstprivate(A,p,r,q1)
    {
			/*
				sekcja
			*/
			#pragma omp section
      {
				int q2 = (p+q1)/2;
	
				/*
					blok sekcji zagnie¿d¿onych wewn¹trz jednej sekcji
				*/
				#pragma omp parallel sections default(none) firstprivate(A,p,r,q1,q2)
				{

					/*
						Zagnie¿d¿ona sekcja
					*/
					#pragma omp section
					{
						sortowanie_szybkie(A,p,q2);
					}
	  
					#pragma omp section
					{
						sortowanie_szybkie(A,q2+1,q1);
					}  
				}
	
				scal(A,p,q2,q1);
			}

			#pragma omp section
			{
	
				int q2 = (q1+1+r)/2;
	
				#pragma omp parallel sections default(none) firstprivate(A,p,r,q1,q2)
				{
	  
					#pragma omp section
					{
						sortowanie_szybkie(A,q1+1,q2);
					}
	  
					#pragma omp section
					{
						sortowanie_szybkie(A,q2+1,r);
					}
				}
				scal(A,q1+1,q2,r);
			}
		}
		scal(A,p,q1,r);
	}
  return;
}


