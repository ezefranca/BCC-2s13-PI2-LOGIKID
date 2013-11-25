/*
 * Código main
 * Inicio: 11/08/2013
 * Autor: Alexandre Savelli Bencz
 */

#include "comum.h"
#include "../src/Menus/StartMenu.h"

void QuitGame()
{
	al_destroy_event_queue(game.fila_eventos);
	al_destroy_display(game.janela);
	al_destroy_font(game.fonte);
}

void fadeout(int velocidade)
{
    ALLEGRO_BITMAP *buffer = NULL;
    buffer = al_create_bitmap(800, 600);
    al_set_target_bitmap(buffer);
    al_draw_bitmap(al_get_backbuffer(game.janela), 0, 0, 0);
    al_set_target_bitmap(al_get_backbuffer(game.janela));

    if (velocidade <= 0)
    {
        velocidade = 1;
    }
    else if (velocidade > 15)
    {
        velocidade = 15;
    }

    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {
        al_clear_to_color(al_map_rgba(0, 0, 0, 0));
        al_draw_tinted_bitmap(buffer, al_map_rgba(255 - alfa, 255 - alfa, 255 - alfa, alfa), 0, 0, 0);
        al_flip_display();
        al_rest(0.005); // Não é necessário caso haja controle de FPS
    }

    al_destroy_bitmap(buffer);
}

void fadein(ALLEGRO_BITMAP *imagem, int velocidade)
{
    if (velocidade < 0)
    {
        velocidade = 1;
    }
    else if (velocidade > 15)
    {
        velocidade = 15;
    }

    int alfa;
    for (alfa = 0; alfa <= 255; alfa += velocidade)
    {
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_tinted_bitmap(imagem, al_map_rgba(alfa, alfa, alfa, alfa), 80, 100, 0);
        al_flip_display();
        al_rest(0.005); // Não é necessário caso haja controle de FPS
    }
}

void InitScreens()
{

    game.song = al_load_sample("./data/sound/music/Logikid.ogg");
    game.songInstance = al_create_sample_instance(game.song);
    al_set_sample_instance_playmode(game.songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(game.songInstance, al_get_default_mixer());
    al_play_sample_instance(game.songInstance);

	ALLEGRO_BITMAP *temp = al_load_bitmap("data/images/intro/senac.png");
	fadein(temp, 7);
	al_rest(2.0);
    fadeout(8);

    temp = al_load_bitmap("data/images/intro/pi.png");
	fadein(temp, 7);
	al_rest(2.0);
    fadeout(8);

    temp = al_load_bitmap("data/images/intro/allegro.png");
    fadein(temp, 7);
    al_rest(2.0);
    fadeout(8);

    temp = al_load_bitmap("data/images/intro/github.png");
    fadein(temp, 7);
    al_rest(2.0);
    fadeout(8);
}

int main(void)
{

	//inputLogic("logic/exemplo.txt");

	if (!inicializar())
		return -1;
	//Animação inicial
	InitScreens();
	StartMenu();
	//GameLoop();

	QuitGame();
	return 0;
}