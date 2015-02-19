#ifndef TERRAIN_H
#define TERRAIN_H

extern unsigned char giGroundToTerrain[];

enum TERRAIN_IDX {
  TERRAIN_IDX_WATER = 0,
  TERRAIN_IDX_GRASS = 1,
  TERRAIN_IDX_SNOW = 2,
  TERRAIN_IDX_SWAMP = 3,
  TERRAIN_IDX_LAVA = 4,
  TERRAIN_IDX_DESERT = 5,
  TERRAIN_IDX_DIRT = 6,
  TERRAIN_IDX_WASTELAND = 7,
  TERRAIN_IDX_BEACH = 8,
};

#endif