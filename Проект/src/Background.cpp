#include "Background.h"
#include "Game.h"
#include "Resource.h"

void
Background::offsetDown(float offset, int ms)
{
  for (auto iter = _objects.begin(); iter != _objects.end();) {
    auto& pos = iter->first->getPosition();

    if (pos.y > _game->getSize().y + iter->first->getSize().y) {
      iter = _objects.erase(iter);
      continue;
    }

    iter->first->addTween(Actor::TweenPosition(pos.x, pos.y + offset * iter->second), ms);
    ++iter;
  }
}

void
Background::addCloud()
{
  // all cloud have random speed
  auto cloudSpeed = static_cast<timeMS>(scalar::randFloat(15000.0f, 30000.0f));

  spSprite cloud = new Sprite;
  cloud->setResAnim(res::ui.getResAnim("Cloud1"));
  cloud->setPosition(-1 * cloud->getSize().x, -1 * cloud->getSize().y);
  cloud->attachTo(_view);
  cloud->addTween(Actor::TweenX(_game->getSize().x), cloudSpeed, -1, true);

  _objects.emplace_front(std::move(cloud), 1.0f);
}

void
Background::_init()
{
  // create start background
  spSprite bgStart = new Sprite;
  bgStart->setResAnim(res::ui.getResAnim("Game_bg_start"));
  bgStart->attachTo(_view);

  spSprite sun = new Sprite;
  sun->setResAnim(res::ui.getResAnim("Sun"));
  sun->setPosition(sun->getSize().x, -1 * sun->getSize().y);
  sun->attachTo(_view);

  _objects.emplace_front(std::move(bgStart), 0.5f);
  _objects.emplace_front(std::move(sun), 0.1f);
}
