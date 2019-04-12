if (k <= 1000)
			{
				ypos = 0;
				// while (ypos < range1[i]/10)
				{	
					yp = text.width*3 * k;
					xp = i * 3;
					r = text.pixels[xp + yp + 2 ];
					g = text.pixels[xp + yp + 1 ];
				 	b = text.pixels[xp + yp + 0] ;
					SDL_SetRenderDrawColor(renderer, r, g, b, 255);
					SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
					x = setkax4[i] + range1[i] * k * cos(ugol1[i]);
					y = setkay4[i] + range1[i] * k * sin(ugol1[i]);
					// SDL_RenderDrawPoint (renderer,x, y);
					ypos++;
				}
			}