#include "color.hpp"
#include "noise.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <thread>

using namespace std;

double CubicLerp(double a, double m, double b, double t) {
  return (1 - t) * (1 - t) * (1 - t) * a + 3 * (1 - t) * (1 - t) * t * m +
         3 * (1 - t) * t * t * b + t * t * t;
}

int main() {
  srand(time(NULL));
  FastNoiseLite perlin;
  perlin.SetFrequency(0.05);
  perlin.SetFractalOctaves(50);

  int seed1 = rand();
  int seed2 = rand();
  int seed3 = seed1+seed2;
  double t = 0.0;

  while (true) {
    auto const w(WEXITSTATUS(std::system("exit `tput cols`")));
    auto const h(WEXITSTATUS(std::system("exit `tput lines`")));
    int newSeed = (int)CubicLerp(seed1, seed3, seed2, t);
    perlin.SetSeed(newSeed);
    for (float y = 0.0f; y < h; y++) {
      for (float x = 0.0f; x < w; x++) {
        double value = perlin.GetNoise(x, y, 0.0f);
        string c;
        if (value < -0.5) {
          c = "\u2588";
          cout << color::reset << color::red << c;
        } else if (value < 0) {
          c = "\u2593";
          cout << color::reset << color::yellow << c;
        } else if (value < 0.5) {
          c = "\u2592";
          cout << color::reset << color::green << c;
        } else {
          c = "\u2591";
          cout << color::reset << color::blue << c;
        }
      }
      cout << endl;
    }
    t += 0.0000001;
    if (t >= 1.0) {
      seed1 = seed2;
      seed2 = rand();
      t = 0.0;
    }
    this_thread::sleep_for(chrono::milliseconds(5000));
    system("clear"); // or "clear" on Linux/Mac
  }
  return 0;
}
