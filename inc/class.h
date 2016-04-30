#include <stdarg.h>

struct class;
struct object;
struct method;

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


struct class *create_class(struct class *superclass, void (*initialiser)(struct object *), void (*finaliser)(struct object *));

struct object *create_from(struct class *class);

void delete_object(struct object *object);

void register_method(struct class *class, int methodkey, void *(*function)(struct object *, va_list) );

void call (struct object *object, int methodkey, ... );

void *attr(struct object *object, int attrkey);

void set(struct object *object, int attrkey, void *value);