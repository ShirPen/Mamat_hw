#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRADE 100
#define MIN_GRADE 0
#define FAILED -1
#define DEFUALT_BINS_NUM 10

static FILE *f;
static int nbins = DEFUALT_BINS_NUM;

void parse_arg(int argc, char **argv);
void operate (int *bins);
int grade_check(int grade);

int main(int argc, char **argv) {

    parse_arg(argc, argv);

    /* Check for errors */
    if(!f){
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return(1);
    }

    /* Initialize array */
    int *bins = (int*)calloc(nbins, sizeof(int));
    
    if(bins == NULL){
    	fprintf(stderr, "Memoray allocation failed\n");
    	return(1);
    }

    operate(bins);
    free(bins);

    /* Close file if its open */
    if (f != NULL) {
        if(fclose(f) != 0 ){
            fprintf(stderr, "Failed to close file\n");
            return(1);
        }
    }
}


void parse_arg(int argc, char **argv){

    f = stdin;
    for (int i=1; i<argc; i++){
        if (!strcmp(argv[i], "-")){
            f = stdin;
        }
        else if (!strcmp(argv[i], "-nbins")){
            nbins = i<argc-1 ? atoi(argv[i+1]) : DEFUALT_BINS_NUM;
            i++;
        }
        else{
            f = fopen(argv[i], "r");
            if (f == NULL){
                fprintf(stderr, "Failed to open file\n");
                exit(1);
            }
        }
    }
}
void operate (int *bins){
    int grade;
    int retval;
    double pace;
    int line=1;

    while(1){
        retval = fscanf(f, "%d", &grade);
        if (retval == EOF){
            break; /* We have reached the end of the document */
        }

        else if (retval != 1){
            /* Error */
            fprintf(stderr, "Error: not a number\n");
            exit(1);
        }
        else if (grade_check(grade) == FAILED){
            /* Checks that grade is valid */
            fprintf(stderr, "Grade in line %d is not valid\n", line);
        }
        else{
            /* Find the right bin */
            int n = grade / (MAX_GRADE/nbins);
            if(grade == MAX_GRADE){
            	bins[n-1]++;
            }
            else{
                bins[n]++;
            }

        }
        line ++;
    }

    /*Print the bins */

    pace = MAX_GRADE /nbins;
    for (int i=0; i<nbins; i++){
        printf("%.0lf-%.0lf\t%d\n",
               i * pace,
               (i < nbins - 1) ? ((i+1)*pace-1) : MAX_GRADE,
               bins[i]);
    }
}
/*the above function checks the input stream to the program, as well as if the user has specified
 * a number of bins */

int grade_check( int grade){

    if(grade < MIN_GRADE || grade > MAX_GRADE){
        return FAILED;
    }
    else{
        return 0;
    }
}
