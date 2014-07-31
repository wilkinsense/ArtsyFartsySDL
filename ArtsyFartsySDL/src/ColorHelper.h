#pragma once

typedef unsigned int ColorRGBA;
typedef ColorRGBA ColorARGB;

class ColorHelper
{
public:
  static ColorRGBA ColorFromRGBA(int r, int g, int b, int a)
  {
    ColorRGBA colorToReturn = ((r % 255) << 3) | ((g % 255) << 2) | ((b % 255) << 1) | (a % 255);
    return colorToReturn;
  }
};