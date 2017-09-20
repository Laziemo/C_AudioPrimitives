/* ------------------------------------------------MicroScale.c-------------------------------------------- */

/*Created by Vishal Menon (Laziemo) in association with Richard Dobson (The Audio Programming Book)
* Version 1.0: September 20, 2017
*
* A command-line tool to calculate micro-tone harmonics of a specified frequency.
* Designed for those kids that are bored of the chromatic scale.
*
*Input:
*	- Root frequency (r_freq)
*	- Octave Division (harmonics per octave)
*Output: 
*	- all N harmonics associated with the root frequency f_root.
*/

/* UPGRADES:
*Add functionality to hear each harmonic
*/

/* ------------------------------------------------MicroScale.c-------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char** argv) {
	
	double r_freq;
	double ratio;
	short interval;
	short i;
	double* harmonics;
	
	//Check for errors in arguments
	if(argc!=3) {
		printf("Bad Arguments: MicroScale takes 3 arguments. \n MicroScale.c <root_frequency> <scale_interval> \n");
		return 1;
	}
	
	//Store command-line arguments into local variables
	r_freq = atof(argv[1]);
	interval = atoi(argv [2]);
	
	//Calculate interval ratio
	ratio = pow(2.0 , 1.0/interval);
	
	//Create space to hold harmonics data
	harmonics = (double*) malloc (interval * sizeof(double));
	
	printf("Root Frequency = %lf Hz", r_freq);
	printf(" The harmonics of %lf Hz for a %i tone octave are : \n" ,r_freq, interval);
	
	//Populate and print harmonics vector
	for (i=0;i<=interval;i++) {
		*(harmonics+i) = r_freq;
		r_freq *= ratio;
		printf("H-%i   : %lf \n",i, *(harmonics+i));
	}
	
	//Clean up memory
	harmonics=NULL;
	free(harmonics);
	
	return 0;
}
