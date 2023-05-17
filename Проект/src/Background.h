#ifndef TOWERBLOCKS_BACKGROUND_H
#define TOWERBLOCKS_BACKGROUND_H

#include "Unit.h"
#include <list>

using namespace oxygine;

DECLARE_SMART(Background, spBackground);

/// The Background is responsible for background objects in game.
class Background : public Unit
{
public:
  /// Move down all objects
  /// @param offset height in pixel
  /// @param ms time for move in milliseconds
  void offsetDown(float offset, int ms);

  /// Add cloud on background.
  void addCloud();

protected:
  // List of objects and depth factor.
  std::list<std::pair<spSprite, float>> _objects;

  void _init() override;
};

#endif // TOWERBLOCKS_BACKGROUND_H
