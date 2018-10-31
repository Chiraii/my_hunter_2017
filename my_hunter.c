/*
** EPITECH PROJECT, 2017
** my_hunter
** File description:
** that's my hunter
*/

#include <SFML/Audio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "framebuffer.h"

void disp_hearts(sfSprite *heart, int lives, sfRenderWindow *window)
{
	sfVector2f pos;

	pos.x = 0;
	pos.y = 650;
	for (int i = 1; i <= lives ; i++) {
		sfRenderWindow_drawSprite(window, heart, NULL);
		sfSprite_setPosition(heart, pos);
		pos.x = pos.x + 160;
	}
}

int main(int argc, char **argv)
{
	sfVector2i vector;
	sfVideoMode mode = {800, 800, 32};
	sfVideoMode title_mode = {800, 800, 32};
	sfRenderWindow *window;
	sfRenderWindow *title;
	sfMouseButtonEvent *mouse_event;
	sfEvent event;
	sfTexture *heart_txtr;
	sfTexture *bg;
	sfTexture *texture_canard;
	sfTexture *flingue_text;
	sfTexture *flingue_recul_text;
	sfTexture *title_pic_text;
	sfSprite *title_pic;
	sfSprite *background;
	sfSprite *sprite;
	sfSprite *heart;
	sfSprite *flingue;
	sfSprite *flingue_recul;
	sfIntRect rect;
	sfClock *clock;
	sfClock *click_clock;
	sfVector2f vector_f;
	sfVector2f back;
	sfVector2f back_pos;
	sfVector2f sprite_pos;
	sfVector2f origin;
	sfVector2f mouse_pos;
	sfTime timer;
	sfTime click;
	sfSoundBuffer *flap_buff;
	sfSoundBuffer *pew_buff;
	sfSoundBuffer *midi_buff;
	sfSoundBuffer *quack_buff;
	sfSoundBuffer *touch_buff;
	sfSoundBuffer *title_song_buff;
	sfSound *touch;
	sfSound *title_song;
	sfSound *flap;
	sfSound *quack;
	sfSound *midi;
	sfSound *pew;
	float seconds;
	float secs;
	int lives = 10;
	int score = 0;
	int x;
	int y;

	if (argc >= 2){
		if (argv[1][0] == '-' && argv[1][1] == 'h') {
			printf("my_hunter is a duck shooting game. It is played with the mouse : the goal of the game is to shoot the ducks that appear on screen.\nSuccessfully shooting a duck adds 1 point to your score.\nIf you shoot, but don't hit a duck, you will loose a life. You have 3 of them, they're symbolized by the little hearts on the bottom left corner of the game screen.\nIf you run out of lives, you loose, so be accurate!\nThe goal is to have the best possible score. Good luck!\n");
		}
		else
			printf("You executed my_hunter wrongly.\nUsage : ./my_hunter\nYou may pass -h as argument on execution to display a help message.\n");
		return (0);
	}
	mouse_pos.x = 150;
	mouse_pos.y = 0;
	origin.x = -110;
	back_pos.x = 0;
	back.x = -910;
	vector_f.x = 3;
	vector_f.y = 0;
	rect.top = 0;
	rect.left = 0;
	rect.width = 110;
	rect.height = 110;
	clock = sfClock_create();
	flap_buff = sfSoundBuffer_createFromFile("flap.wav");
	quack_buff = sfSoundBuffer_createFromFile("quack.wav");
	midi_buff = sfSoundBuffer_createFromFile("bad_midi.wav");
	pew_buff = sfSoundBuffer_createFromFile("Gun+1.wav");
	title_song_buff = sfSoundBuffer_createFromFile("title.wav");
	touch_buff = sfSoundBuffer_createFromFile("touch.wav");
	flap = sfSound_create();
	quack = sfSound_create();
	pew = sfSound_create();
	midi = sfSound_create();
	title_song = sfSound_create();
	touch = sfSound_create();
	sfSound_setBuffer(touch, touch_buff);
	sfSound_setBuffer(title_song, title_song_buff);
	sfSound_setBuffer(flap, flap_buff);
	sfSound_setBuffer(quack, quack_buff);
	sfSound_setBuffer(pew, pew_buff);
	sfSound_setBuffer(midi, midi_buff);
	title = sfRenderWindow_create(title_mode, "My Hunter II - Legacy of the Duck Hunter : Revelations of the Doom Prophet", sfClose, NULL);
	title_pic_text = sfTexture_createFromFile("title_screen.jpg", NULL);
	heart_txtr = sfTexture_createFromFile("gentil_ptit_coeur_plutot_sympa_quand_meme.png", NULL);
	bg = sfTexture_createFromFile("sky_bg.jpg", NULL);
	flingue_text = sfTexture_createFromFile("flingue.png", NULL);
	flingue_recul_text = sfTexture_createFromFile("flingue_recul.png", NULL);
	texture_canard = sfTexture_createFromFile("spritesheet.png", NULL);
	title_pic = sfSprite_create();
	flingue = sfSprite_create();
	flingue_recul = sfSprite_create();
	sprite = sfSprite_create();
	background = sfSprite_create();
	heart = sfSprite_create();
	sfSprite_setTexture(flingue, flingue_text, sfTrue);
	sfSprite_setTexture(sprite, texture_canard, sfTrue);
	sfSprite_setTexture(background, bg, sfTrue);
	sfSprite_setTexture(heart, heart_txtr, sfTrue);
	sfSprite_setTexture(title_pic, title_pic_text, sfTrue);
	sfRenderWindow_setFramerateLimit(title, 60);
	sfSound_setLoop(midi, sfTrue);
	sfSound_setVolume(quack, 50);
	sfSound_setVolume(midi, 50);
	sfSound_play(title_song);
	while (sfRenderWindow_isOpen(title)) {
		sfRenderWindow_clear(title, sfBlack);
		sfRenderWindow_drawSprite(title, title_pic, NULL);
		while (sfRenderWindow_pollEvent(title, &event)) {
			if (event.type == sfEvtMouseButtonPressed) {
				sfSound_stop(title_song);
				sfRenderWindow_close(title);
				sfTexture_destroy(title_pic_text);
				sfSprite_destroy(title_pic);
				sfSoundBuffer_destroy(title_song_buff);
				sfSound_destroy(title_song);
				sfSoundBuffer_destroy(touch_buff);
				sfSound_destroy(touch);
			}
			if (event.type == sfEvtKeyPressed) {
				sfSound_play(touch);
			}
		}
		sfRenderWindow_display(title);
	}
	window = sfRenderWindow_create(mode, "My Hunter II - Legacy of the Duck Hunter : Revelations of the Doom Prophet", sfClose, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);
	sfRenderWindow_setMouseCursorVisible(window, sfFalse);
	sfSound_play(midi);
	while (sfRenderWindow_isOpen(window)) {
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed)
				sfRenderWindow_close(window);
			if (event.type == sfEvtMouseButtonPressed) {
				sfSound_play(pew);
				sfSprite_setTexture(flingue, flingue_recul_text, sfTrue);
				vector = sfMouse_getPositionRenderWindow(window);
				x = vector.x;
				y = vector.y;
				sprite_pos = sfSprite_getPosition(sprite);
				if (vector.x <= sprite_pos.x + 110 && vector.x >= sprite_pos.x && vector.y <= sprite_pos.y + 110 && vector.y >= sprite_pos.y) {
					score++;
					printf("THAT'S A HIT! YOUR SCORE IS : %d\n", score);
					back_pos.x = 0 - sprite_pos.x - 110;
					back_pos.y = rand() % (600 - 110) + 220;
					sfSprite_setPosition(sprite, back_pos);
					vector_f.x++;
				}
				else {
					lives--;
					printf("YOU MISSED! LIVES LEFT : %d\n", lives);
				}
				if (lives == 0) {
					printf("YOU RAN OUT OF LIVES! BETTER LUCK NEXT TIME\n");
					sfSound_stop(midi);
					sfSound_stop(flap);
					sfSound_stop(quack);
					sfSound_stop(pew);
					sfSound_destroy(pew);
					sfSound_destroy(midi);
					sfSound_destroy(quack);
					sfSound_destroy(flap);
					sfSoundBuffer_destroy(flap_buff);
					sfSoundBuffer_destroy(quack_buff);
					sfSoundBuffer_destroy(pew_buff);
					sfSoundBuffer_destroy(midi_buff);
					sfTexture_destroy(texture_canard);
					sfTexture_destroy(bg);
					sfTexture_destroy(flingue_text);
					sfTexture_destroy(flingue_recul_text);
					sfTexture_destroy(heart_txtr);
					sfSprite_destroy(heart);
					sfSprite_destroy(sprite);
					sfSprite_destroy(background);
					sfSprite_destroy(flingue);
					sfSprite_destroy(flingue_recul);
					sfRenderWindow_close(window);
					return (0);
				}
			}
		}
		vector = sfMouse_getPositionRenderWindow(window);
		sfRenderWindow_clear(window, sfBlack);
		timer = sfClock_getElapsedTime(clock);
		seconds = timer.microseconds / 1000000.0;
		if (seconds > 0.15) {
			rect.left = rect.left + 110;
			if (rect.left == 110)
				sfSound_play(quack);
			if (rect.left == 220)
				sfSound_play(flap);
			if (rect.left >= 330)
				rect.left = 0;
			sfClock_restart(clock);
		}
		mouse_pos.x = vector.x - 43;
		mouse_pos.y = vector.y - 13;
		sfSprite_setPosition(flingue, mouse_pos);
		sfRenderWindow_drawSprite(window, background, NULL);
		disp_hearts(heart, lives, window);
		sfSprite_setTextureRect(sprite, rect);
		sfRenderWindow_drawSprite(window, sprite, NULL);
		sfRenderWindow_drawSprite(window, flingue, NULL);
		sprite_pos = sfSprite_getPosition(sprite);
		origin.y = rand() % (600 - 110) + 220;
		if (origin.y <= 110)
			origin.y = 110;
		if (sprite_pos.x >= 800)
			sfSprite_setPosition(sprite, origin);
		else
			sfSprite_move(sprite, vector_f);
		sfRenderWindow_display(window);
		sfSprite_setTexture(flingue, flingue_text, sfTrue);
		back_pos.y = 0;
		back.y = 0;
		srand(time(NULL));
	}
	if (!window)
		return (84);
	sfSound_stop(midi);
	sfSound_stop(flap);
	sfSound_stop(quack);
	sfSound_stop(pew);
	sfSound_destroy(pew);
	sfSound_destroy(midi);
	sfSound_destroy(quack);
	sfSound_destroy(flap);
	sfSoundBuffer_destroy(flap_buff);
	sfSoundBuffer_destroy(quack_buff);
	sfSoundBuffer_destroy(pew_buff);
	sfSoundBuffer_destroy(midi_buff);
	sfTexture_destroy(texture_canard);
	sfTexture_destroy(bg);
	sfTexture_destroy(flingue_text);
	sfTexture_destroy(flingue_recul_text);
	sfTexture_destroy(heart_txtr);
	sfSprite_destroy(heart);
	sfSprite_destroy(sprite);
	sfSprite_destroy(background);
	sfSprite_destroy(flingue);
	sfSprite_destroy(flingue_recul);
	sfRenderWindow_destroy(window);
	return (0);
}
