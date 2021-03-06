#ifndef CLIENT_BIGENERGYVIEW_H_
#define CLIENT_BIGENERGYVIEW_H_

#include "client_RenderedView.h"
#include "../../../common/common_Point.h"
#include "../../../common/common_MapConstants.h"
#include "../../controller/client_SoundController.h"
#include <SDL2pp/SDL2pp.hh>

class BigEnergyView : public AnimatedView {
private:
  SDL2pp::Texture *texture;

public:
  BigEnergyView(unsigned int id, SDL2pp::Renderer *renderer) : AnimatedView(id, renderer) {
    texture = new SDL2pp::Texture(*getRenderer(), "res/drawable/powerups/energy/energy_big.png");
  }

  virtual ~BigEnergyView() {
    SoundController::play(("res/sound/powerups/energyup.wav"));
    delete texture;
  }

  virtual SDL2pp::Texture * getTexture(ORIENTATION orient) {
    return texture;
  }

};

#endif
