#include <gtest/gtest.h>
#include "figures.h"
#include <cmath>
#include <string>

static double findArea(int n, double R) {
    static const double PI = 3.14159265358979323846;
    return (static_cast<double>(n) / 2.0) * R * R * std::sin(2.0 * PI / static_cast<double>(n));
}

TEST(test_01, basic_test_set) {
    Pentagon p(0.0, 0.0, 1.0);
    Point c = p.center();
    EXPECT_NEAR(c.x, 0.0, 1e-9);
    EXPECT_NEAR(c.y, 0.0, 1e-9);
}

TEST(test_02, basic_test_set) {
    double R = 1.0;
    Pentagon p(0.0, 0.0, R);
    double area = static_cast<double>(p);
    double expect = findArea(5, R);
    EXPECT_NEAR(area, expect, 1e-6);
}

TEST(test_03, basic_test_set) {
    Pentagon p(1.0, 2.0, 3.0);
    EXPECT_EQ(p.vertices().size(), 5);
}

TEST(test_04, basic_test_set) {
    Hexagon h(1.5, -2.5, 2.0);
    Point c = h.center();
    EXPECT_NEAR(c.x, 1.5, 1e-9);
    EXPECT_NEAR(c.y, -2.5, 1e-9);
}

TEST(test_05, basic_test_set) {
    double R = 2.0;
    Hexagon h(0.0, 0.0, R);
    double area = static_cast<double>(h);
    double expect = findArea(6, R);
    EXPECT_NEAR(area, expect, 1e-6);
}

TEST(test_06, basic_test_set) {
    Hexagon h(-1.0, 0.5, 1.0);
    EXPECT_EQ(h.vertices().size(), 6);
}

TEST(test_07, basic_test_set) {
    Octagon o(-3.0, 4.0, 1.5);
    Point c = o.center();
    EXPECT_NEAR(c.x, -3.0, 1e-9);
    EXPECT_NEAR(c.y, 4.0, 1e-9);
}

TEST(test_08, basic_test_set) {
    double R = 3.0;
    Octagon o(0.0, 0.0, R);
    double area = static_cast<double>(o);
    double expect = findArea(8, R);
    EXPECT_NEAR(area, expect, 1e-6);
}

TEST(test_09, basic_test_set) {
    Octagon o(2.0, 2.0, 0.8);
    EXPECT_EQ(o.vertices().size(), 8);
}
