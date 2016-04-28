struct entity {
    char symbol;
    int x;
    int y;
    void (*update)(struct entity *);
};

struct entity *create_entity();
void delete_entity(struct entity *entity);
void update(struct entity *entity);
void move(struct entity *entity, int direction);
