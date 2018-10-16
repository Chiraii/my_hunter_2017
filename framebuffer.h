/*
** EPITECH PROJECT, 2017
** framebuffer
** File description:
** that's the framebuffer header
*/

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_
#include <SFML/Graphics.h>

struct framebuffer {
	unsigned int width;
	unsigned int height;
	sfUint8 *pixels;
};

typedef struct framebuffer framebuffer_t;

framebuffer_t *framebuffer_create(unsigned int width, unsigned int height);

void framebuffer_destroy(framebuffer_t *framebuffer);

void my_put_pixel(framebuffer_t *framebuffer, unsigned int x, unsigned int y, sfColor color);

void disp_hearts(sfSprite *heart, int lives, sfRenderWindow *window);

#endif
