#ifndef __STUDENT__
#define __STUDENT__

#include "stack.h"
#include "stdlib.h"

typedef struct student {
	char *name;
	int age;
    int id;
}*pstudent_t, student_t;

elem_t student_clone (elem_t e);
/* ------------------------------------------ */
void student_destroy(elem_t e);
void student_print(elem_t e);
/* ------------------------------------------ */

#endif /* __STUDENT__ */ 