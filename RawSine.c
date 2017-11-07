/* ------------------------------------------------RawSine.c-------------------------------------------- */

/*Created by Vishal Menon (Laziemo) in association with Richard Dobson (The Audio Programming Book)
* Version 1.0: October 25th, 2017
*
* Generate Raw Binary Sinewave with native endianess check
* 
*
*Input:
*	- File Name
*	- Sample Duration
*   - Frequency
*   - Sample Rate
*   - Amplitude
*   - Sample Type
*Output: 
*	- Raw Binary Sinewave Sample
*/

/* ------------------------------------------------RawSine.c-------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#ifndef M_PI
#define M_PI  (3.141592654)
#endif

enum { ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_FREQ, ARG_SR, ARG_AMP, ARG_TYPE,ARG_NARGS };
enum samptype {RAWSAMP_SHORT, RAWSAMP_FLOAT};
//Check endianness
//This function uses a pointer to check how data is stored on the native system
int byte_order(){
    int one = 1;
    char* endptr = (char*) &one;
    return (*endptr);
//If the value returned is 1 that means the MSB is to the left and therefore big_endian
}

const char* endianess[2] = { "big_endian", "little_endian" };

/*-------------------------------------------------main-----------------------------------------------------*/

int main(int argc, char** argv) {
	
    unsigned long i, nsamps;
    unsigned int maxframe = 0;
    unsigned int samptype, endian, bitreverse;
    double samp, dur, freq, srate, amp, step;
    double start, end, fac, maxsamp;
    double twopi = 2 * M_PI;
    double angleincr;
    
    FILE* fp = NULL;
    float fsamp;
    short ssamp;
    
    
	
	//Check for errors in arguments
	if(argc!=ARG_NARGS) {
		printf("Bad Arguments: RawSine takes 6 arguments. \n ./RawSine outfile.raw dur freq srate amp isfloat\n");
		return 1;
	}
	
	fp = fopen (argv[ARG_OUTFILE], "wb");
    if (fp==NULL){
        fprintf(stderr, "Error creating output file");
        return 1;
    }
    
    dur = atof(argv[ARG_DUR]);
	freq = atof(argv[ARG_FREQ]);
    srate = atof(argv[ARG_SR]);
    amp = atof(argv[ARG_AMP]);
    
    samptype = (unsigned int) atoi (argv[ARG_TYPE]);
    if(samptype > 1){
        printf("error: sampletype can be only 0 or 1!\n");
        return 1;
    }
    
    
    nsamps = (unsigned long) (dur * srate);
    
    step =  dur/nsamps;
    angleincr = freq * twopi / srate;
    
    
    start = 1.0; //Normalized 
    end = 1.0e-4;
    maxsamp = 0.0;
    
    fac = pow(end/start, 1.0/nsamps);
    
    endian = byte_order();
    fprintf(stderr, "Writing %d %s samples \n", nsamps, endianess[endian]);
    
    /*LOOP BASED ON SAMPLE TYPE*/
    
    if(samptype == RAWSAMP_SHORT){
        for (i=0; i<nsamps; i++){
            samp =  amp * sin (angleincr*i);
            samp *= start;
            start *= fac;
            
            ssamp = (short) (samp * 32767); // Mapped between -32767 to +32767; since short's range is -32768 to -32767
            
            if(fwrite(&ssamp, sizeof(short), 1, fp) != 1){
                fprintf(stderr, "Error writing data to file\n");
                return 1;
            }
            
            //Calculate max sample and its position
            if (fabs(samp)>maxsamp){
                maxsamp = fabs(amp);
                maxframe = 1;
            }
        }
    }
    
    else{
        for (i=0; i<nsamps; i++){
            samp =  amp * sin (angleincr*i);
            samp *= start;
            start *= fac;
            fsamp = (float) samp;
            
            if(fwrite(&fsamp, sizeof(float), 1, fp) != 1){
                fprintf(stderr, "Error writing data to file\n");
                return 1;
            }
            
            if (fabs(samp)>maxsamp){
                maxsamp = fabs(amp);
                maxframe = 1;
            }
        }
    }
    
    fclose(fp);
    fprintf(stderr,"DONE! Maximum Sample Value = %.8lf at frame %d \n", maxsamp, maxframe);
    
	return 0;
}
