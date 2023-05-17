#include "GameScene.h"
#include "HighScoreScene.h"
#include "HowToPlayScene.h"
#include "MainMenuScene.h"
#include "Resource.h"
#include "oxygine-framework.h"
#include <array>
#include <vector>

void
application_preinit()
{}

void
application_init()
{
  // load resources
  res::load();

  // load scenes
  MainMenuScene::instance = new MainMenuScene;
  GameScene::instance = new GameScene;
  HighScoreScene::instance = new HighScoreScene;
  HowToPlayScene::instance = new HowToPlayScene;

  // show main menu
  MainMenuScene::instance->show();
}

void
application_destroy()
{
  // free scenes
  HowToPlayScene::instance = nullptr;
  HighScoreScene::instance = nullptr;
  GameScene::instance = nullptr;
  MainMenuScene::instance = nullptr;

  res::free();
}

void
application_update()
{}
