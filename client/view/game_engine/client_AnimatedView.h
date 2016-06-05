#ifndef CLIENT_ANIMATEDVIEW_H_
#define CLIENT_ANIMATEDVIEW_H_

#include "../../../common/common_MapConstants.h"
#include "client_RenderedView.h"
#include "../../../common/common_Point.h"
#include <SDL2pp/SDL2pp.hh>

class AnimatedView : public RenderedView {
  protected:
    unsigned int x,y;

  public:
    AnimatedView(SDL2pp::Renderer *renderer) : RenderedView(renderer) {
    }

    virtual ~AnimatedView() {
    }

    virtual void draw(Point &massCenter) = 0;

    virtual void move(unsigned int x, unsigned int y) {
        setX(x);
        setY(y);
    }

    //It should implement
    unsigned int getX() { return x; }
    unsigned int getY() { return y; }
    void setX(unsigned int x) { this->x = x; }
    void setY(unsigned int y) { this->y = y; }

};

#endif