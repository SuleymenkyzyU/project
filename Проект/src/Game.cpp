#include "Game.h"
#include "GameScene.h"
#include "HighScoreScene.h"
#include "MainMenuScene.h"
#include "Resource.h"
#include "ScoreStorage.h"

void
Game::init()
{
  // scene layer would have size of display
  setSize(oxygine::getStage()->getSize());

  // add background stage
  _background = new Background;
  _background->init({}, this);

  // add crane as game object
  _crane = new Crane;
  _crane->init({ getSize().x / 2, -120 }, this);

  _tower = new Tower;
  _towerLine = getSize().y - 300;
  _tower->init({ getSize().x / 2, _towerLine }, this);

  TextStyle style =
    TextStyle(res::ui.getResFont("main")).withColor(Color::White).withFontSize(48).alignMiddle().alignLeft();

  _textScores = new TextField;
  _textScores->setPosition(10, getSize().y / 4);
  _textScores->setStyle(style);
  _textScores->setText("Score: " + std::to_string(_tower->getScores()));
  _textScores->attachTo(this);

  _textLifes = new TextField;
  _textLifes->setPosition(10, _textScores->getPosition().y + 60);
  _textLifes->setStyle(style);
  _textLifes->setText("Lifes: " + std::to_string(_lifes));
  _textLifes->attachTo(this);

  _textTowerHeight = new TextField;
  _textTowerHeight->setPosition(10, _textLifes->getPosition().y + 60);
  _textTowerHeight->setStyle(style);
  _textTowerHeight->setText("Height: " + std::to_string(_tower->getTowerHeight()));
  _textTowerHeight->attachTo(this);
}

void
Game::doUpdate(const oxygine::UpdateState& us)
{
  _crane->update(us);
  _tower->update(us);
}

void
Game::doThrowBlock()
{
  spSprite block = _crane->doThrowBlock();
  if (!block) {
    return;
  }

  block->setAnchor(0.5f, 0.5f);
  block->attachTo(this);

  auto tween = block->addTween(Actor::TweenPosition(block->getPosition().x, _towerLine - block->getSize().y), 800);
  tween->addEventListener(TweenEvent::DONE, [this, block](Event*) {
    auto result = _tower->addBlock(block, block->getPosition().x);
    switch (result) {
      case Tower::FallResult::Success: {
        _tower->offsetDown(100.0f, 140);
        _background->offsetDown(100.0f, 140);

        if (_tower->getTowerHeight() % 5 == 0) {
          _background->addCloud();
        }

        break;
      }

      case Tower::FallResult::Hit: {
        --_lifes;
        spTweenQueue hitTween = new TweenQueue;
        hitTween->add(Actor::TweenY(block->getPosition().y + block->getSize().y / 2), 120);
        hitTween->add(Actor::TweenRotationDegrees(90), 80);
        hitTween->add(Actor::TweenY(getSize().y + block->getSize().y), 160);
        hitTween->add(Actor::TweenAlpha(0), 100);
        block->addTween(hitTween)->detachWhenDone();
        break;
      }

      case Tower::FallResult::Miss: {
        --_lifes;
        auto tweenMiss =
          block->addTween(Actor::TweenPosition(block->getPosition().x, getSize().y + block->getSize().y), 300);
        tweenMiss->detachWhenDone();
        break;
      }
    }

    _textScores->setText("Score: " + std::to_string(_tower->getScores()));
    _textLifes->setText("Lifes: " + std::to_string(_lifes));
    _textTowerHeight->setText("Height: " + std::to_string(_tower->getTowerHeight()));

    if (_lifes == 0) {
      ScoreStorage<HighScoreScene::getScoresRecords()>::store(_tower->getScores());

      spSprite background = new Sprite;
      background->setResAnim(res::ui.getResAnim("Game_bg_gameover"));
      background->attachTo(this);

      TextStyle style =
        TextStyle(res::ui.getResFont("main")).withColor(Color::White).withFontSize(78).alignMiddle().alignBaseline();

      spTextField scores = new TextField;
      scores->setPosition(getSize().x / 2, getSize().y * 0.75f);
      scores->setStyle(style);
      scores->setText(std::to_string(_tower->getScores()));
      scores->attachTo(this);

      _crane->stop();
      auto t = background->addTween(TweenDummy(), 3000);
      t->addEventListener(TweenEvent::DONE, [this](Event*) {
        this->_clock->pause();
        GameScene::instance->changeScene(MainMenuScene::instance);
      });
    }
  });
}