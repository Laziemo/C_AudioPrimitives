/*--------------------------------------------------------------------SineDec.c--------------------------------------------------------------------*/
/*
 * Created by Vishal Menon (Laziemo) in association with Richard Dobson (The Audio Programming Book)
 * Version 1.0: October 06, 2017
 * Combining ExpDec.c and Sinewave.c to generate a sinewave file with exponential decay
 *
 *Input:
 * - .txt file containing audio data (fp)
 * - Duration (dur)
 * - Sinewave Frequency (freq)
 * - Sample Rate (srate)
 * - Amplitude (amp)
 *
 *Output:
 * - FILE containing sinwave data with exponential decay
 * 
 *UPGRADES: 
 * Create and EXPPitchDec -> Getting close to a kick drum
 *
*/ 
/*--------------------------------------------------------------------SineDec.c--------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.141592654
#endif

enum {ARG_NAME,
		ARG_OUTFILE, 
		ARG_DUR, 
		ARG_HZ, 
		ARG_SR, 
		ARG_AMP, 
		ARG_NARGS};

/*--------------------------------------------------------------------main--------------------------------------------------------------------*/


int main(int argc, char** argv){
	int i, nsamps, srate;
	double samp, dur, freq, amp, maxsamp;
	double start, end, fac, angleincr;
	double twopi = 2.0 * M_PI;
	FILE *fp = NULL;
	
		if (argc != ARG_NARGS){
			fprintf(stderr, "Bad Usage \n Correct Usage: sindec sound.txt dur freq srate amp \n");
			return 1;
		}
	
	fp = fopen (argv[ARG_OUTFILE], "w");
	
		if (fp == NULL){
			fprintf(stderr, "Error creating file \n");
			return 1;
		}
		
	dur = atof(argv[ARG_DUR]);
	freq = atof(argv[ARG_HZ]);
	srate = atoi(argv[ARG_SR]);
	amp = atof(argv[ARG_AMP]);
	
	nsamps = (int) (dur * srate);
	angleincr = (freq * twopi) / srate;
	
	start = 1.0;
	end = 1.0e-4;
	maxsamp = 1.0e-4 ;
	
    //What will happen: start/end? Attack? Find out...
	fac = pow(end/start,1.0/nsamps); 
		//Sine Generator
		for(i = 0 ; i<nsamps; i++){
			samp = amp * sin(angleincr * i);
            //Exponential Decay
			/*samp *= start;
			start *= fac; 
			*/
			fprintf(fp, "%0.8lf \n", samp);
			
            //Report the maximum amplitude of the signal
				if(fabs(samp) > maxsamp) {
					maxsamp = fabs(samp);
				}
		}
		
		fclose(fp);
		
		fprintf(stderr, "DONE! Maximum Sample Value = %0.8lf \n", maxsamp);
		
return 0;
}
	
/*--------------------------------------------------------------------main--------------------------------------------------------------------*/
	
	
