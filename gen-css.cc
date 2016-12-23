#include <iostream>
#include "desolarized.h"

static int to256(float x) {
  x = 255 * x;
  if (x < 0) {
    return 0;
  }
  if (x > 255) {
    return 255;
  }
  return std::roundf(x);
}

static std::ostream& operator<<(std::ostream& out, const RGB& rgb) noexcept {
  out << "rgb(";
  out << to256(rgb.R()) << ", ";
  out << to256(rgb.G()) << ", ";
  out << to256(rgb.B()) << ")";
  return out;
}

int main() {
  std::cout << ":root {\n";

  for (int i = 0; i < desolarized::kNumberOfColours; ++i) {
    const std::string& name = desolarized::kColourName[i];
    const RGB base = desolarized::kColours[i];
    const RGB light = desolarized::kColoursLight[i];
    const RGB dark = desolarized::kColoursDark[i];

    std::cout << "\t--desolarized-" << name << ": " << base << ";\n";
    std::cout << "\t--desolarized-light-" << name << ": " << light << ";\n";
    std::cout << "\t--desolarized-dark-" << name << ": " << dark << ";\n";
  }

  std::cout << "}";
}
