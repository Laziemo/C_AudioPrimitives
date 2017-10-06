/*-------------------------------------------------------------ExpEnv.c-------------------------------------------------------------*/
/*
 * Created by Vishal Menon in association with Richard Dobson (Audio Programming Book)
 * Implementation of exponential attack and decay curves
 *
 *Input:
 *	- Duration (duration)
 *	- Number of Points/Ticks (npoints)
 *  - Start time value (startvalue)
 *  - End time value (endvalue)
 *Output: 
 *	- Exponentially decreasing or increasing values from startvalue to endvalue
 USAGE:
 * Multiply output to an audio buffer to apply expoential envelope shaping
*/

/*-------------------------------------------------------------ExpEnv.c-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*-------------------------------------------------------------main-------------------------------------------------------------*/

int main (int argc, char* argv []){
    
    int i, nsteps;
    double startval, endval;
    double dur, step, start, end, thisstep;
    double fac, valrange, offset;
    const double verysmall = 1.0e-4; // ~-80 db     
 
        if(argc != 5){
            printf("Insufficient Command Line Arguments! \n Usage: expenv duration npoints startvalue endvalue");
            return 1;
        }
    
    dur = atof(argv[1]);
        if(dur <= 0.0){
            fprintf(stderr, "Error: duration time must be positive");
            return 1;
        }
        
    nsteps = atoi(argv[2]);
        if(nsteps <= 0.0){
            fprintf(stderr, "Error: steps time must be positive");
            return 1;
        }
        
    step = dur/nsteps; //constant time increment
    startval = atof(argv[3]);
    endval = atof(argv[4]);
    valrange = endval -startval;
    
        if(valrange ==0.0){
            fprintf(stderr, "Error: Start and End values are the same! \n");
            return 1;
        }
    
        if (startval > endval){
            start = 1.0;
            end =  verysmall;
            valrange = -valrange;
            offset = endval;
        }
        else{
            start = verysmall;
            end = 1.0;
            offset = startval;
        }
        
    thisstep = 0.0;
        
    fac = pow(end/start, 1.0/nsteps); //MAIN FORMULA IMPLEMENTATION where fac=factor or ratio
    
        for (i=0; i<nsteps;i++){
            fprintf(stdout, "%.4lf \t %.8lf \n" , thisstep, offset + (start * valrange));
            start *= fac;
            thisstep += step;
            }
            
    fprintf(stdout, "%.4lf \t .8lf \n", thisstep, offset + (start * valrange));
        
    fprintf(stderr, "DONE! \n");
    
return 0;
    
  
}
/*-------------------------------------------------------------main-------------------------------------------------------------*/
