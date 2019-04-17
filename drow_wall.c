/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:52:17 by vmcclure          #+#    #+#             */
/*   Updated: 2019/04/15 14:53:53 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "wolf.h"

void drow_wall(SDL_Renderer *renderer, t_wall wall, t_tga image)
{
	int dx1;
	int dy1;
	int dx4;
	int dy4;
	int dist1;
	int dist4;
	float dir1;
	float dir4;
	float k;
	char r;
	char g;
	char b;
	int i;
	int x;
	int y;
	float m;
	char a;
	float *stena1_x;
	float *stena1_y;
	float *stena2_x;
	float *stena2_y;

	float *dist_sten;
	float *ugol_sten;
	float shag_dlya_2_steni;
	float shag_dlya_1_steni;
	int maxdist;
	int x0;
	int y0;
	int x2;
	int y2;
	int x1;
	int y1;
	int xp;
	int yp;
	int mindist;
	int buf;

	t_texture text;
	SDL_SetRenderDrawColor(renderer, 250 , 150, 200, 255);
	SDL_RenderDrawPoint (renderer, wall.x1, wall.y1); // 50 : 50
	SDL_RenderDrawPoint (renderer, wall.x2, wall.y2); // 150 : 40
	SDL_RenderDrawPoint (renderer, wall.x3, wall.y3); // 50 : 100
	SDL_RenderDrawPoint (renderer, wall.x4, wall.y4); // 120 : 120
	if (wall.x3 > wall.x4)
	{
		buf = wall.x3;
		wall.x3 = wall.x4;
		wall.x4 = buf;
	}
	if (wall.x1 > wall.x2)
	{
		buf = wall.x1;
		wall.x1 = wall.x2;
		wall.x2 = buf;
	}
	dx1 = wall.x1 - wall.x2;
	dy1 = wall.y1 - wall.y2;
	dx4 = wall.x3 - wall.x4;
	dy4 = wall.y3 - wall.y4;
	text = readbmp("10.bmp");
	dist1 = pow(pow(wall.x1 - wall.x2, 2) + pow(wall.y1- wall.y2, 2), 0.5);
	dist4 = pow(pow(wall.x3 - wall.x4, 2) + pow(wall.y3- wall.y4, 2), 0.5);
	if (dist4 > dist1)
	{
		maxdist = dist4;
		mindist = dist1;
		shag_dlya_1_steni = 1;
		shag_dlya_2_steni = (float)mindist / (float)maxdist;
	}
	else
	{
		maxdist = dist1;
		mindist = dist4;
		shag_dlya_1_steni = (float)mindist / (float)maxdist;
		shag_dlya_2_steni = 1;
	}
	
	dir1 = (atan((float)dy1/(float)dx1));
	dir4 = (atan((float)dy4/(float)dx4));
	stena1_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena1_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_x = (float *)malloc((sizeof(float)) * (maxdist+1));
	stena2_y = (float *)malloc((sizeof(float)) * (maxdist+1));
	ugol_sten = (float *)malloc((sizeof(float)) * (maxdist+1));
	dist_sten = (float *)malloc((sizeof(float)) * (maxdist+1));
	i = 0;
	while (i < maxdist)
	{
		stena1_x[i] = wall.x3 + (i * shag_dlya_1_steni) * cos(dir4);
		stena1_y[i] = wall.y3 + (i * shag_dlya_1_steni) * sin(dir4);
		stena2_x[i] = wall.x1 + (i * shag_dlya_2_steni) * cos(dir1);
		stena2_y[i] = wall.y1 + (i * shag_dlya_2_steni) * sin(dir1);
		ugol_sten[i] = atan((float)(stena1_y[i] - stena2_y[i])/(stena1_x[i] - stena2_x[i]));

		//dist_sten[i] = sqrt(((int)(stena2_x[i] - stena1_x[i]) * (int)(stena2_x[i] - stena1_x[i])) + ((int)(stena2_y[i] - stena1_y[i]) * (int)(stena2_y[i] - stena1_y[i])));
		dist_sten[i] = sqrt(pow(stena2_x[i] - stena1_x[i], 2) + pow(stena2_y[i] - stena1_y[i], 2));
		 printf ("%f\n", dist_sten[i]);
		if (ugol_sten[i] > 0)
			ugol_sten[i] -= M_PI;
		i++;	
	}

	x = 0;
	while (x < maxdist)
	{
		y = 0;
		while (y < dist_sten[x] )
		{
			k = dist_sten[x]   / image.height;
			m = maxdist / image.width;
			x0 = (stena1_x[x]) + y *1  * cos(ugol_sten[x]);
			y0 = (stena1_y[x]) + y*1 * sin(ugol_sten[x]);
			yp = (int)(y/k);//* text.width * (image.bpp/8);
			xp = (int)(x/m);// * (image.bpp/8);
			r = image.pic[yp][xp].red;
			g = image.pic[yp][xp].green;
			b = image.pic[yp][xp].blue;
			a = image.pic[yp][xp].alpha;
			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
			SDL_RenderDrawPoint (renderer,x0, y0);
			y++;
		}
		x++;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	free(stena1_x);
	free(stena1_y);
	free(stena2_x);
	free(stena2_y);
	free(ugol_sten);
	free(dist_sten);
	free(text.pixels);
}
