/*--------------------------------------------------------------------Breakpoints.c--------------------------------------------------------------------*/
/*
 * Created by Vishal Menon (Laziemo) in association with Richard Dobson (The Audio Programming Book)
 * Version 1.0: September 23, 2017
 * Envelope Generator Origins
 * 
 *Input:
 * - InputFile containing BreakPoint data
 *Output:
 * - Duration of the envelope
 * - Maximum Breakpoint value 
*/ 
/*--------------------------------------------------------------------Breakpoints.c--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define NPOINTS 64

typedef struct{
    double time;
    double value;
} BREAKPOINT;

BREAKPOINT* get_breakpoints(FILE* fp, unsigned long* psize);
BREAKPOINT max_point(const BREAKPOINT* points, unsigned long npoints);
//char* fgets(char* line, int maxline, FILE* fp)';
//int* sscanf(char* string, const char* format,..); returns number of succesful conversions made

/*--------------------------------------------------------------------main--------------------------------------------------------------------*/

int main(int argc, char* argv[] ){
    unsigned long size;
    double dur;
    BREAKPOINT* points;
    BREAKPOINT maxpoint;
    FILE* fp;
    
    printf("Breakpoints Program: Envelope Shaping Origins\n");
    
        if (argc != 2){
        printf("Insufficient command line arguments! Breakpoints takes 2 arguments. \n Usage: Breakpoints inputfile.txt \n");
        return 0;
        }
    
    fp = fopen(argv[1], "r"); //open file in read mode
        if(fp == NULL) return 0;
    
    size = 0;
    points = get_breakpoints(fp, &size);
    
        if(points==NULL){
        printf("No breakpoints read\n");
        fclose(fp);
        return 1;
        }
     
        if (size < 2){
        printf("Error: Atleast 2 breakpoints required!");
        free(points);
        fclose(fp);
        return 1;
        }
        
        if (points[0].time != 0){
            printf("Error in breakpoint data: First point must start at 0 time.");
            free(points);
            fclose(fp);
            return 1;
        }
    
    /*Error Checks Complete
     * 
     * Display Outputs
     */
    
    printf("read %lu breakpoints \n", size);
    dur = points[size-1].time;
    printf("Envelope Duration = %lf seconds \n", dur);
    maxpoint = max_point(points, size);
    printf("Maximum value: %lf at %lf seconds \n", maxpoint.value, maxpoint.time);
    free(points);
    fclose(fp);
    
return 0;
}
/*-----------------------------------------------------------------FUNCTION DEFINITIONS-----------------------------------------------------------------*/
/*
 * 
 */
BREAKPOINT* get_breakpoints(FILE* fp, unsigned long* psize){
    int got;
    unsigned long npoints = 0 , size = NPOINTS; // Envelope with 64 BREAKPOINTS = array of 64 BREAKPOINTS ~ Might have to increase the size
    double lasttime = 0.0;
    BREAKPOINT* points = NULL;
    char line[80];
    
        if (fp == NULL) return NULL;
    
    points = (BREAKPOINT*) malloc (size * sizeof(BREAKPOINT));
        if(points == NULL) return NULL;
        
    while(fgets(line,80,fp)){
        //Scan for errors in fgets output to line array
        got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value);
            if(got < 0) continue;
            if(got == 0) {
                printf("Line %lu has non-numeric data \n", npoints+1);
                break;
            }
            if(got == 1){
                printf("Incomplete breakpoint found at point %lu \n", npoints+1);
                break;
            }
            if(points[npoints].time < lasttime){
                printf("data error at point %lu: time not increasing \n", npoints+1);
                break;
            }

        lasttime = points[npoints].time;
        //Auto-increament through array 
            if(++npoints == size){ //While fgets - if more BREAKPOINT data exists than initial size allocated - reallocate memory and re-size
                BREAKPOINT* tmp;
                size += NPOINTS;
                tmp=(BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) * size);
                    if(tmp=NULL){
                        npoints=0;
                        free(points);
                        points = NULL;
                        break;
                    }
                    points = tmp;
            }
    }
        if(npoints) *psize = npoints;
                     
return points;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

BREAKPOINT max_point(const BREAKPOINT* points, unsigned long npoints){
    int i;
    BREAKPOINT point;
    
    point.time = points[0].time;
    point.value = points[0].value;
    
    for(i=1; i<npoints;i++){
        if(point.value<points[i].value){
            point.value = points[i].value;
            point.time = points[i].time;
        }
    }
    return point;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
