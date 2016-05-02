#ifndef SPACE_H
#define SPACE_H

struct space
{
    void **array;
    int width;
    int height;
};

struct space *newSpace(int width, int height);
void setSpaceElement(struct space *space, int x, int y, void *content);
void *getSpaceElement(struct space *space, int x, int y);
void printSpace(struct space *space);
void setupSpace();
struct space *getSpace();

#endif
