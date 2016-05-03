#ifndef SPACEINVADERS_FIELD_H
#define SPACEINVADERS_FIELD_H

struct field
{
    struct entity *data;
    unsigned width;
    unsigned height;
};

struct field fldCreate(unsigned width, unsigned height);
void fldFree(struct field fld);

#endif //SPACEINVADERS_FIELD_H
