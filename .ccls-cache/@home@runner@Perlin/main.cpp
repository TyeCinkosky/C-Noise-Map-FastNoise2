#include "noise.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

using namespace std;

double lerp(double a, double b, double t) {
    return (1 - t) * a + t * b;
}

int main() {
  srand(time(NULL));
  FastNoiseLite perlin;
  perlin.SetFrequency(0.1);
  perlin.SetFractalOctaves(20);

  int seed1 = rand();
  int seed2 = rand();
  double t = 0.0;

    while (true) {
        perlin.SetSeed((int)lerp(seed1, seed2, t));
            for (float y = 0.0f; y < 25; y++) {
            for (float x = 0.0f; x < 80; x++) {
                double value = perlin.GetNoise(x, y, 0.0f);
                char c;
                if (value < -0.5) c = '.';
                else if (value < 0) c = ',';
                else if (value < 0.5) c = '+';
                else c = '#';
                cout << c;
            }
            cout << endl;
        }
        t += 0.0001;
        if (t >= 1.0) {
            seed1 = seed2;
            seed2 = rand();
            t = 0.0;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("clear"); // or "clear" on Linux/Mac
    }
    return 0;
}
