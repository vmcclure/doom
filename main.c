/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:51:32 by vmcclure          #+#    #+#             */
/*   Updated: 2019/04/15 23:10:54 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>
#include <time.h>

void brez(float x0, float x1, float y0, float y1, SDL_Renderer *renderer, t_texture text, float m,  int x2, float start)
{
	float dx;
	float dy;
	float x;
	float y;
	float d;
	float d1;
	float d2;
	int r;
	int g;
	int b;
	int yp;
	float k;
	int xp;
	int e;
	// x2 = x2 + start;
	// printf ("%d\n",x2);
	// printf ("%f\n",start);
	if (x0 < 0 )
			return;
	e = 1;
	float dist_sten;
	dx = (x0 - x1);
	if (dx < 0)
		e = -1;
	dy = y1 - y0;
	d = 2* (dx - dy);
	d1 = 2*dx * e;
	d2 = (dx - dy) *2;
	x = x0;
	y = y0;
	dist_sten = sqrt(pow(dx,2) + pow(dy,2));

	xp = (int)((x2)/m) * 3;//(text.bpp/8);
	k = dist_sten   / (text.width);
	while (y < y1)
	{
		// if (x < 0 )
		// 	return;
		y += 1;
		if (d < 0)
			d +=d1;
		else 
		{
			x += e;
			d +=d2;
		}
		
		yp = (int)((y - y0)/k) * text.width * 3;//(text.bpp/8);
		
		r = text.pixels[yp+xp + 2];
		g = text.pixels[yp+xp + 1];
		b = text.pixels[yp+xp + 0];
		
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderDrawPoint (renderer,x, y);

	}
	
}
void drow_wall(SDL_Renderer *renderer, t_wall wall)
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
	float yy;
	float xx;
	float longx1;
	float longx2;
	

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
	clock_t start = clock();
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
	// ugol_sten = (float *)malloc((sizeof(float)) * (maxdist+1));
	// dist_sten = (float *)malloc((sizeof(float)) * (maxdist+1));
	i = 0;
	while (i <= maxdist)
	{
		
			stena1_x[i] = wall.x1 + (i * shag_dlya_2_steni) * cos(dir1);
			stena1_y[i] = wall.y1 + (i * shag_dlya_2_steni) * sin(dir1);
			stena2_x[i] = wall.x3 + (i * shag_dlya_1_steni) * cos(dir4);
			stena2_y[i] = wall.y3 + (i * shag_dlya_1_steni) * sin(dir4);
		
		// ugol_sten[i] = atan((float)(stena1_y[i] - stena2_y[i])/(stena1_x[i] - stena2_x[i]));

		// dist_sten[i] = sqrt(((int)(stena2_x[i] - stena1_x[i]) * (int)(stena2_x[i] - stena1_x[i])) + ((int)(stena2_y[i] - stena1_y[i]) * (int)(stena2_y[i] - stena1_y[i])));
		// dist_sten[i] = sqrt(pow(stena2_x[i] - stena1_x[i], 2) + pow(stena2_y[i] - stena1_y[i], 2));
		 
		// if (ugol_sten[i] > 0)
		// 	ugol_sten[i] -= M_PI;
		i++;	
	}

	
	x = 0;
	m = maxdist /(float)text.height ;
	// printf ("%f\n",stena1_x[0]);
	while (x < maxdist)
	{
		
		// if (stena1_x[x] >= 0 && stena2_x[x] >=0 )
		{
			brez (stena1_x[x], stena2_x[x], stena1_y[x], stena2_y[x], renderer,text, m,  x, stena1_x[0]);
		}
		// y = 0;
		// xx =0.5  * cos(ugol_sten[x]);
		// yy = 0.5 * sin(ugol_sten[x]);
		
		// while (y < dist_sten[x] *2 )
		// {
		// 	k = dist_sten[x]   / (text.width/2);
		// 	x0 = (stena1_x[x]) + y * xx;
		// 	y0 = (stena1_y[x]) + y * yy;
		// 	yp = (int)(y/k) * text.width * 3;//(text.bpp/8);
		// 	xp = (int)(x/m) * 3;//(text.bpp/8);
		// 	r = text.pixels[yp + xp + 2];
		// 	g = text.pixels[yp + xp + 1];
		// 	b = text.pixels[yp + xp + 0];
		// 	//a = image.pic[yp][xp].alpha;
		// 	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		// 	SDL_RenderDrawPoint (renderer,x0, y0);
		// 	y++;
		// }
		x++;
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time: %f seconds\n", seconds);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	free(stena1_x);
	free(stena1_y);
	free(stena2_x);
	free(stena2_y);
	// free(dist_sten);
	free(text.pixels);
}


int main()
{
    SDL_Window *win;
    SDL_Renderer *renderer;
	SDL_Event event;
	t_wall wall;

	wall.x1 = -500000;
	wall.y1 = 50;
	wall.x2 = 600;
	wall.y2 = 50;
	wall.x3 = -500000;
	wall.y3 = 600;
	wall.x4 = 600;
	wall.y4 = 600;

    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Hello World", 50, 50, 800, 800, 0);
    renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED);
	 SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255);
    //SDL_RenderDrawPoint(renderer, 10, 10);
	drow_wall(renderer, wall);
    SDL_RenderPresent(renderer);
    while (1)
	{
		if (SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				break;
			// if (event.type == SDL_KEYDOWN)		
			// 	break;
			if(event.key.keysym.sym == SDLK_RIGHT)
		{
			wall.x1 += 3;
			SDL_RenderClear(renderer);
			drow_wall(renderer, wall);
			SDL_RenderPresent(renderer);
		}
		if(event.key.keysym.sym == SDLK_LEFT)
		{
			wall.x1 -= 3;
			SDL_RenderClear(renderer);
			drow_wall(renderer, wall);
			SDL_RenderPresent(renderer);
		}
		if(event.key.keysym.sym == SDLK_UP)
		{
			wall.y4  += 3;
			SDL_RenderClear(renderer);
			drow_wall(renderer, wall);
			SDL_RenderPresent(renderer);
		}
		if(event.key.keysym.sym == SDLK_DOWN)
		{
			wall.y4 -=3;
			SDL_RenderClear(renderer);
			drow_wall(renderer, wall);
			
			SDL_RenderPresent(renderer);
		}
		}
	}		
    SDL_DestroyWindow(win);

    SDL_Quit();
    return(0);
}