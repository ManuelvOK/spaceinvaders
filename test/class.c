#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "dict.h"
#include "dict.c"

struct class;
struct method;
struct object;

struct class {
    struct class *superclass;
    void (*initialiser)(struct object *);
    void (*finaliser)(struct object *);
    struct dict *methods;
};

struct object{
    struct class *class;
    struct dict *data;
};

struct method {
    unsigned int argc;
    void *(*function)(struct object *, va_list);
};

struct class *create_class(struct class *superclass, void (*initialiser)(struct object *), void (*finaliser)(struct object *)) {
    struct dict *methods = new_dict();
    struct class *new_class = malloc(sizeof *new_class);
    assert(new_class != NULL);
    new_class->superclass = superclass;
    new_class->initialiser = initialiser;
    new_class->methods = methods;
    return new_class;
}

struct object *create_from(struct class *class) {
    struct object *new_object;
    if (class->superclass != NULL) {
        new_object = create_from(class->superclass);
    } else {
        new_object = malloc(sizeof *new_object);
        assert(new_object != NULL);
        new_object->data = new_dict();
    }
    new_object->class = class;
    if (class->initialiser != NULL) {
        class->initialiser(new_object);
    }
    return new_object;
}

void delete_object(struct object *object) {
    struct class *class = object->class;
    while (class != NULL) {
        if (class->finaliser != NULL) {
            class->finaliser(object);
        }
        class = class->superclass;
    }
    free(object);
}

void register_method(struct class *class, int methodkey, void *(*function)(struct object *, va_list) ) {
    struct method *new_method = malloc(sizeof *new_method);
    assert(new_method!=NULL);
    new_method->function = function;
    dict_add(class->methods,methodkey,new_method);    
}

void call (struct object *object, int methodkey, ... ) {
    va_list args;
    va_start(args,methodkey);
    printf("key %i\n", methodkey);
    struct method *method = NULL;
    struct class *class = object->class;
    while (1) {
        assert(class!=NULL); //asserts if method wasn't found in any class or superclass
        method = dict_get(class->methods,methodkey);
        if (method != NULL) break;
        class = class->superclass;
    }
    method->function(object, args);
}

// TESTING AREA:

enum {TEST = 0
};

void *test1(struct object *object, va_list args) {
    printf("ge1testet");
    return NULL;
}

int main () {
    struct class *myclass = create_class(NULL,NULL,NULL);
    register_method(myclass,TEST,test1);
    struct object *myobject = create_from(myclass);
    call(myobject,TEST);
    delete_object(myobject);
    return 0;
}
