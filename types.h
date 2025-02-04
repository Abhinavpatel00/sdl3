#include<math.h>
#include <stdint.h>
#include <SDL3/SDL.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int32 bool32;
typedef float real32;
typedef double real64;

#define global static
#define local static
#define internal static

#define ArrayCount(arr) (sizeof((arr)) / (sizeof((arr)[0])))
#define Kilobytes(number) ((number) * 1024ull)
#define Megabytes(number) (Kilobytes(number) * 1024ull)
#define Gigabytes(number) (Megabytes(number) * 1024ull)
#define Terabytes(number) (Gigabytes(number) * 1024ull)

#ifdef HANDMADE_SLOW
#define Assert(expression) if(!(expression)) { *(int*) 0 = 0; }
#else
#define Assert(expression)
#endif

inline uint32
SafeTruncateUInt64(uint64 Value) {
  Assert(Value <= 0xFFFFFFFF);
  uint32 Result = (uint32)Value;
  return Result;
}

typedef struct {
    SDL_Renderer *Renderer;
    int Width;
    int Height;
} game_offscreen_buffer;

#define Pi32 3.14159265359

typedef struct {
  uint32 *Tiles;
} tile_map;

typedef struct {
  uint32 TileMapX;
  uint32 TileMapY;
  uint32 RelTileX;
  uint32 RelTileY;
} tile_map_position;

typedef struct {
  uint32 AbsTileX;
  uint32 AbsTileY;

  // NOTE: relative to lower left corner
  real32 TileRelX;
  real32 TileRelY;
} world_position;

typedef struct {
  world_position PlayerPos;
} game_state;

typedef struct {
  uint32 TileMapShift;
  uint32 TileMapMask;
  uint32 TileMapDim;

  int32 TileCountX;
  int32 TileCountY;

  uint32 TileMapCountX;
  uint32 TileMapCountY;

  real32 TileSizeInPixels;
  real32 TileSizeInMeters;
  real32 MetersToPixels;

  tile_map *TileMaps;
} world;


inline int32
RoundReal32ToUint32(real32 Input) {
  uint32 Result = (uint32)(Input + 0.5f);
  return Result;
}

inline int32
FloorReal32ToInt32(real32 Value) {
  int32 Result = (int32)floor(Value);
  return Result;
}

inline real32
Sin(real32 Value) {
  real32 Result = sinf(Value);
  return Result;
}

inline real32
Cos(real32 Value) {
  real32 Result = cosf(Value);
  return Result;
}
