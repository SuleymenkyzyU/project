#include "MainMenuScene.h"
#include "GameScene.h"
#include "HighScoreScene.h"
#include "HowToPlayScene.h"
#include "Resource.h"

spMainMenuScene MainMenuScene::instance; // NOLINT

MainMenuScene::MainMenuScene()
{
  // create background
  oxygine::spSprite background = new oxygine::Sprite;
  background->setResAnim(res::ui.getResAnim("MainMenu_Background"));
  background->attachTo(_view);

  float center_x = _view->getSize().x / 2;
  float start_y = _view->getSize().y * 0.33f;

  oxygine::EventCallback cbClick = CLOSURE(this, &MainMenuScene::onClick);
  oxygine::EventCallback cbMouseMove = CLOSURE(this, &MainMenuScene::onMouseMove);

  for (size_t i = 0; i < _buttonsNames.size(); ++i) {
    oxygine::spSprite button = new oxygine::Sprite();
    button->setResAnim(res::ui.getResAnim(_buttonsNames[i]));
    button->setName(_buttonsNames[i]);

    button->setPosition(center_x - button->getSize().x / 2, start_y + button->getSize().y * (i * 1.2f));
    button->addEventListener(oxygine::TouchEvent::CLICK, cbClick);
    button->addEventListener(oxygine::TouchEvent::OVER, cbMouseMove);
    button->addEventListener(oxygine::TouchEvent::OUT, cbMouseMove);

    button->addEventListener(oxygine::TouchEvent::CLICK,
                             [](oxygine::Event* e) -> void { oxygine::logs::messageln("button clicked"); });

    button->attachTo(_view);

    _buttons.emplace_back(button);
  }
}

void
MainMenuScene::onClick(oxygine::Event* ev)
{
  std::string id = ev->currentTarget->getName();
  auto button = _view->getChildT<oxygine::Sprite>(id);

  button->setColor(oxygine::Color::White);
  button->addTween(oxygine::Sprite::TweenColor(oxygine::Color::Green), 500, 1, true);

  if (id == _buttonsNames[0]) {
    changeScene(GameScene::instance);
    return;
  }

  if (id == _buttonsNames[1]) {
    changeScene(HighScoreScene::instance);
    return;
  }

  if (id == _buttonsNames[2]) {
    changeScene(HowToPlayScene::instance);
    return;
  }
}

void
MainMenuScene::onMouseMove(oxygine::Event* ev)
{
  std::string id = ev->currentTarget->getName();
  auto button = _view->getChildT<oxygine::Sprite>(id);

  if (ev->type == oxygine::TouchEvent::OVER) {
    button->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(64, 64, 64, 0)), 300);
  }

  if (ev->type == oxygine::TouchEvent::OUT) {
    button->addTween(oxygine::Sprite::TweenAddColor(oxygine::Color(0, 0, 0, 0)), 300);
  }
}
