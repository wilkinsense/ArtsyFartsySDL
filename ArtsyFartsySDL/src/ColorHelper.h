#pragma once

//typedef unsigned int ColorRGBA;
//typedef ColorRGBA ColorARGB;

struct ColorRGBA
{
  int r;
  int g;
  int b;
  int a;

  ColorRGBA() : r(0), g(0), b(0), a(0) {}
  ColorRGBA(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
};

class ColorHelper
{
public:
  static int ColorFromRGBA(int r, int g, int b, int a)
  {
    int colorToReturn = ((r % 255) << 3) | ((g % 255) << 2) | ((b % 255) << 1) | (a % 255);
    return colorToReturn;
  }
};