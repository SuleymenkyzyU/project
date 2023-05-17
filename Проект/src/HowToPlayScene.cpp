#include "HowToPlayScene.h"
#include "MainMenuScene.h"
#include "Resource.h"

spHowToPlayScene HowToPlayScene::instance; // NOLINT

HowToPlayScene::HowToPlayScene()
{
  // create background
  oxygine::spSprite background = new oxygine::Sprite;
  background->setResAnim(res::ui.getResAnim("HowToPlay_Background"));
  background->attachTo(_view);

  // create back button
  oxygine::spSprite button = new oxygine::Sprite;
  button->setName("back");
  button->setResAnim(res::ui.getResAnim("btn_Back"));
  button->setPosition(button->getSize() / 2);

  oxygine::EventCallback callback = CLOSURE(this, &HowToPlayScene::onClick);
  button->addEventListener(oxygine::TouchEvent::CLICK, callback);

  button->attachTo(_view);
}

void
HowToPlayScene::onClick(oxygine::Event* ev)
{
  std::string id = ev->currentTarget->getName();

  if (id == "back") {
    changeScene(MainMenuScene::instance);
  }
}
