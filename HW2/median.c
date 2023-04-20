#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void operate(FILE *f);
int grade_check( int grade);

int main(int argc, char **argv){

    FILE *f;

    if (argc == 1 || !strcmp("-", argv[1])){
        f = stdin;
    }
    else{
        f = fopen(argv[1], "r");
    }

    /* Check for errors */
    if(!f){
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return(1);
    }

    operate(f);

    /* Close file if its open */
    if (f != NULL) {
        fclose(f);
    }
}


// Driver function
void operate(FILE *f)
{
	int grades[100] = {0};
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
	    else if (grade_check(grade) == -1){
	    	/* Checks that grade is valid */
	    	fprintf(stderr, "Grade in line %d is not valid", line);
	        }
	    else{
	    	grades[grade] ++;
	        amount ++;
	    }
	    line ++;
	}
	int i;
	for (i = 0; i < 100 ; i++){
		stop += grades[i];
		if(stop >= (amount+1)/2){
			break;
		}
	}
	printf("%d", i);

}

int grade_check( int grade){

    if(grade<0 || grade > 100){
        return -1;
    }
    else{
        return 0;
    }
}
