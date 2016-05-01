#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

#include "../inc/list.h"

void list_add(struct list *list, void *value) {
    struct list_element *new = malloc(sizeof *new);
    assert(new != NULL);
    new->value = value;
    new->next = list->first;
    list->first = new;
}

void list_remove(struct list *list, void *value) {
    struct list_element **element = &(list->first);
    while (*element != NULL) {
        if ((*element)->value == value) {
            struct list_element *tmp = *element;
            *element = (*element)->next;
            if (tmp == list->bookmark) list->bookmark = tmp->next;
            free(tmp);
        }
        else {
            element = &((*element)->next);
        }
    }
    // do something if value wasnt in list?
}

int list_length(struct list *list) {
    int i = 0;
    struct list_element *element = list->first;
    while (element != NULL) {
        ++i;
        element = element->next;
    }
    return i;
}


/*void list_print(struct list list) {
    struct list_element *element = list.first;
    while (element != NULL) {
        printf("%i ", *(int *)element->value);
        element = element->next;
    }
    printf("\n");
}

int main () {
    struct list test_list = {NULL};
    int a = 1, b = 2, c = 3;
    list_add(&test_list,&a);
    list_add(&test_list,&b);
    list_print(test_list);
    list_remove(&test_list,&b);
    list_print(test_list);
    return 0;
}
*/