#ifndef TOWERBLOCKS_MAINMENUSCENE_H
#define TOWERBLOCKS_MAINMENUSCENE_H

#include "Scene.h"
#include <array>
#include <vector>

DECLARE_SMART(MainMenuScene, spMainMenuScene);
class MainMenuScene : public Scene
{
public:
  static spMainMenuScene instance;

  MainMenuScene();

private:
  std::vector<oxygine::spSprite> _buttons;
  std::array<std::string, 4> _buttonsNames{ "MainMenu_btn_Play", "MainMenu_btn_HighScore", "MainMenu_btn_HowToPlay" };

  void onClick(oxygine::Event* ev);
  void onMouseMove(oxygine::Event* ev);
};

#endif // TOWERBLOCKS_MAINMENUSCENE_H
