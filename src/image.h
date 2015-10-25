#ifndef IMAGE_H
#define IMAGE_H

#include <vector>


class Image {
   public:
      //Constructor
      Image();

      //Destructor
      ~Image();

      void free();

      bool loadFromFile(SDL_Renderer* renderer);
      void render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr, SDL_Rect* dstrect = nullptr, 
                   double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
      int getWidth();
      int getHeight();
      void insertPaths(std::vector<std::string> paths);
      void next();
      void previous();

      
   private:
      SDL_Texture* texture_;
      int width_;
      int height_;
      int id_;
      std::vector<std::string> paths_;
};

#endif
