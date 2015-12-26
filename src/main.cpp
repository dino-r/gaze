#include "SDL.hpp"
//#include "SDL2/SDL_image.h"
//#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <tuple>
#include <algorithm>

#include "image.hpp"
#include "input.hpp"

#ifdef __APPLE__
   #define FONT_PATH "/Library/Fonts/Andale Mono.ttf"
#elif defined __linux__
   #define FONT_PATH "/usr/share/fonts/TTF/DejaVuSansMono.ttf"
#endif



Image gImage;
Input uInput;


int round(float x) {
   return floor(x + 0.5f);
}

SDL_Rect center_fit (int im_w, int im_h, int screen_w, int screen_h ) {
   float width_growth  = float (screen_w) / float(im_w);
   float height_growth = float (screen_h) / float(im_h);
   
   int x, y, w, h;
   if (width_growth < height_growth) {
      w = round(width_growth * im_w );
      h = round(width_growth * im_h );
      x = 0;
      y = (screen_h - h)/2;
      
   } else {
      w = round(height_growth * im_w );
      h = round(height_growth * im_h );
      x = (screen_w - w)/2; 
      y =  0;
   }

   return {x, y, w, h};
}

void update_position (SDL_Point rel_motion, SDL_Rect* rect) {
   rect->x += rel_motion.x;
   rect->y += rel_motion.y;
}

constexpr float ZOOM_FACTOR = 1.1f;

SDL_Point rect_coordinates(SDL_Point p, SDL_Rect rect) {
   return {p.x - rect.x, p.y - rect.y};
}

void update_zoom (int wheel, SDL_Point mousePos, SDL_Rect* rect) {
   //TODO: for an OS with an actual scroll wheel (not the hacked linux stuff), 
   //the zoom should scale with the integer that we have in the wheel.
   //But I don't know how strong it should be...

   //zoom the rect
   if( wheel > 0 ) {
      float z = float(wheel) * ZOOM_FACTOR;
      rect->w = round( float(rect->w) * z ); 
      rect->h = round( float(rect->h) * z );
      rect->x += round( (1.f-z) * float(mousePos.x) );
      rect->y += round( (1.f-z) * float(mousePos.y) );
   } else if (wheel < 0) {
      float z = float(-wheel) * ZOOM_FACTOR;
      rect->w = round( float(rect->w) / z ); 
      rect->h = round( float(rect->h) / z );
      rect->x += round( (1.f-1.f/z) * float(mousePos.x) );
      rect->y += round( (1.f-1.f/z) * float(mousePos.y) );
   }

}

std::vector<std::string> argparse(int argc, char* args[]) {
   auto arguments = std::vector<std::string>();
   if (argc > 0) {
      for (int i = 1; i < argc; i++) {
         arguments.push_back( std::string(args[i]) );
      }
   }
   return arguments;
}



int main( int argc, char* args[] ) {
   auto arguments = argparse(argc, args);
   try { 
      SDL::SDL sdl;
      SDL::Window win;
      SDL::Renderer rend ( win );
      SDL::TTF font ( FONT_PATH );
      SDL::Image img;


      gImage.insertPaths(arguments);
      if ( !gImage.loadFromFile(rend.renderer))  {
         printf("Failed to load image...");
      } else {

         SDL_Rect srcrect, dstrect;
         SDL_Event e;
         SDL_Point mouse_image_coords;

         //default src and dst rectangles of images. No clipping and fitting everything on the window
         srcrect = {0,0, gImage.getWidth(), gImage.getHeight()};
         dstrect = center_fit( gImage.getWidth(), gImage.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT );

         while( !uInput.quit() ) {
            while( SDL_PollEvent( &e ) != 0 ) {
               uInput.handleEvent(&e);
               
               if (uInput.next()) {
                  gImage.next();
                  if ( !gImage.loadFromFile(rend.renderer) ) {
                     printf("Failed to load image...");
                  } else {
                     srcrect = {0,0, gImage.getWidth(), gImage.getHeight()};
                     dstrect = center_fit( gImage.getWidth(), gImage.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT );
                  }
               }
               if (uInput.previous()) {
                  gImage.previous();
                  if ( !gImage.loadFromFile(rend.renderer) ) {
                     printf("Failed to load image...");
                  } else {
                     srcrect = {0,0, gImage.getWidth(), gImage.getHeight()};
                     dstrect = center_fit( gImage.getWidth(), gImage.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT );
                  }
               }

               SDL_SetRenderDrawColor( rend.renderer, 0x00, 0x00, 0x00, 0xFF );
               SDL_RenderClear( rend.renderer);

               //click and drag around
               if (uInput.mouseIsDown()) {
                  update_position( uInput.getRelativeMotion(), &dstrect );
               }

            

               mouse_image_coords = rect_coordinates(uInput.getMousePosition(), dstrect);
               update_zoom(uInput.getWheel(), mouse_image_coords, &dstrect);

               gImage.render(rend.renderer, &srcrect, &dstrect);
               SDL_RenderPresent( rend.renderer);
            }
         }
      }
   } catch (std::string str) {
      std::cout << str << "\n";
   }
   return 0;
}

