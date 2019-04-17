#ifndef WOLF_H
# define WOLF_H
#include "include/SDL2/SDL.h"
#include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct      s_bmpheader
{
    unsigned char	b1,b2;			//Символы BM (смение 0, длина 2)
	unsigned short	bfSize;			//Размер файла в байтах	(Смещение 2, длина 2)
	unsigned short	bfReserved1;	        //Бесполезно (Смещение 6, длина 2)
	unsigned short	bfReserved2;	        //Бесполезно (Смещение 8, длина 2)
	unsigned short  padding;		//Мусор, для выравнивания
	unsigned short	bfoffbits;		//Смещение до самого изображения (Смещение 10, длина 2)
    char            a[42];
}           t_bmphead;

typedef struct s_texture
{
	int	fail;
	int	width;
    int height;
	unsigned char *pixels;
	int bpp;
	t_bmphead hdbmp;
}               t_texture;

typedef struct s_wall
{
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	int x4;
	int y4;
}               t_wall;

typedef struct		s_tga
{
	unsigned char	id_length;
	unsigned char	color_map;
	unsigned char	data_type;
	unsigned char	xy_origin[2];
	short int		width;
	short int		height;
	unsigned char	bpp;
	unsigned char	flip_g;
	unsigned char	flip_v;
}					t_tga;

t_texture readbmp(char* filename);
#endif