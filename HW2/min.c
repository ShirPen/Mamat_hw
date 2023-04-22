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

void operate( FILE *f){

    int grade;
    int retval;
    int curr_min;
    int line = 1;

    curr_min = 100;

    while(1){
        retval = fscanf(f, "%d", &grade);
        if( retval == EOF){
            break; /* Finished */
        }
        else if(retval != 1){
            /* Error */
        }
        else if (grade_check(grade) == -1){
            /* Checks that grade is valid */
            fprintf(stderr, "Grade in line %d is not valid\n", line);
        }
        else{
            if( grade < curr_min){
                curr_min = grade;
            }
        }
        line ++;
    }

    printf("%d\t", curr_min);
}

int grade_check( int grade){

    if(grade<0 || grade > 100){
        return -1;
    }
    else{
        return 0;
    }
}


