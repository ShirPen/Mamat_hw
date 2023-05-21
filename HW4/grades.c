#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grades.h"
#include "linked-list.h"


typedef enum { SUCCESS = 0, FAIL = 1, ERROR = -1} Result;

typedef struct list* list_p;

typedef struct course{
    char* course_name;
    int course_grade;
}*pcourse;

typedef struct student{
    int id;
    char* name;
    int course_total;
    int course_amnt;
    list_p course_list;

}*pstudent;

typedef struct grades{
   list_p student_list;
}*pgrades;



/*----------------Function Declaration----------------*/
pstudent check_student(int id, pgrades grades_m);
int check_course(const char *course_name, pstudent student);
int course_clone (void *element, void **output);
int student_clone (void *element, void **output);
void student_destroy(void* element);
void course_destroy(void* element);
void print_student(pstudent student);



/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, or NULL in case of an error
 */
struct grades* grades_init(){

    pgrades grades = malloc(sizeof(struct grades));

    if(grades == NULL){
        fprintf(stderr, "Error: malloc grades failed\n");
        return NULL;
    }
    grades->student_list = list_init(student_clone,
                                student_destroy);
    return grades;
}

/**
 * @brief destroys grades
 * @param grades pointer to the grades list
 */

void grades_destroy(struct grades *grades){

    list_destroy(grades->student_list);
//    pstudent curr_student = (struct student*) grades->student_list;
//    struct iterator* current = (struct iterator *) grades->student_list;
//
//    //Loop that free's all the grade's students
//    while(current != NULL){
//        student_destroy(curr_student);
//        current = list_next(current);
//        curr_student = (struct course*) current;
//    }

    free(grades);
}

/**
 * @brief creates a student course list
 * @returns A pointer to the data-structure, or NULL in case of an error
 */

struct student* student_init(const char* name, int id){
    pstudent student = malloc(sizeof(struct student));
    if(student == NULL) {
        return NULL;
    }

    student->course_list = NULL;
    student->id = id;
    student->name = malloc(strlen(name) + 1);
    student->course_total = 0;
    student->course_amnt = 0;
    strcpy(student->name, name);
    return student;
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or a student with
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id){

    if(grades == NULL){
        return FAIL;
    }

    if(check_student(id, grades) != NULL){
        return FAIL;
    }
    else{
        pstudent new_student = student_init(name, id);
        list_push_back(grades->student_list, new_student);
        return SUCCESS;
    }
}

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Fails if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

    if(grades == NULL){
        return FAIL;
    }

    if(grade < 0 || grade > 100){
        return FAIL;
    }

    //Finds the student in the list
    pstudent student = check_student(id, grades);

    //Checks if course exists
    int res = check_course(name, student);
    if(res == FAIL){
        return FAIL;
    }

    pcourse course = malloc(sizeof(struct course));

    course->course_name = malloc(strlen(name) + 1);
    strcpy(course->course_name, name);
    course->course_grade = grade;

    list_push_back(student->course_list, course);
    student->course_amnt ++;
    student->course_total += grade;


    return SUCCESS;

}

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out){

    if(grades == NULL){
        return ERROR;
    }

    //Finds the student
    pstudent student = check_student(id, grades);

    if( student == NULL){
        return ERROR;
    }

    if(student->course_amnt == 0){
        return 0;
    }
    else{
        *out = student->name;
        return (student->course_total)/(student->course_amnt);
    }


}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id){
    if(grades == NULL){
        return FAIL;
    }

    //Finds the student
    pstudent student = check_student(id, grades);

    if( student == NULL){
        return FAIL;
    }

    print_student(student);

    return SUCCESS;

}

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades){

    if(grades == NULL){
        return FAIL;
    }

    // Start with the head of the linked list
    struct iterator* current = list_begin(grades->student_list);

    pstudent curr_student;

    while(current != NULL){

    	curr_student = list_get(current);
        print_student(curr_student);
        current = list_next(current);

    }

    return SUCCESS;
}


/**
 * @brief clones a course
 * @param element pointer to the course to be cloned
 * @param output pointer to the pointer to the cloned course
 * @returns 0 for success, 1 for fail
 */

int course_clone (void *element, void **output){
    if(element == NULL){
        return FAIL;
    }
    else {

        pcourse course_copy = (pcourse)malloc(sizeof(struct course));

        if (course_copy == NULL) {
        	*output= NULL;
            return FAIL;
        }

        //Casts element into a course type
        pcourse  orig_course = (struct course*)element;

        course_copy->course_name = malloc(strlen(orig_course->course_name) + 1);
        strcpy(course_copy->course_name, orig_course->course_name);


        if(orig_course->course_grade < 0 || orig_course->course_grade > 100){
            free(course_copy->course_name);
            free(course_copy);
            *output= NULL;
            return FAIL;
        }

        course_copy->course_grade = orig_course->course_grade;
        *output= course_copy;

        return SUCCESS;

    }
}


/**
 * @brief clones a course
 * @param element pointer to the course to be cloned
 * @param output pointer to the pointer to the cloned course
 * @returns 0 for success, 1 for fail
 */

void course_destroy(void* element){

    pcourse course_dest = (struct course*)element;
    free(course_dest->course_name);
    free(course_dest);
}

/**
 * @brief clones a student
 * @param element pointer to the student to be cloned
 * @param output pointer to the pointer to the cloned student
 * @returns 0 for success, 1 for fail
 */

int student_clone (void *element, void **output){
    if(element == NULL){
        return FAIL;
    }
    else {

        pstudent student_copy = malloc(sizeof(struct student));

        if (student_copy == NULL) {
        	*output= NULL;
            return FAIL;
        }

        //Casts e into a student type
        pstudent  orig_student = (struct student*)element;

        student_copy->name = malloc(strlen(orig_student->name) + 1);
        strcpy(student_copy->name, orig_student->name);

        /*clone is only used when adding a student and thus new student will
                                                                 have avg 0*/
        student_copy->course_total = 0;
        student_copy->course_amnt = 0;

        if(orig_student->id < 0){
            free(student_copy);
            *output= NULL;
            return FAIL;
        }

        student_copy->id = orig_student->id;
        student_copy->course_list = list_init(course_clone, course_destroy); // Initialize the courses list, if needed
        *output= student_copy;

        return SUCCESS;

    }
}



/**
 * @brief clones a course
 * @param element pointer to the course to be cloned
 * @param output pointer to the pointer to the cloned course
 * @returns 0 for success, 1 for fail
 */

void student_destroy(void* element){

    pstudent student_dest = (struct student*)element;

    free(student_dest->name);

    list_destroy(student_dest->course_list);

//    pcourse curr_course = (struct course*) student_dest->course_list;
//    struct iterator* current = (struct iterator *) student_dest->course_list;
//
//    //Loop that free's all the student's courses
//    while(current != NULL){
//        course_destroy(curr_course);
//        current = list_next(current);
//        curr_course = (struct course*) current;
//    }

    free(student_dest);

}


/**
 * @brief checks the linked list students for a course num
 * @param course_name course number to be checked
 * @param student pointer to the student
 * @returns 0 for success, 1 for fail
 */
int check_course(const char *course_name, pstudent student){

// Start with the head of the linked list
    struct iterator* current = list_begin(student->course_list);

    pcourse check;

    while(current != NULL){

    	check = (struct course*)list_get(current);

        if(strcmp(course_name, check->course_name) == 0 ){
            return FAIL;
        }
        else{
            current = list_next(current);
        }

    }

    //We have reached the end of the list with no copies of the course name
    return SUCCESS;
}



/**
 * @brief checks the linked list grades for an id
 * @param id id to be checked
 * @param grades pointer to the linked list
 * @returns pointer to student or NULL if student doesnt exist
 */
pstudent check_student(int id, pgrades grades_m){

// Start with the head of the linked list
    struct iterator* current = list_begin(grades_m->student_list);

    pstudent check;

    while(current != NULL){

    	check = (struct student*)list_get(current);

        if(check->id == id){
            return check;
        }
        else{
            current = list_next(current);
        }

    }

    //We have reached the end of the list with no copies of the id
    return NULL;
}

void print_student(pstudent student){

    printf("%s %d: ",student->name, student->id);

    // Start with the head of the linked list
    struct iterator* current = list_begin(student->course_list);

    pcourse curr_course;

    for(int i = 0; i<student->course_amnt-1; i++){
    	curr_course=(struct course*)list_get(current);
        printf("%s %d,", curr_course->course_name, curr_course->course_grade);
        current = list_next(current);
    }

    printf("%s, %d\n", curr_course->course_name, curr_course->course_grade);
}
