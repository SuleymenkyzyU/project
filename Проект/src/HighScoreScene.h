#ifndef TOWERBLOCKS_HIGHSCORESCENE_H
#define TOWERBLOCKS_HIGHSCORESCENE_H

#include "Scene.h"
#include <vector>

using namespace oxygine;

DECLARE_SMART(HighScoreScene, spHighScoreScene);
class HighScoreScene : public Scene
{
public:
  static spHighScoreScene instance;

  HighScoreScene();

  static constexpr size_t getScoresRecords() { return scores; }

private:
  static constexpr size_t scores = 3;

  std::vector<spTextField> _scores;

  void _show() override;
  void _hide() override;

  void onClick(oxygine::Event* ev);
};

#endif // TOWERBLOCKS_HIGHSCORESCENE_H
