#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct stack {
    size_t max_size;
    size_t curr_size;
    elem_t *data; //points to first element in array of "elem_t"s
    clone_t clone_func;
    destroy_t destroy_func;
    print_t print_func;
};

//Creates the stack, user must supply clone, destroy, and print functions
pstack_t stack_create(size_t max_num_of_elem, clone_t clone_func,
                      destroy_t destroy_func, print_t print_func){

    pstack_t stack_ptr = malloc(sizeof (struct stack));
    //allocates memory for the struct "stack"

    if(stack_ptr == NULL){
        fprintf(stderr, "Error: memory allocation for stack failed\n");
        return NULL;
    }

    stack_ptr->data = malloc(sizeof (elem_t)*max_num_of_elem);
    //allocates memory for the actual array of elements

    if(stack_ptr->data == NULL){
        fprintf(stderr, "Error: memory allocation for array failed\n");
        free(stack_ptr);
        return NULL;
    }

    stack_ptr->max_size = max_num_of_elem;
    stack_ptr->curr_size = 0;
    stack_ptr->clone_func = clone_func;
    stack_ptr->destroy_func = destroy_func;
    stack_ptr->print_func = print_func;

    if(max_num_of_elem <= 0){
        fprintf(stderr, "Error: stack size is invalid\n");
        free(stack_ptr);
        free(stack_ptr->data);
        return NULL;
    }
/*---------------------Pointer Function Check---------------------*/
    if(clone_func == NULL){
        fprintf(stderr, "Error: clone function points to null\n");
        free(stack_ptr);
        free(stack_ptr->data);
        return NULL;
    }
    if(destroy_func == NULL){
        fprintf(stderr, "Error: destroy function points to null\n");
        free(stack_ptr);
        free(stack_ptr->data);
        return NULL;
    }
    if(print_func == NULL){
        fprintf(stderr, "Error: print function points to null\n");
        free(stack_ptr);
        free(stack_ptr->data);
        return NULL;
    }

    return stack_ptr;

}

//Given a pointer to a stack, it free's the memory thus destroying the stack
Result stack_destroy(pstack_t stack){

    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return FAIL;
    }

    //Destroys each element in the magazine one by one using stack_pop
    while(stack->curr_size !=0){
       stack_pop(stack);
    }

    if(stack->data != NULL){
        free(stack->data);
    }

    free(stack);
    return SUCCESS;
}

//Given an element supplied by the user and a stack, it will add said element
Result stack_push(pstack_t stack, elem_t new_elem){

    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return FAIL;
    }

    if(new_elem == NULL){
        fprintf(stderr, "Error: element added points to NULL\n");
        return FAIL;
    }

    //Checks there is room in magazine
    if(stack->curr_size >= stack->max_size){
        fprintf(stderr, "Error: no room in stack\n");
        return FAIL;
    }

    elem_t elem_clone = stack->clone_func(new_elem);

    if(elem_clone == NULL){
        fprintf(stderr, "Error: failed to copy element\n");
        return FAIL;
    }
    else{
        stack->data[stack->curr_size] = elem_clone; //pointer arithmetic to get
                                                    //correct space in array
        stack->curr_size++;
        return SUCCESS;
    }


}

//Given a stack, the last element in will be taken out and its memory freed
//The user must supply the destroy function
void stack_pop(pstack_t stack){

    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return;
    }

    if(stack->curr_size == 0){
        fprintf(stderr, "Error: stack is empty\n");
        return;
    }
    else{
        elem_t popped = stack->data[stack->curr_size -1]; //go to last element
        stack->destroy_func(popped);
        stack->curr_size--;

    }
}

//Given a stack, the top element value will be returned (and no changes occur)
elem_t stack_peek(pstack_t stack){

    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return NULL;
    }

    if(stack->curr_size == 0){
        return NULL;
    }
    else{
        return stack->data[(stack->curr_size) - 1];
    }
}

//Given a stack, the amount of elements in the stack will be returned
size_t stack_size(pstack_t stack){

    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return FAIL;
    }

    return stack->curr_size;
}

//Given a stack, it will return if a stack is at max capacity or not
bool stack_is_empty(pstack_t stack){

    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return 0;
    }
    if(stack->curr_size == 0){
        return 1;
    }
    else{
        return 0;
    }
}

//Given a stack, it will return the availabe space in said stack
size_t stack_capacity(pstack_t stack){

    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return FAIL;
    }

    return (stack->max_size - stack->curr_size);

}

//Prints all the elements in the stack
void stack_print(pstack_t stack){
    if(stack == NULL){
        fprintf(stderr, "Error: stack points to NULL\n");
        return;
    }
    for(int i=(stack->curr_size) -1; i>=0; i--){
        stack->print_func(stack->data[i]);
    }
}


