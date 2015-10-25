#ifndef INPUT_H
#define INPUT_H

class Input {
   public:
      Input();

      void handleEvent(SDL_Event* e);

      SDL_Point getMousePosition();
      SDL_Point getRelativeMotion();
      int  getWheel();
      bool mouseIsDown();
      bool quit();

      bool next();
      bool previous();

   private:
      SDL_Point relativeMotion_;
      SDL_Point mousePos_;
      int wheel_;
      bool mouseDown_;
      bool quit_;
      bool next_;
      bool previous_;
};
#endif
