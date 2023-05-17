#ifndef TOWERBLOCKS_SCORESTORAGE_H
#define TOWERBLOCKS_SCORESTORAGE_H

#include <array>
#include <cstddef>
#include <fstream>

template<size_t N>
class ScoreStorage
{
public:
  using score_type = unsigned int;

  static std::array<score_type, N> load();
  static bool store(score_type score);
};

template<size_t N>
auto
ScoreStorage<N>::load() -> std::array<ScoreStorage::score_type, N>
{
  std::ifstream infile;
  infile.open("scores", std::ios::in); // TODO: delete hardcode filename

  std::array<score_type, N> results{};
  for (unsigned int& result : results) {
    if (!(infile >> result)) {
      break;
    }
  }

  return results;
}

template<size_t N>
bool
ScoreStorage<N>::store(ScoreStorage::score_type score)
{
  std::array<ScoreStorage::score_type, N> results = load();

  bool isRecord = false;
  for (auto& s : results) {
    if (score > s) {
      isRecord = true;
      std::swap(score, s);
    }
  }

  std::ofstream outfile;
  outfile.open("scores", std::ios::out | std::ios::trunc); // TODO: delete hardcode filename

  for (const auto& s : results) {
    if (!(outfile << s << '\n')) {
      break;
    }
  }

  return isRecord;
}

#endif // TOWERBLOCKS_SCORESTORAGE_H
