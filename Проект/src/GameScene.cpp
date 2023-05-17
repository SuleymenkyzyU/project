#include "GameScene.h"
#include "Resource.h"

spGameScene GameScene::instance; // NOLINT

void
GameScene::newGame()
{
  _game = new Game();
  _game->init();
  _game->attachTo(_view);
  _game->setClock(new Clock);
}

GameScene::GameScene()
{
  newGame();

  // create menu button
  // TODO: Make exit button under Game Actor for pause and go to Main Menu.
  // TODO: If game is paused - add Resume button to Main Menu.

  _view->addEventListener(oxygine::TouchEvent::CLICK, CLOSURE(this, &GameScene::onClick));
}

void
GameScene::onClick(oxygine::Event* ev)
{
  // every click button throw block
  _game->doThrowBlock();
}

void
GameScene::_show()
{
  if (_game->isGameOver()) {
    _game->detach();
    newGame();
  }
  _game->getClock()->resetPause();
}
