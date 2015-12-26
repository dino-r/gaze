#include "SDL2/SDL.h"
#include "input.hpp"

Input::Input () {
   mousePos_ = {0,0};
   relativeMotion_ = {0,0};
   wheel_ = 0;
   mouseDown_ = false;
   quit_ = false;
   next_ = false;
   previous_ = false;
}

void Input::handleEvent( SDL_Event* e ) {
   //defaults that need to be reset every time
   next_ = false;
   previous_ = false;

   switch(e->type) {
      case SDL_MOUSEMOTION:
         int x, y;

         SDL_GetMouseState( &x, &y );
         mousePos_ = {x, y};

         SDL_GetRelativeMouseState( &x, &y );
         relativeMotion_ = {x, y};
         break;

      case SDL_MOUSEBUTTONDOWN:
         switch(e->button.button) {
            case SDL_BUTTON_LEFT:
               mouseDown_ = true;
               break;
            case SDL_BUTTON_X1:
               wheel_ = 1;
               break;
            case SDL_BUTTON_X2:
               wheel_ = -1;
               break;
            default:
               break;
         }
         break;

      case SDL_MOUSEBUTTONUP:
         switch(e->button.button) {
            case SDL_BUTTON_LEFT:
               mouseDown_ = false;
               break;
            case SDL_BUTTON_X1:
               wheel_ = 0;
               break;
            case SDL_BUTTON_X2:
               wheel_ = 0;
               break;
            default:
               break;
         }
         break;

      case SDL_KEYDOWN:
         switch(e->key.keysym.sym) {
            case SDLK_j:
               next_ = true;
               break;
            case SDLK_k:
               previous_ = true;
               break;
         }
         break;

      case SDL_KEYUP:
         switch(e->key.keysym.sym) {
            case SDLK_j:
               //next_ = false;
               break;
            case SDLK_k:
               //previous_ = false;
               break;
         }
         break;

      case SDL_QUIT:
         quit_ = true;
         break;

      default:
         break;
   }
}

SDL_Point Input::getMousePosition() {
   return mousePos_;
}

SDL_Point Input::getRelativeMotion() {
   return relativeMotion_;
}

int Input::getWheel() {
   return wheel_;
}

bool Input::mouseIsDown() {
   return mouseDown_;
}

bool Input::quit() {
   return quit_;
}

bool Input::next() {
   return next_;
}

bool Input::previous() {
   return previous_;
}
