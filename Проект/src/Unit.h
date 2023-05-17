#ifndef TOWERBLOCKS_UNIT_H
#define TOWERBLOCKS_UNIT_H

#include "oxygine-framework.h"

using namespace oxygine;

// forward declaration
class Game;

DECLARE_SMART(Unit, spUnit);

/// Base class for game units.
class Unit : public Object
{
public:

  /// Initialize game unit
  /// @param pos position in game for unit
  /// @param game pointer on game for attach unit
  void init(const Vector2& pos, Game* game);

  /// Update handler for game unit
  /// @param us UpdateState with information about update
  void update(const UpdateState& us);

  /// Getter for game unit position in game
  /// @return position in game
  const Vector2& getPosition() const { return _view->getPosition(); }

protected:
  // Two methods for derived classes
  virtual void _init() {}
  virtual void _update(const UpdateState& us) {}

  oxygine::spActor _view;
  Game* _game{ nullptr };
};

#endif // TOWERBLOCKS_UNIT_H
