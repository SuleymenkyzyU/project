#ifndef TOWERBLOCKS_HOWTOPLAYSCENE_H
#define TOWERBLOCKS_HOWTOPLAYSCENE_H

#include "Scene.h"

DECLARE_SMART(HowToPlayScene, spHowToPlayScene);
class HowToPlayScene : public Scene
{
public:
  static spHowToPlayScene instance;

  HowToPlayScene();

private:
  void onClick(oxygine::Event* ev);
};

#endif // TOWERBLOCKS_HOWTOPLAYSCENE_H
