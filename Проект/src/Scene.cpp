#include "Scene.h"

Scene::Scene()
{
  _view = new oxygine::Actor;
  _view->setSize(oxygine::getStage()->getSize());
}

void
Scene::changeScene(spScene next)
{
  hide();
  next->show();
}

void
Scene::show()
{
  // add scene view to root
  oxygine::getStage()->addChild(_view);
  // and fade in
  _view->setAlpha(0);
  _view->addTween(oxygine::Actor::TweenAlpha(255), 300);

  // call virtual method (overloaded in inherited classes)
  _show();
}

void
Scene::hide()
{
  oxygine::spTween tween = _view->addTween(oxygine::Actor::TweenAlpha(0), 300);
  // detach when done
  tween->detachWhenDone();
  // and call Scene::hidden
  tween->addDoneCallback(CLOSURE(this, &Scene::hidden));
}

void
Scene::hidden(oxygine::Event* ev)
{
  // hidden called by Tween
  // notify HiddenEvent listeners

  HiddenEvent he(this);
  dispatchEvent(&he);
}