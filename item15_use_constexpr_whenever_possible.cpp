//
// Created by marci_000 on 31.01.2017.
//

#include "item15_use_constexpr_whenever_possible.h"

struct Point {
  // Not needed - but would not cause to fail static_assert
  //constexpr Point& operator=(const Point& pt) {
  //  x = pt.x;
  //  y = pt.y;
  //}

  // Not needed - but would not cause to fail static_assert
  //Point& operator=(const Point& pt) {
  //  x = pt.x;
  //  y = pt.y;
  //}

  // Those are fine since c++14, in earlier c++11 setX and setY would be const due to constexpr use.
  // also void  type was not a literal type then and was not allowed to use in constexpr funcitons.
  constexpr void setX(int newX) noexcept { x = newX; }
  constexpr void setY(int newY) noexcept { y = newY; }

  int x;
  int y;
};

constexpr Point point_add(const Point& pt1, const Point& pt2) noexcept {
  Point pt{0, 0};
  pt.x = pt1.x + pt2.x;
  pt.y = pt1.y + pt2.y;
  return pt;
}

void item15_use_constexpr_whenever_possible::run() {
  constexpr Point pt1{1,2};
  constexpr Point pt2{3,4};
  constexpr Point pt12 = point_add(pt1, pt2);
  static_assert(pt12.x == 4 && pt12.y == 6, "");

  // That is wrong, constexpr makes variable const, contrary to that making function constexpr does not makes it const.
  //pt12.setX(11);
  //pt12.setY(22);
  //static_assert(pt12.x == 11 && pt12.y == 22, "");
}
