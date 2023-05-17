#ifndef TOWERBLOCKS_TOWER_H
#define TOWERBLOCKS_TOWER_H

#include "Unit.h"
#include <list>

using namespace oxygine;

DECLARE_SMART(Tower, spTower);
class Tower : public Unit
{
public:
  enum class FallResult
  {
    Success,
    Hit,
    Miss,
  };

  Tower() = default;

  FallResult addBlock(spSprite block, float x);
  void offsetDown(float offset, int ms);

  unsigned int getScores() const noexcept { return _scores; }
  unsigned int getTowerHeight() const noexcept { return _height; }

protected:
  const float blockWidthHit{ 60 };

  std::list<spSprite> _blocks;

  float _towerLine, _lastPosX{ 0 };
  float _shakeValue, _angle{ 0.0f };
  unsigned int _height{ 0 }, _scores{ 0 };

  void _init() override;
  void _update(const UpdateState& us) override;
};

#endif // TOWERBLOCKS_TOWER_H
