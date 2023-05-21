#include "student.h"
#include <string.h>

//Clones an element
elem_t student_clone (elem_t e){

    if(e == NULL){
        return NULL;
    }
    else {

        pstudent_t student_copy = malloc(sizeof(struct student));

        if (student_copy == NULL) {
            return NULL;
        }

        //Casts e into a student type
        pstudent_t  temp_student = (struct student*)e;

        student_copy->name = malloc(strlen(temp_student->name) + 1);
        strcpy(student_copy->name, temp_student->name);


        if(temp_student->age <= 0){
            free(student_copy);
            return NULL;
        }

        student_copy->age = temp_student->age;

        if(temp_student->id < 0){
            free(student_copy);
            return NULL;
        }

        student_copy->id = temp_student->id;

        return student_copy;

    }
}

//Destroys a student by freeing the memory
void student_destroy(elem_t e){

    //Casts e into a student type
    pstudent_t  student_dest = (struct student*)e;

    free(student_dest->name);
    free(student_dest);
}

//Prints all the fields of a student
void student_print(elem_t e){

    //Casts e into a student type
    pstudent_t  stud_p = (struct student*)e;

    printf("student name: %s, age: %d, id: %d.\n", stud_p->name, stud_p->age,
                                                    stud_p->id);
}
