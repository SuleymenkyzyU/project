#include "Tower.h"
#include "Game.h"
#include "Resource.h"

void
Tower::_init()
{
  // set basement
  spSprite basement = new Sprite;
  basement->setResAnim(res::ui.getResAnim("Game_Basement"));
  basement->setAnchor(0.5f, 0.5f);
  basement->attachTo(_view);
  _blocks.push_back(basement);

  _towerLine = _view->getPosition().y + basement->getSize().y;
}

void
Tower::_update(const oxygine::UpdateState& us)
{
  if (_height < 7) {
    return;
  }

  _angle += 0.5f / us.dt;

  float x = _game->getSize().x / 2 + std::sin(_angle) * _shakeValue / 10;
  _view->setPosition(x, _view->getPosition().y);
}

Tower::FallResult
Tower::addBlock(spSprite block, float x)
{
  float posX = x - getPosition().x;
  float delta = std::abs(_lastPosX - posX);

  if (delta > blockWidthHit) {
    if (delta > blockWidthHit * 2) {
      return FallResult::Miss;
    }
    return FallResult::Hit;
  }

  _shakeValue += delta;
  _lastPosX = posX;
  ++_height;

  _scores += blockWidthHit - delta;

  block->detach();
  block->setAnchor(0.5f, 1.0f);
  block->setPosition(posX, 0);
  block->setPriority(10);
  block->attachTo(_view);

  _blocks.push_front(block);

  return FallResult::Success;
}

void
Tower::offsetDown(float offset, int ms)
{
  if (_blocks.size() > 1) {
    for (auto const& b : _blocks) {
      if (_towerLine + b->getPosition().y - b->getSize().y > _game->getSize().y) {
        b->detach();
        _blocks.pop_back();
        break;
      }
      auto pos = b->getPosition();
      b->addTween(Actor::TweenPosition(pos.x, pos.y + offset), ms);
    }
  }
}
