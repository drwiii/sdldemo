/*
   sdldemo.c [drw 22-Aug-2019]

   SDL graphics tutorial version 1: load an image, show it, move it.
   Copyright (C) 2019, Douglas Winslow <winslowdoug@gmail.com>
*/

#include "SDL/SDL.h"		// include the C headers for the SDL graphics library
#include "SDL/SDL_image.h"	// include the C headers for the SDL_image extension (allows loading various image formats)

void main()	// main() is the function C jumps to when you run the program. void means we do not return an exit status code to the shell.
{
	SDL_Surface *vscreen, *image;	// SDL surfaces are like virtual screens in memory. we use them to prepare things to put into the window.
	SDL_Rect src, dest;		// SDL rectangles consist of coordinates (X,Y) and dimensions (Width,Height).

	SDL_Init(SDL_INIT_VIDEO);	// tell SDL to initialize only the video subsystem.
	vscreen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);	// initialize the window to show the virtual screen surface at 640x480, 32bpp
	SDL_FillRect(vscreen, NULL, SDL_MapRGB(vscreen->format, 16, 32, 64));	// fill vscreen with a background of: Red 16, Green 32, Blue 64

	image = IMG_Load("logo.gif");		// load the GIF image into the image surface (this uses the SDL_image extension)

	// we loaded the GIF, so we will now try to center it on our vscreen
	// let's set up coordinates (x, y) and dimensions (w, h). we do this with our SDL_Rect rectangles:

	// here we do this for the source rectangle; where in the source image are we reading, and how large?
	src.x = 0;		// set source coordinate X (left-to-right, we set this to leftmost pixel)
	src.y = 0;		// set source coordinate Y (top-to-bottom, we set this to topmost pixel)
	src.w = image->w;	// set how many pixels wide (we set this to the width property of the loaded image)
	src.h = image->h;	// set how many pixels tall (we set this to the height property of the loaded image)
	// so we've set the source rectangle to cover the entire pixel area of the loaded image

	// here we do this for the destination rectangle; where on vscreen are we putting this, and how large?
	dest.x = (vscreen->w / 2) - (src.w / 2);	// set destination coordinate X, in middle of vscreen, minus half the width of source
	dest.y = (vscreen->h / 2) - (src.h / 2);	// set destination coordinate Y, in middle of vscreen, minus half the height of source
	dest.w = src.w;					// set how many pixels wide (we reference the src.width we set above)
	dest.h = src.h;					// set how many pixels tall (we reference the src.height we set above)
	// so we've set the destination rectangle to cover the entire pixel area of the loaded image, but we've placed it in the center of vscreen

	SDL_BlitSurface(image, &src, vscreen, &dest);	// blit the image, with the src coordinates, onto vscreen, at the dest coordinates
	SDL_Flip(vscreen);	// flip the vscreen onto the actual running window *
	SDL_Delay(2 * 1000);	// wait two seconds

	int a;	// allocate an integer, we're going to make the image do something

	for (a = dest.x; a <= vscreen->w; a++)	// from current dest.x to furthest right pixel of vscreen width
	{
		SDL_FillRect(vscreen, NULL, SDL_MapRGB(vscreen->format, 32, 64, 128));	// fill the vscreen, the NULL says to use the entirety

		dest.x = a;		// we only update destination coordinate X with what the loop is setting the integer to

		SDL_BlitSurface(image, &src, vscreen, &dest);	// again put the image with the updated coordinate onto the vscreen
		SDL_Flip(vscreen);	// flip the vscreen onto the window *
		SDL_Delay(10);		// not so fast
	}

	SDL_FreeSurface(image);	// unload the image to reclaim memory
	SDL_Delay(1000);	// wait one second

	SDL_Quit();		// tell SDL to unload the program
}

