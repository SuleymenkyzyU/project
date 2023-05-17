#include "Unit.h"
#include "Game.h"

void
Unit::init(const oxygine::Vector2& pos, Game* game)
{
  _game = game;

  _view = new oxygine::Actor;
  _view->setPosition(pos);
  _view->attachTo(game);

  // should be overloaded in inherited classes
  _init();
}

void
Unit::update(const UpdateState& us)
{
  // should be overloaded in inherited classes
  _update(us);
}
