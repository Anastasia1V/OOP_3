#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>

struct Point
{
    double x;
    double y;
};

class Figure
{
public:
    Figure() = default;
    Figure(const Figure&) = default;
    Figure(Figure&&) = default;
    virtual ~Figure() = default;
    virtual Figure* clone() const = 0;
    virtual Point center() const = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual std::istream& read(std::istream& is) = 0;
    virtual operator double() const = 0;
    virtual Figure& operator=(const Figure& other) = 0;
    virtual Figure& operator=(Figure&& other) = 0;
    virtual bool equals(const Figure& other) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Figure& f);
std::istream& operator>>(std::istream& is, Figure& f);

class Polygon : public Figure
{
public:
    Polygon();
    Polygon(int sides, double cx, double cy, double r);
    Polygon(const Polygon& other);
    Polygon(Polygon&& other);
    ~Polygon();
    Figure* clone() const;
    Point center() const;
    std::ostream& print(std::ostream& os) const;
    std::istream& read(std::istream& is);
    operator double() const;
    Polygon& operator=(const Polygon& other);
    Polygon& operator=(Polygon&& other);
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other);
    bool equals(const Figure& other) const;
    const std::vector<Point>& vertices() const noexcept;

protected:
    void findVertices();
    double findArea() const;
    int n;
    double cx;
    double cy;
    double radius;
    std::vector<Point> verts;
};

class Pentagon : public Polygon
{
public:
    Pentagon();
    Pentagon(double cx, double cy, double r);
    Figure* clone() const;
};

class Hexagon : public Polygon
{
public:
    Hexagon();
    Hexagon(double cx, double cy, double r);
    Figure* clone() const;
};

class Octagon : public Polygon
{
public:
    Octagon();
    Octagon(double cx, double cy, double r);
    Figure* clone() const;
};

class FiguresList
{
public:
    FiguresList();
    FiguresList(const FiguresList& other);
    FiguresList(FiguresList&& other);
    ~FiguresList() noexcept;
    FiguresList& operator=(const FiguresList& other);
    FiguresList& operator=(FiguresList&& other);
    void pushBack(Figure* f);
    void removeAt(std::size_t index);
    std::size_t size() const;
    Figure* get(std::size_t index) const;
    double totalArea() const;
    std::ostream& printAll(std::ostream& os) const;
    std::ostream& printCenters(std::ostream& os) const;
    std::ostream& printVertices(std::ostream& os) const;
    std::ostream& printAreas(std::ostream& os) const;

private:
    void expand();
    Figure** figuresData;
    std::size_t count;
    std::size_t capacity;
};
