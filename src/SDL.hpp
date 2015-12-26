/* C++ classes that wrap the C SDL2 library functions */

#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;

namespace SDL {

   class SDL {
      public:
         SDL() {
            if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
               throw std::string("SDL_Init failed");
            }
         }

         ~SDL() noexcept {
            SDL_Quit();
         }
      
   };

   class Window {
      public:
         Window () {
            window = SDL_CreateWindow ( "gaze", SDL_WINDOWPOS_UNDEFINED, 
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

            if( window == nullptr ) {
               throw std::string ("window failed");
            }
         }

         ~Window() noexcept {
            SDL_DestroyWindow( window );

         }

         SDL_Window* window = nullptr;

   };

   class Renderer {
      public:
         Renderer( Window& win ) {
            renderer = SDL_CreateRenderer( win.window, -1, SDL_RENDERER_ACCELERATED );
            if (renderer == nullptr) {
               throw std::string ("renderer failed");
            }
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
         }

         ~Renderer() noexcept {
            SDL_DestroyRenderer( renderer );
            renderer = nullptr;
         }

         void clear () {
            SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
            SDL_RenderClear( renderer );
         }

         SDL_Renderer* renderer = nullptr;
   };

   class Image {
      public:
         Image () {
            int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
            if ( !( IMG_Init( imgFlags ) & imgFlags ) ) {
               throw std::string("SDL_image failed");
            }
         }

         ~Image() noexcept {
            IMG_Quit();
         }
   };

   class TTF {
      public:
         TTF (std::string fontpath) {
            if (TTF_Init () == -1) {
               throw std::string("SDL_TTF failed!");
            }

            font = TTF_OpenFont(fontpath.c_str(), 15);
            if (font == nullptr) {
               throw std::string("SDL_TTF failed to load font");
            }
         }

         ~TTF() noexcept {
            TTF_CloseFont( font );
            font = nullptr;
            TTF_Quit();
         }

      private:
         TTF_Font* font = nullptr;
   };

   class Surface {
      public:
         Surface (std::string path) {
            SDL_Surface* surface = IMG_Load (path.c_str());
            if ( surface == nullptr ) {
               throw std::string("SDL_Image couldn't load image file");
            }
         }

         ~Surface() noexcept {
            SDL_FreeSurface ( surface );
            surface = nullptr;
         }

         SDL_Surface* surface = nullptr;
   };

}

#endif
