#include "HighScoreScene.h"
#include "MainMenuScene.h"
#include "Resource.h"
#include "ScoreStorage.h"
#include <array>
#include <cassert>
#include <fstream>

spHighScoreScene HighScoreScene::instance; // NOLINT

HighScoreScene::HighScoreScene()
{
  // create background
  oxygine::spSprite background = new Sprite;
  background->setResAnim(res::ui.getResAnim("HighScores_Background"));
  background->attachTo(_view);

  // show scores in table
  TextStyle style =
    TextStyle(res::ui.getResFont("main")).withColor(Color::White).withFontSize(52).alignMiddle().alignLeft();

  _scores.reserve(scores);
  for (size_t i = 0; i < scores; ++i) {
    spTextField score = new TextField;
    score->setPosition(110, 136 + i * 68);
    score->setStyle(style);
    score->setText("0");
    score->attachTo(_view);

    _scores.push_back(score);
  }

  // create back button
  oxygine::spSprite button = new oxygine::Sprite;
  button->setName("back");
  button->setResAnim(res::ui.getResAnim("btn_Back"));
  button->setPosition(button->getSize() / 2);

  oxygine::EventCallback callback = CLOSURE(this, &HighScoreScene::onClick);
  button->addEventListener(oxygine::TouchEvent::CLICK, callback);

  button->attachTo(_view);
}

void
HighScoreScene::_show()
{
  std::array<unsigned int, scores> results = ScoreStorage<scores>::load();

  assert(_scores.size() == results.size());
  for (size_t i = 0; i < results.size(); ++i) {
    _scores[i]->setText(std::to_string(results[i]));
  }
}

void
HighScoreScene::_hide()
{
  // ??
}

void
HighScoreScene::onClick(oxygine::Event* ev)
{
  std::string id = ev->currentTarget->getName();

  if (id == "back") {
    changeScene(MainMenuScene::instance);
  }
}