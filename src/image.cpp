#include "SDL.hpp"
#include <string>

#include "image.hpp"


Image::Image() {
   texture_ = nullptr;
   width_   = 0;
   height_  = 0;
   id_      = 0;
   paths_   = std::vector<std::string>();
}

Image::~Image() noexcept{
   free();
}
void Image::free() {
   if( texture_ != nullptr ) {
      SDL_DestroyTexture( texture_ );
      texture_ = nullptr;
      width_   = 0;
      height_  = 0;
      id_      = 0;
      paths_ = std::vector<std::string> ();
   }
}

bool Image::loadFromFile(SDL_Renderer* renderer) {
   auto path = paths_[id_];

   SDL_Texture* newTexture = nullptr;

   SDL_Surface* loadedSurface = IMG_Load (path.c_str());
   if( loadedSurface == nullptr ) {
      printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
   } else {
      newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
      if( newTexture == nullptr ) {
         printf( "Unable to create a texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
      } else {
         width_  = loadedSurface->w;
         height_ = loadedSurface->h;
      }

      SDL_FreeSurface( loadedSurface );
   }

   texture_ = newTexture;
   return texture_ != nullptr;
}

void Image::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* dstrect, 
                   double angle, SDL_Point* center, SDL_RendererFlip flip ) {
   SDL_RenderCopyEx( renderer, texture_, clip, dstrect, angle, center, flip );
}

int Image::getWidth() {
   return width_;
}

int Image::getHeight() {
   return height_;
}

void Image::insertPaths(std::vector<std::string> paths){
   paths_ = paths;
}

void Image::next() {
   if ((int)paths_.size() - 1 >  id_) id_ += 1;
}

void Image::previous() {
   if (id_ > 0) id_ -= 1;
}
