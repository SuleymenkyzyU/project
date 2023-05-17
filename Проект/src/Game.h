#ifndef TOWERBLOCKS_GAME_H
#define TOWERBLOCKS_GAME_H

#include "Background.h"
#include "Crane.h"
#include "Tower.h"
#include "Unit.h"
#include "oxygine-framework.h"
#include <forward_list>

using namespace oxygine;

DECLARE_SMART(Game, spGame);

class Game : public oxygine::Actor
{
  using List = std::forward_list<spUnit>;

public:
  void init();

  void doThrowBlock();

  bool isGameOver() const { return _lifes == 0; }

private:
  spBackground _background;
  spCrane _crane;
  spTower _tower;

  spTextField _textScores;
  spTextField _textLifes;
  spTextField _textTowerHeight;

  float _towerLine;
  unsigned int _lifes{ 5 };

  void doUpdate(const oxygine::UpdateState& us) override;
};

#endif // TOWERBLOCKS_GAME_H
