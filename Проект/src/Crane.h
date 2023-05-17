#ifndef TOWERBLOCKS_CRANE_H
#define TOWERBLOCKS_CRANE_H

#include "Unit.h"
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Crane, spCrane);

/// Crane is mechanical pendulum for throw blocks on tower.
class Crane : public Unit
{
public:
  /// Throw block from crane and get this block.
  /// @return block from crane
  spSprite doThrowBlock();

  /// Start crane work from base.
  void start();

  /// Stop crane work
  void stop();

protected:
  const float pi{ std::acos(-1.0f) };
  const float gravity{ -0.981f };
  const timeMS speedAnimation{ 360 };

  /// Three states for crane: move from base, work as pendulum and move to base.
  enum class States
  {
    Stopped,
    FromBase,
    Working,
    ToBase,
  };

  void _init() override;
  void _update(const UpdateState& us) override;

  /// Start crane return to base.
  void moveToBase();

  /// Get new random block sprite
  /// @return new random block
  spSprite getNewBlock() const;

  States _state{ States::Stopped };
  spSprite _block;

  Vector2 _basePosition;

  // Pendulum simulation parameters
  float _length{ 0.00f }, _speed{ -8.5f }, _velocity{ 0.0f }, _acceleration{ 0.0f }, _angle{ -0.5f * pi };
};

#endif // TOWERBLOCKS_CRANE_H
