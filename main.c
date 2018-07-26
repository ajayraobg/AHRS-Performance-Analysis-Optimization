/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
//*************************************************//
/*Project: AHRS Performace Analysis & optimization	*/
/*Author: Ajay Rao                   		   		*/
/*Affiliation: NCSU                   		   		*/
/*Version: 1.0										*/
/*E-mail:abrao2@ncsu.edu                      		*/
//*************************************************//
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include "MadgwickAHRS.h"


#define N_TESTS (1000)

#define base 1 		 //Set this to 1 for running the basic version and to populate "op_base_log.txt". Set this to 1 for other optimzed version and to populate "op_log"

#define validate 0   //Set this to 1 for validating the o/p of base function v/s optimized function. Run this after executing the function with base set to 0 and 1 atleast once.

#if 0				//Set this to 1 while doing the step 5 of the optimization and beyond
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;  
#endif


float randGen(float lower, float upper){
	float num = fmod((rand() + lower),(upper + 1));
	return num;
}


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/

int main (void) {
	if (validate == 0) {
		float gx,gy,gz,mx,my,mz,ax,ay,az;
		struct timespec start, end;
		unsigned long diff,total=0,min=1234567890;
		int n=0,flag_a,flag_m;
		FILE *fp1 ,*fp2;
		if (base == 1){
			fp1 = fopen("op_base_log.txt","w+");
		}
		else{
			fp2 = fopen("op_log.txt","w+");
		}


		for (n=0; n<N_TESTS; n++) {
	  		gx = randGen(-10.0,10.0);
	  		gy = randGen(-10.0,10.0);
	  		gz = randGen(-10.0,10.0);
	  		mx = randGen(-100.0,100.0);
	 		my = randGen(-100.0,100.0);
	  		mz = randGen(-100.0,100.0);
	  		ax = randGen(-1000.0,1000.0);
	  		ay = randGen(-1000.0,1000.0);
	  		az = randGen(-1000.0,1000.0);

	  		if (((int)az == 0) && ((int)ay == 0) && ((int)az == 0)){
				flag_a = 1;
	  		}
	  		else{
		  		flag_a = 0;
	  		}
	  		if (((int)mx == 0) && ((int)my == 0) && ((int)mz == 0)){
	  			flag_m = 1;
	 		 }
	  		else{
				flag_m = 0;
	  		}	  
	  		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
	  		MadgwickAHRSupdate(gx,gy,gz,ax,ay,az,mx,my,mz,flag_a,flag_m);
	  		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);	  


	  		if(base == 1){
	  			fprintf(fp1,"%f\n%f\n%f\n%f\n",q0,q1,q2,q3);
	  		}
	  		else{
	  			fprintf(fp2,"%f\n%f\n%f\n%f\n",q0,q1,q2,q3);
	 		}	  

	  
	  		diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	  		total += diff;
	  		if (diff < min)
	   			min = diff;
		  
		}

		if(base == 1){		
			fclose (fp1);
		}
		else{
			fclose (fp2);
		}

		printf("Average %10.3f us\n",total/(1000.0*N_TESTS));
		printf("Minimum %10.3f us\n", min/1000.0);

}

	if (validate == 1){

		int  i=0,j=0;
    	double numbers[4000];
   		double numbers_1[4000];
    	double atof ( const char * str );
    	char line[4000];  /* declare a char array */
    	char line_1[4000];

    	FILE *file, *file1;  /* declare a FILE pointer  */
    	file = fopen("op_base_log.txt", "r");  /* open a text file for reading */
    	file1 = fopen("op_log.txt", "r");

    	while(fgets(line, sizeof line, file)!=NULL) {       /* keep looping until NULL pointer... */
        	numbers[i]=atof(line);  /* convert string to double float*/
        	i++;
    	}
    	while(fgets(line_1, sizeof line_1, file1)!=NULL) {       /* keep looping until NULL pointer... */
			numbers_1[j]=atof(line_1);  /* convert string to double float*/
        	j++;
    	}


    	for (i=0 ; i<4000 ; i++) {
        	if(fabs(numbers[i])>fabs(numbers_1[i])){
            	if((((fabs(numbers[i]) - fabs(numbers_1[i]))/fabs(numbers[i]))/100) > 0.001){
                	printf("Error greater than 0.01 for %f %f \n",numbers[i],numbers_1[i]);
          		}
          	}
        	else{
                if((((fabs(numbers_1[i]) - fabs(numbers[i]))/fabs(numbers_1[i]))/100) > 0.001){
                    printf("Error greater than 0.01 for %f %f \n",numbers[i],numbers_1[i]);
                }
            }
		}
    	fclose(file);
    	fclose(file1);
	}

	exit(0);

}




