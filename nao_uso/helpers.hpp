#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

typedef pair<int, int> position;

enum direction {
  UP,
  LEFT,
  DOWN,
  RIGHT
};