#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/entity.h"
#include "../inc/board.h"

#define INDEX(x, y, width) ((y) * (width) + (x))

struct board brdCreate(unsigned width, unsigned height)
{
    struct board brd;

    brd.width = width;
    brd.height = height;
    brd.xoffset = 0;
    brd.yoffset = 0;
    brd.monster_state = 0;
    brd.data = (struct entity*)calloc(width * height, sizeof(struct entity));

    return brd;
}

void brdFree(struct board *this)
{
    free(this->data);
}



struct entity brdGet(struct board *this, unsigned x, unsigned y)
{
    if (x >= this->width)  return entCreateEmpty();
    if (y >= this->height) return entCreateEmpty();

    return this->data[INDEX(x, y, this->width)];
}

struct entity *brdGetRow(struct board *this, unsigned y)
{
    if (y >= this->height) return NULL;

    return this->data + INDEX(0, y, this->width);
}

void brdSet(struct board *this, struct entity value, unsigned x, unsigned y)
{
    if (x >= this->width)  return;
    if (y >= this->height) return;

    this->data[INDEX(x, y, this->width)] = value;
}

size_t brdRead(struct board *brd, FILE *file)
{
    uint16_t width, height, xoffset, yoffset;
    uint8_t monster_state;
    size_t total = 0;
    size_t read;

    read = fread(&width, sizeof(width), 1, file);
    if (read != 1) return 0;
    total += read;

    read = fread(&height, sizeof(height), 1, file);
    if (read != 1) return 0;
    total += read;

    read = fread(&xoffset, sizeof(xoffset), 1, file);
    if (read != 1) return 0;
    total += read;

    read = fread(&yoffset, sizeof(yoffset), 1, file);
    if (read != 1) return 0;
    total += read;

    read = fread(&monster_state, sizeof(monster_state), 1, file);
    if (read != 1) return 0;
    total += read;

    *brd = brdCreate(width, height);
    brd->xoffset = xoffset;
    brd->yoffset = yoffset;
    brd->monster_state = monster_state;

    read = fread(brd->data, sizeof(brd->data[0]), width * height, file);
    if (read != width * height)
    {
        brdFree(brd);
        return 0;
    }
    total += read;

    return total;
}

size_t brdWrite(struct board *this, FILE *file)
{
    uint16_t width = (uint16_t)this->width;
    uint16_t height = (uint16_t)this->height;
    uint16_t xoffset = (uint16_t)this->xoffset;
    uint16_t yoffset = (uint16_t)this->yoffset;
    uint8_t monster_state = (uint8_t)this->monster_state;
    size_t total = 0;
    size_t written;

    written = fwrite(&width, sizeof(width), 1, file);
    if (written != 1) return 0;
    total += written;

    written = fwrite(&height, sizeof(height), 1, file);
    if (written != 1) return 0;
    total += written;

    written = fwrite(&xoffset, sizeof(xoffset), 1, file);
    if (written != 1) return 0;
    total += written;

    written = fwrite(&yoffset, sizeof(yoffset), 1, file);
    if (written != 1) return 0;
    total += written;

    written = fwrite(&monster_state, sizeof(monster_state), 1, file);
    if (written != 1) return 0;
    total += written;

    written = fwrite(this->data, sizeof(this->data[0]), width * height, file);
    if (written != width * height) return 0;
    total += written;

    return total;
}