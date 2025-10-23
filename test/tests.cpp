#include <gtest/gtest.h>
#include "figures.h"
#include <sstream>
#include <cmath>
#include <string>

static double expected_regular_polygon_area(int n, double R) {
    static const double PI = 3.14159265358979323846;
    return (static_cast<double>(n) / 2.0) * R * R * std::sin(2.0 * PI / static_cast<double>(n));
}

TEST(test_01, basic_test_set) {
    Polygon p;
    EXPECT_EQ(p.vertices().size(), 3);
    Point c = p.center();
    EXPECT_NEAR(c.x, 0.0, 1e-9);
    EXPECT_NEAR(c.y, 0.0, 1e-9);
    double area = static_cast<double>(p);
    double expect = expected_regular_polygon_area(3, 1.0);
    EXPECT_NEAR(area, expect, 1e-6);
}

TEST(test_02, basic_test_set) {
    Pentagon p(0.0, 0.0, 1.0);
    EXPECT_EQ(p.vertices().size(), 5);
    Point c = p.center();
    EXPECT_NEAR(c.x, 0.0, 1e-9);
    EXPECT_NEAR(c.y, 0.0, 1e-9);
    double area = static_cast<double>(p);
    double expect = expected_regular_polygon_area(5, 1.0);
    EXPECT_NEAR(area, expect, 1e-6);
}

TEST(test_03, basic_test_set) {
    Hexagon h(1.0, 2.0, 2.0);
    Octagon o(-1.0, -2.0, 3.0);
    EXPECT_EQ(h.vertices().size(), 6);
    EXPECT_EQ(o.vertices().size(), 8);
    double ah = static_cast<double>(h);
    double ao = static_cast<double>(o);
    double eh = expected_regular_polygon_area(6, 2.0);
    double eo = expected_regular_polygon_area(8, 3.0);
    EXPECT_NEAR(ah, eh, 1e-6);
    EXPECT_NEAR(ao, eo, 1e-6);
    Point ch = h.center();
    Point co = o.center();
    EXPECT_NEAR(ch.x, 1.0, 1e-9);
    EXPECT_NEAR(ch.y, 2.0, 1e-9);
    EXPECT_NEAR(co.x, -1.0, 1e-9);
    EXPECT_NEAR(co.y, -2.0, 1e-9);
}

TEST(test_04, basic_test_set) {
    Pentagon p(0.0, 0.0, 1.5);
    std::stringstream ss;
    ss << p;
    std::string out = ss.str();
    EXPECT_NE(out.find("Полигон n"), std::string::npos);
    std::stringstream in("1.0 2.0 3.0");
    Pentagon p2;
    in >> p2;
    Point c = p2.center();
    EXPECT_NEAR(c.x, 1.0, 1e-9);
    EXPECT_NEAR(c.y, 2.0, 1e-9);
    double area = static_cast<double>(p2);
    double expect = expected_regular_polygon_area(5, 3.0);
    EXPECT_NEAR(area, expect, 1e-6);
}

TEST(test_05, basic_test_set) {
    FiguresArray arr;
    EXPECT_EQ(arr.size(), 0);
    Figure* f1 = new Pentagon(0.0, 0.0, 1.0);
    Figure* f2 = new Hexagon(0.0, 0.0, 2.0);
    arr.pushBack(f1);
    arr.pushBack(f2);
    EXPECT_EQ(arr.size(), 2);
    double total = arr.totalArea();
    double expect = expected_regular_polygon_area(5, 1.0) + expected_regular_polygon_area(6, 2.0);
    EXPECT_NEAR(total, expect, 1e-6);
    arr.removeAt(0);
    EXPECT_EQ(arr.size(), 1);
    double total2 = arr.totalArea();
    EXPECT_NEAR(total2, expected_regular_polygon_area(6, 2.0), 1e-6);
}

TEST(test_06, basic_test_set) {
    FiguresArray a1;
    a1.pushBack(new Pentagon(0.0, 0.0, 1.0));
    a1.pushBack(new Hexagon(1.0, 1.0, 2.0));
    EXPECT_EQ(a1.size(), 2);
    FiguresArray a2 = a1;
    EXPECT_EQ(a2.size(), 2);
    a1.removeAt(0);
    EXPECT_EQ(a1.size(), 1);
    EXPECT_EQ(a2.size(), 2);
    double expect = expected_regular_polygon_area(5, 1.0) + expected_regular_polygon_area(6, 2.0);
    EXPECT_NEAR(a2.totalArea(), expect, 1e-6);
}

TEST(test_07, basic_test_set) {
    Pentagon a(0.0, 0.0, 1.0);
    Pentagon b(0.0, 0.0, 1.0);
    Pentagon c(0.0, 0.0, 2.0);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    Hexagon h1(0.0, 0.0, 1.0);
    EXPECT_FALSE(a == h1);
}

TEST(test_08, basic_test_set) {
    FiguresArray arr;
    arr.pushBack(new Pentagon(0.0, 0.0, 1.0));
    EXPECT_THROW(arr.removeAt(5), std::out_of_range);
}

TEST(test_09, basic_test_set) {
    FiguresArray arr;
    arr.pushBack(new Pentagon(0.0, 0.0, 1.0));
    arr.pushBack(new Hexagon(1.0, 2.0, 2.0));
    std::stringstream s_centers;
    arr.printCenters(s_centers);
    std::string out_centers = s_centers.str();
    EXPECT_NE(out_centers.find("центр"), std::string::npos);
    EXPECT_NE(out_centers.find("Фигура[0]"), std::string::npos);
    std::stringstream s_verts;
    arr.printVertices(s_verts);
    std::string out_verts = s_verts.str();
    EXPECT_NE(out_verts.find("вершины"), std::string::npos);
    std::stringstream s_areas;
    arr.printAreas(s_areas);
    std::string out_areas = s_areas.str();
    EXPECT_NE(out_areas.find("площадь"), std::string::npos);
    std::stringstream s_all;
    arr.printAll(s_all);
    std::string out_all = s_all.str();
    EXPECT_NE(out_all.find("центр"), std::string::npos);
    EXPECT_NE(out_all.find("площадь"), std::string::npos);
    EXPECT_NE(out_all.find("Координаты вершин"), std::string::npos);
}

TEST(test_10, basic_test_set) {
    Polygon a(5, 0.0, 0.0, 1.0);
    Polygon b;
    b = a;
    EXPECT_EQ(b.vertices().size(), 5);
    EXPECT_NEAR(b.center().x, 0.0, 1e-9);
    EXPECT_NEAR(b.center().y, 0.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(b), expected_regular_polygon_area(5, 1.0), 1e-6);
    Polygon c(6, 1.0, 1.0, 2.0);
    Polygon d;
    d = std::move(c);
    EXPECT_EQ(d.vertices().size(), 6);
    EXPECT_NEAR(d.center().x, 1.0, 1e-9);
    EXPECT_NEAR(d.center().y, 1.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(d), expected_regular_polygon_area(6, 2.0), 1e-6);
}

TEST(test_11, basic_test_set) {
    Pentagon p_src(0.0, 0.0, 1.0);
    Polygon target(3, 0.0, 0.0, 1.0);
    const Figure& ref = p_src;
    target.operator=(ref);
    EXPECT_EQ(target.vertices().size(), 5);
    EXPECT_NEAR(static_cast<double>(target), expected_regular_polygon_area(5, 1.0), 1e-6);
    Polygon target2(3, 0.0, 0.0, 1.0);
    Pentagon tmp(2.0, 2.0, 2.5);
    target2.operator=(static_cast<Figure&&>(tmp));
    EXPECT_NEAR(target2.center().x, 2.0, 1e-9);
    EXPECT_NEAR(target2.center().y, 2.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(target2), expected_regular_polygon_area(5, 2.5), 1e-6);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

