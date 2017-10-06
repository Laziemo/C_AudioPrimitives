/*--------------------------------------------------------------------Sinewave.c--------------------------------------------------------------------*/
/*
 * Created by Vishal Menon (Laziemo) in association with Richard Dobson (The Audio Programming Book)
 * Version 1.0: October 6, 2017
 * Sine Wave Generator Origins
 * Write a sine wave as text
 * 
 *Input: 
 * - Number of samples that represent the sound <duration*samplerate> (nsamps)
 * - Sinewave frequency to generate (freq)
 * - Sample Rate (srate)
 * 
 *Output:
 * - Sinewave Data
 *
 * USAGE: 
 * The > symbol can be used after command line arguments followed by a filename.txt to copy the contents of stdout to a .txt file 
 *
*/ 
/*--------------------------------------------------------------------Sinewave.c--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MY_PI (3.141592654)
//Easier way to recognize command line arguments
enum {ARG_NAME, ARG_NSAMPS,ARG_FREQ,ARG_SR,ARG_NARGS};
/*--------------------------------------------------------------------main--------------------------------------------------------------------*/

int main(int argc, char** argv){
    int i, nsamps, srate;
    double samp, freq;
    double twopi = 2.0 * MY_PI;
    double angleincr;
    
    if(argc != ARG_NARGS){
        fprintf(stderr,"Bad Usage.\n Correct Usage: S nsamps freq srate\n");
        return 1;
    }
    
    nsamps = atoi(argv[ARG_NSAMPS]);
    freq = atof(argv[ARG_FREQ]);
    srate = atoi(argv[ARG_SR]);
    
    angleincr = twopi*freq/nsamps;
    
        for(i=0; i<nsamps; i++){
            samp = sin(angleincr * i);
            fprintf(stdout, "%.8lf\n", samp);
        }
        
    fprintf(stderr, "DONE!\n");
        
return 0;

}

/*--------------------------------------------------------------------main--------------------------------------------------------------------*/
