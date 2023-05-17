#ifndef TOWERBLOCKS_GAMESCENE_H
#define TOWERBLOCKS_GAMESCENE_H

#include "Game.h"
#include "MainMenuScene.h"
#include "Scene.h"

DECLARE_SMART(GameScene, spGameScene);
class GameScene : public Scene
{
public:
  static spGameScene instance;

  GameScene();

private:
  void onClick(oxygine::Event* ev);
  void _show() override;
  void newGame();

  spGame _game;
};

#endif // TOWERBLOCKS_GAMESCENE_H
