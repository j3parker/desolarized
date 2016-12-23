#ifndef _DESOLARIZED_H_
#define _DESOLARIZED_H_

#include <array>
#include "colour.h"

namespace desolarized {

const LAB kYellow = LAB(79, 10, 65);
const LAB kOrange = LAB(65, 45, 300);
const LAB kRed = LAB(50, 65, 45);
const LAB kMagenta = LAB(50, 65, -5);
const LAB kViolet = LAB(50, 15, -45);
const LAB kBlue = LAB(55, -10, -45);
const LAB kCyan = LAB(60, -35, -5);
const LAB kGreen = LAB(60, -25, 65);

namespace {
const int kLABStepSize = 10;
}

#define COLOUR_VARIANTS(c)                \
  const LAB c##Light = c + LAB(kLABStepSize, 0, 0); \
  const LAB c##Dark = c - LAB(kLABStepSize, 0, 0);

COLOUR_VARIANTS(kYellow);
COLOUR_VARIANTS(kOrange);
COLOUR_VARIANTS(kRed);
COLOUR_VARIANTS(kMagenta);
COLOUR_VARIANTS(kViolet);
COLOUR_VARIANTS(kBlue);
COLOUR_VARIANTS(kCyan);
COLOUR_VARIANTS(kGreen);

#undef COLOUR_VARIANTS

enum class Colour : unsigned int {
  Yellow,
  Orange,
  Red,
  Magenta,
  Violet,
  Blue,
  Cyan,
  Green
};

const int kNumberOfColours = 8;

#define COLOUR_ARRAY(var)                                    \
  const std::array<LAB, kNumberOfColours> kColours##var = {  \
      kYellow##var, kOrange##var, kRed##var,  kMagenta##var, \
      kViolet##var, kBlue##var,   kCyan##var, kGreen##var};

COLOUR_ARRAY();
COLOUR_ARRAY(Light);
COLOUR_ARRAY(Dark);

std::array<std::string, kNumberOfColours> kColourName = {
    "yellow", "orange", "red", "magenta", "violet", "blue", "cyan", "green"};

#undef COLOUR_ARRAY

const LAB kBase03 = LAB(10, 0, -10);
const LAB kBase02 = LAB(25, 0, -10);
const LAB kBase01 = LAB(50, 0, -9);
const LAB kBase00 = LAB(60, 0, -9);
const LAB kBase0 = LAB(75, 0, -7);
const LAB kBase1 = LAB(85, 0, -5);
const LAB kBase2 = LAB(95, 0, -4);
const LAB kBase3 = LAB(101, 0, 0);

enum class Shade : unsigned int {
  Foreground,
  Foreground2,
  Background,
  Background2
};

const int kNumberOfShades = 4;

#define SHADE_ARRAY                                  \
  const std::array<LAB, kNumberOfShades> kShades = { \
      kForeground, kForeground2, kBackground, kBackground2};

namespace light {
const LAB kForeground = kBase03;
const LAB kForeground2 = kBase00;
const LAB kBackground = kBase3;
const LAB kBackground2 = kBase2;
const LAB kMuted = kBase2;

SHADE_ARRAY;
}

namespace dark {
const LAB kForeground = kBase0;
const LAB kForeground2 = kBase01;
const LAB kBackground = kBase03;
const LAB kBackground2 = kBase02;
const LAB kMuted = kBase02;

SHADE_ARRAY;
}

#undef SHADE_ARRAY
}

#endif
