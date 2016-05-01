struct list {
    struct list_element *first;
    struct list_element *bookmark; // used for iterating, will automatically be changed if targeted element is removed from list
};

struct list_element {
    void *value;
    struct list_element *next;
};

void list_add(struct list *list, void *value);

void list_remove(struct list *list, void *value);