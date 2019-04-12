/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmcclure <vmcclure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:51:32 by vmcclure          #+#    #+#             */
/*   Updated: 2019/04/12 21:47:40 by vmcclure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>
void drow_wall(SDL_Renderer *renderer, t_wall wall)
{
	int dx1;
	int dx2;
	int dy1;
	int dy2;
	int dx3;
	int dy3;
	int dx4;
	int dy4;
	int dist1;
	int dist2;
	int dist3;
	int dist4;
	float dir1;
	float dir2;
	float dir3;
	float dir4;
	int k;
	char r;
	char g;
	char b;
	int i;
	int x;
	int y;
	float shag1;
	float shag2;
	float shag3;
	float shag4;
	float ugol1[64];
	float ugol2[64];
	float ugol3[64];
	float ugol4[64];
	float setkax1[64];
	float setkax2[64];
	float setkax3[64];
	float setkax4[64];
	float setkay1[64];
	float setkay2[64];
	float setkay3[64];
	float setkay4[64];
	int range1[64];
	int range2[64];
	int range3[64];
	int range4[64];
	t_texture text;
	dx1 = wall.x1 - wall.x2;
	dy1 = wall.y1 - wall.y2;
	dx2 = wall.x2 - wall.x4;
	dy2 = wall.y2 - wall.y4;
	dx3 = wall.x1 - wall.x3;
	dy3 = wall.y1 - wall.y3;
	dx4 = wall.x3 - wall.x4;
	dy4 = wall.y3 - wall.y4;
	text = readbmp("10.bmp");
	dist1 = pow(pow(wall.x1 - wall.x2, 2) + pow(wall.y1- wall.y2, 2), 0.5);
	dist2 = pow(pow(wall.x2 - wall.x4, 2) + pow(wall.y2- wall.y4, 2), 0.5);
	dist3 = pow(pow(wall.x1 - wall.x3, 2) + pow(wall.y1- wall.y3, 2), 0.5);
	dist4 = pow(pow(wall.x3 - wall.x4, 2) + pow(wall.y3- wall.y4, 2), 0.5);
	shag1 = (float)dist1/64;
	shag2 = (float)dist2/64;
	shag3 = (float)dist3/64;
	shag4 = (float)dist4/64;
	dir1 = (atan((float)dy1/(float)dx1));
	dir2 = (atan((float)dy2/(float)dx2));
	dir3 = (atan((float)dy3/(float)dx3));
	dir4 = (atan((float)dy4/(float)dx4));
	// printf ("dir2 %f\n", dir2);
	// printf ("d1 %d\n", dist1);
	// printf ("d2 %d\n", dist2);
	// printf ("d3 %d\n", dist3);
	// printf ("d4 %d\n", dist4);
	// printf ("%d", text.bpp);
	
	i = 0;
	while (i <= dist1)
	{
		x = wall.x1 + i * cos(dir1);
		y =  wall.y1 + i * sin(dir1);
		//SDL_RenderDrawPoint (renderer,x, y);
		i++;
	}
	i = 0;
	
	i = 0;
	while (i <= dist2)
	{
		x = wall.x2 - i * cos(dir2);
		y =  wall.y2 - i * sin(dir2);
		//SDL_RenderDrawPoint (renderer,x, y);
		i++;
	}
	i = 0;
	while (i <= dist3)
	{
		x = wall.x1 - i * cos(dir3);
		y =  wall.y1 - i * sin(dir3);
	//	SDL_RenderDrawPoint (renderer,x, y);
		i++;
	}
	i = 0;
	while (i <= dist4)
	{
		x = wall.x4 - i * cos(dir4);
		y =  wall.y4 - i * sin(dir4);
		//SDL_RenderDrawPoint (renderer,x, y);
		i++;
	}
	i = 0;
	SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
	while (i <= 64)
	{
		setkax1[i] =  wall.x1 + (shag1 * i) * cos(dir1);
		setkay1[i] =  wall.y1 + (shag1 * i) * sin(dir1);
		setkax2[i] =  wall.x4 + (shag2 * i) * cos(dir2);
		setkay2[i] =  wall.y4 + (shag2 * i) * sin(dir2);
		setkax3[i] =  wall.x3 + (shag3 * i) * cos(dir3);
		setkay3[i] =  wall.y3 + (shag3 * i) * sin(dir3);
		setkax4[i] =  wall.x3 + (shag4 * i) * cos(dir4);
		setkay4[i] =  wall.y3 + (shag4 * i) * sin(dir4);
		range1[i] = pow(pow(setkax1[i] - setkax4[i], 2) + pow(setkay1[i]- setkay4[i], 2), 0.5);
		range2[i] = pow(pow(setkax2[i] - setkax3[i], 2) + pow(setkay2[i]- setkay3[i], 2), 0.5);
		range3[i] = pow(pow(setkax1[i] - setkax3[i], 2) + pow(setkay1[i]- setkay3[i], 2), 0.5);
		range4[i] = pow(pow(setkax3[i] - setkax4[i], 2) + pow(setkay3[i]- setkay4[i], 2), 0.5);		
		SDL_RenderDrawPoint (renderer,setkax1[i], setkay1[i]);
		SDL_RenderDrawPoint (renderer,setkax2[i], setkay2[i]);
		SDL_RenderDrawPoint (renderer,setkax3[i], setkay3[i]);
		SDL_RenderDrawPoint (renderer,setkax4[i], setkay4[i]);
		i++;
	}
	i = 0;
	int ypos;
	int yp;
	int xpos;
	int xp;
	while (i < 64)
	{
		ugol1[i] = (atan((float)(setkay1[i] - setkay4[i])/(setkax1[i] - setkax4[i])));
		ugol2[i] = (atan((float)(setkay2[i] - setkay3[i])/(setkax2[i] - setkax3[i])));
		ugol3[i] = (atan((float)(setkay1[i] - setkay3[i])/(setkax1[i] - setkax3[i])));
		ugol4[i] = (atan((float)(setkay3[i] - setkay4[i])/(setkax3[i] - setkax4[i])));
		k = 0;
		while (k < 64)
		{
			// x = setkax4[i] + k * range1[i]/64* cos(ugol1[i]);
			// y = setkay4[i] + k * range1[i]/64*sin(ugol1[i]);
			ypos =0;
			while (ypos < range1[i]/64)
			{
				x = setkax4[i] + (ypos +k * range1[i]/64) * cos(ugol1[i]);
				y = setkay4[i] + (ypos +k * range1[i]/64)* sin(ugol1[i]);

				yp = text.width * 3 * k;
				xp = i * 3;
				r = text.pixels[xp + yp + 2 ];
				g = text.pixels[xp + yp + 1 ];
				b = text.pixels[xp + yp + 0] ;
				SDL_SetRenderDrawColor(renderer, r, g, b, 255);
				//  SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
				SDL_RenderDrawPoint (renderer,x, y);
				ypos++;
			}
				// yp = text.width * 3 * k;				
				// xp = i * 3;
				// r = text.pixels[xp + yp + 2 ];
				// g = text.pixels[xp + yp + 1 ];
				// b = text.pixels[xp + yp + 0] ;
				// SDL_SetRenderDrawColor(renderer, r, g, b, 255);
				// SDL_RenderDrawPoint (renderer,i, k);
						
			k++;
		}
		
		k = 0;
		// while (k < 64)
		// {
		// 	ypos = 0;
		// 	while (ypos < range2[i]/32)
		// 	{
		// 		yp = text.width * 3 * i;
		// 		xp = k * 3;
		// 		r = text.pixels[xp + yp + 2 ];
		// 		g = text.pixels[xp + yp + 1 ];
		// 		b = text.pixels[xp + yp + 0] ;
		// 		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		// 		x = setkax3[i] + ((k) * range2[i]/64 +ypos) * cos(ugol2[i]);
		// 		y =  setkay3[i] + ((k)* range2[i]/64 +ypos) * sin(ugol2[i]);
		// 		SDL_RenderDrawPoint (renderer,x, y);
		// 		ypos++;
		// 	}
		// 	k++;
		// }
		i++;
	}
	SDL_SetRenderDrawColor(renderer, 250 , 0, 200, 255);
	SDL_RenderDrawPoint (renderer, wall.x1, wall.y1); // 50 : 50
	SDL_RenderDrawPoint (renderer, wall.x2, wall.y2); // 150 : 40
	SDL_RenderDrawPoint (renderer, wall.x3, wall.y3); // 50 : 100
	SDL_RenderDrawPoint (renderer, wall.x4, wall.y4); // 120 : 120
	y = 0;
	// while (y < 64)
	// {
	// 	x = 0;
	// 	while (x < 64)
	// 	{
	// 		r = text.pixels[x*3 + (text.width * 3 * y) + 2 ];
	// 		g = text.pixels[x*3 + (text.width * 3 * y) + 1 ];
	// 		b = text.pixels[x*3 + (text.width * 3 * y) + 0] ;
	// 		x++;
	// 		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	// 		SDL_RenderDrawPoint (renderer,x, y+50);
	// 	}
	// 	y++;
	// }
}


int main()
{
    SDL_Window *win;
    SDL_Renderer *renderer;
	SDL_Event event;
	t_wall wall;

	wall.x1 = 50;
	wall.y1 = 50;
	wall.x2 = 300;
	wall.y2 = 30;
	wall.x3 = 40;
	wall.y3 = 300;
	wall.x4 = 299;
	wall.y4 = 120;

    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Hello World", 50, 50, 500, 500, 0);
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
			if (event.type == SDL_KEYDOWN)		
				break;
		}
	}		
    SDL_DestroyWindow(win);

    SDL_Quit();
    return(0);
}