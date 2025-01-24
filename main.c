#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_cpuinfo.h>

int main(int argc, char *argv[]) {

   printf("Number of logical CPU cores: %d\n", SDL_GetNumLogicalCPUCores());
   printf("L1 cache line size: %d bytes\n", SDL_GetCPUCacheLineSize());
   printf("Has AltiVec: %s\n", SDL_HasAltiVec() ? "true" : "false");
   printf("Has MMX: %s\n", SDL_HasMMX() ? "true" : "false");
   printf("Has SSE: %s\n", SDL_HasSSE() ? "true" : "false");
   printf("Has SSE2: %s\n", SDL_HasSSE2() ? "true" : "false");
   printf("Has SSE3: %s\n", SDL_HasSSE3() ? "true" : "false");
   printf("Has SSE4.1: %s\n", SDL_HasSSE41() ? "true" : "false");
   printf("Has SSE4.2: %s\n", SDL_HasSSE42() ? "true" : "false");
   printf("Has AVX: %s\n", SDL_HasAVX() ? "true" : "false");
   printf("Has AVX2: %s\n", SDL_HasAVX2() ? "true" : "false");
   printf("Has AVX-512F: %s\n", SDL_HasAVX512F() ? "true" : "false");
   printf("Has ARM SIMD: %s\n", SDL_HasARMSIMD() ? "true" : "false");
   printf("Has NEON: %s\n", SDL_HasNEON() ? "true" : "false");
   printf("Has LSX: %s\n", SDL_HasLSX() ? "true" : "false");
   printf("Has LASX: %s\n", SDL_HasLASX() ? "true" : "false");
   printf("System RAM: %d MiB\n", SDL_GetSystemRAM());
   printf("SIMD alignment: %zu bytes\n", SDL_GetSIMDAlignment());

   SDL_Quit();
   return 0;
}