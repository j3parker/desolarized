#ifndef _COLOUR_H_
#define _COLOUR_H_

#include <cmath>

struct LAB;
struct XYZ;
struct RGB;

template <class T>
const T kD65 = XYZ(95.047f, 100.0f, 108.883f);

struct LAB final {
 public:
  LAB(float l, float a, float b) noexcept : L_(l), A_(a), B_(b) {}

  float L() const noexcept { return L_; }
  float A() const noexcept { return A_; }
  float B() const noexcept { return B_; }

 private:
  float L_, A_, B_;
};

LAB operator+(const LAB& lhs, const LAB& rhs) noexcept {
  return LAB(lhs.L() + rhs.L(), lhs.A() + rhs.A(), lhs.B() + rhs.B());
}

LAB operator-(const LAB& lhs, const LAB& rhs) noexcept {
  return LAB(lhs.L() - rhs.L(), lhs.A() - rhs.A(), lhs.B() - rhs.B());
}

struct XYZ final {
 public:
  XYZ(float x, float y, float z) noexcept : X_(x), Y_(y), Z_(z) {}

  XYZ(const LAB& lab) noexcept {
    float Y = (lab.L() + 16.0f) / 116.0f;
    float X = Y + (lab.A() / 500.0f);
    float Z = Y - (lab.B() / 200.0f);
    X_ = kD65<XYZ>.X() * f(X);
    Y_ = kD65<XYZ>.Y() * f(Y);
    Z_ = kD65<XYZ>.Z() * f(Z);
  }

  float X() const noexcept { return X_; }
  float Y() const noexcept { return Y_; }
  float Z() const noexcept { return Z_; }

 private:
  static float f(float t) {
    float t3 = t * t * t;
    if (t3 > 0.008856f) {
      return t3;
    }
    return (t - 0.13793103448f) / 7.787f;
  }

  float X_, Y_, Z_;
};

struct RGBLinear final {
 public:
  RGBLinear(float r, float g, float b) noexcept : R_(r), G_(g), B_(b) {}

  RGBLinear(const XYZ& xyz) noexcept {
    float X = xyz.X() / 100.0f;
    float Y = xyz.Y() / 100.0f;
    float Z = xyz.Z() / 100.0f;
    R_ = 3.2406f * X - 1.5372f * Y - 0.4986f * Z;
    G_ = -0.9689f * X + 1.8758f * Y + 0.0415f * Z;
    B_ = 0.0557f * X - 0.2040f * Y + 1.0570f * Z;
  }

  float R() const noexcept { return R_; }
  float G() const noexcept { return G_; }
  float B() const noexcept { return B_; }

 private:
  float R_, G_, B_;
};

struct RGB final {
 public:
  RGB(const LAB& lab) noexcept : RGB(static_cast<XYZ>(lab)) {}
  RGB(const XYZ& xyz) noexcept : RGB(static_cast<RGBLinear>(xyz)) {}
  RGB(const RGBLinear& rgb)
  noexcept : R_(g(rgb.R())), G_(g(rgb.G())), B_(g(rgb.B())) {}

  float R() const noexcept { return R_; }
  float G() const noexcept { return G_; }
  float B() const noexcept { return B_; }

 private:
  static float g(float x) {
    if (x > 0.0031308f) {
      return 1.055 * std::pow(x, 1.0f / 2.4f) - 0.055f;
    }
    return 12.92f * x;
  }

  float R_, G_, B_;
};

#endif
