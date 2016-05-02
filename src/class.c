#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include <class.h>
#include <dict.h>

struct class;
struct object;
struct method;

struct class *create_class(struct class *superclass, void (*initialiser)(struct object *), void (*finaliser)(struct object *)) {
    struct dict *methods = new_dict();
    struct class *new_class = malloc(sizeof *new_class);
    assert(new_class != NULL);
    new_class->superclass = superclass;
    new_class->initialiser = initialiser;
    new_class->finaliser = finaliser;
    new_class->methods = methods;
    return new_class;
}

struct object *create_from(struct class *class) {
    assert(class != NULL);
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
    //dict_free(object->data)  // yet to be implemented
    free(object);
}

void register_method(struct class *class, int methodkey, void *(*function)(struct object *, va_list) ) {
    struct method *new_method = malloc(sizeof *new_method);
    assert(new_method!=NULL);
    new_method->function = function;
    dict_add(class->methods,methodkey,new_method);    
}

void *call (struct object *object, int methodkey, ... ) {
    va_list args;
    va_start(args,methodkey);
    struct method *method = NULL;
    struct class *class = object->class;
    while (1) {
        assert(class!=NULL); //asserts if method wasn't found in any class or superclass
        method = dict_get(class->methods,methodkey);
        if (method != NULL) break;
        class = class->superclass;
    }
    return method->function(object, args);
}

void *attr(struct object *object, int attrkey) {
    return dict_get(object->data,attrkey);
}

void set(struct object *object, int attrkey, void *value) {
    dict_set(object->data,attrkey,value);
}

/*/ TESTING AREA:

enum {TEST = 0
};

void *test1(struct object *object, va_list args) {
    printf("ge1testet");
    return NULL;
}

/
int main () {
    struct class *myclass = create_class(NULL,NULL,NULL);
    register_method(myclass,TEST,test1);
    struct object *myobject = create_from(myclass);
    call(myobject,TEST);
    delete_object(myobject);
    return 0;
}
*/