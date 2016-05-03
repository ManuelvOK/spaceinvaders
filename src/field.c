#include <stdlib.h>

#include "../inc/entity.h"
#include "../inc/field.h"

struct field fldCreate(unsigned width, unsigned height)
{
    struct field fld;

    fld.width = width;
    fld.height = height;
    fld.data = (struct entity*)calloc(width * height, sizeof(struct entity));

    return fld;
}

void fldFree(struct field fld)
{
    free(fld.data);
}
