#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "dict.h"

struct item {
    int key;
    void *value;
    struct item *next;
};

struct dict {
    struct item *first;
};

struct dict *new_dict() {
    struct dict *dict = malloc(sizeof *dict);
    dict->first = NULL;
    return dict;
}

void del_dict(struct dict *dict);
// yet to be implemented

void dict_add(struct dict *dict, int key, void *value) {
    struct item *new_item = malloc(sizeof *new_item);
    assert(new_item != NULL);
    new_item->key = key;
    new_item->value = value;
    new_item->next = dict->first;
    dict->first = new_item;
    
}

void dict_remove(struct dict *dict, int key);
// yet to be implemented

void *dict_get(struct dict *dict, int key) {
    struct item *item = dict->first;
    while (item != NULL) {
        if (item->key == key) return item->value;
        item = item->next;
    }
    return NULL;
}

/*
int main () {
    int x,y;
    x = 7;
    y = 42;
    struct dict *mydict = new_dict();
    dict_add(mydict,x,&y);
    int *r = dict_get(mydict,x);
    assert(r != NULL);
    printf("%i",*r);
    return 0;
}
*/