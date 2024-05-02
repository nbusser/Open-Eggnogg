#pragma once

#include <vector>

enum Tile { NONE, WALL };

class Map {
public:
  size_t width;
  size_t height;
  std::vector<std::vector<Tile>> grid;

  Map();

  void loadMapFile(const std::string &mapFilePath);

private:
  void clearGrid();
  void buildGrid(const size_t width, const size_t height);
};
