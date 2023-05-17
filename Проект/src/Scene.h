#ifndef TOWERBLOCKS_SCENE_H
#define TOWERBLOCKS_SCENE_H

#include "oxygine-framework.h"

/// Base class for Scenes
DECLARE_SMART(Scene, spScene);
class Scene : public oxygine::EventDispatcher
{
public:
  Scene();

  class HiddenEvent : public oxygine::Event
  {
  public:
    // define unique int ID with makefourcc 'SHid' = SceneHidden
    enum
    {
      EVENT = makefourcc('S', 'H', 'i', 'd')
    };

    HiddenEvent(Scene* scene_)
      : Event(EVENT)
      , scene(scene_){};
    Scene* scene;
  };

  void show();
  void hide();

  /// Change current scene on next scene.
  /// @param next next scene
  void changeScene(spScene next);

  oxygine::spActor getView() const { return _view; }

protected:
  virtual void _show() {}
  virtual void _hide() {}

  void hidden(oxygine::Event* ev);
  oxygine::spActor _view;
};

#endif // TOWERBLOCKS_SCENE_H
