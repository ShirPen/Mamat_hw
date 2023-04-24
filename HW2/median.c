#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_GRADE 100
#define MIN_GRADE 0
#define FAILED -1

void operate(FILE *f);
int grade_check( int grade);

int main(int argc, char **argv){

    FILE *f;

    if (argc == 1 || !strcmp("-", argv[1])){
        f = stdin;
    }
    else{
        f = fopen(argv[1], "r");
        if(f == NULL ){
            fprintf(stderr, "Failed to open file\n");
            return(1);
        }
    }

    /* Check for errors */
    if(!f){
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return(1);
    }

    operate(f);

    /* Close file if its open */
    if (f != NULL) {
        if(fclose(f) != 0 ){
            fprintf(stderr, "Failed to close file\n");
            return(1);
        }
    }
}


// Driver function
void operate(FILE *f){
    int grades[MAX_GRADE +1] = {MIN_GRADE};
    int grade;
    int retval;
    int line = 1;
    int amount = 0;
    int stop = 0; //stop condition for finding median

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
	    	grades[grade] ++;
	        amount ++;
	    }
	    line ++;
	}
	int i;
	for (i = MIN_GRADE; i <= MAX_GRADE ; i++){
		stop += grades[i];
		if(stop >= (amount+1)/2){
			break;
		}
	}
	printf("%d\t", i);

}

int grade_check( int grade){

    if(grade < MIN_GRADE || grade > MAX_GRADE ){
        return FILED;
    }
    else{
        return 0;
    }
}
