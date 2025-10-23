#include "figures.h"
#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    return figure.print(os);
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    return figure.read(is);
}

Polygon::Polygon()
    : n(3), x(0.0), y(0.0), radius(1.0), vect()
{
    findVertices();
}

Polygon::Polygon(int sides, double x, double y, double r)
    : n(sides), x(x), y(y), radius(r), vect()
{
    if (n < 3) {
        throw std::invalid_argument("Число сторон должно быть >= 3");
    } else if (radius <= 0.0) {
        throw std::invalid_argument("Радиус должен быть положительным");
    } else {
        findVertices();
    }
}

Polygon::Polygon(const Polygon& other)
    : n(other.n), x(other.x), y(other.y), radius(other.radius), vect(other.vect)
{
}

Polygon::Polygon(Polygon&& other)
    : n(other.n), x(other.x), y(other.y), radius(other.radius), vect(std::move(other.vect))
{
    other.n = 0;
    other.x = 0.0;
    other.y = 0.0;
    other.radius = 0.0;
}

Polygon::~Polygon() {
}

Figure* Polygon::clone() const {
    return new Polygon(*this);
}

Point Polygon::center() const {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

std::ostream& Polygon::print(std::ostream& os) const {
    os << "Полигон n = " << n << " центр = (" << x << ", " << y << ") радиус = " << radius << "\n";
    os << "Координаты вершин: ";
    for (std::size_t i = 0; i < vect.size(); ++i) {
        os << "(" << vect[i].x << ", " << vect[i].y << ")";
        if (i + 1 < vect.size()) {
            os << " ";
        }
    }
    os << "\n";
    return os;
}

std::istream& Polygon::read(std::istream& is) {
    double x;
    double y;
    double r;
    is >> x >> y >> r;
    if (!is) {
        throw std::runtime_error("Некорректный ввод для полигона");
    } else {
        x = x;
        y = y;
        radius = r;
        findVertices();
    }
    return is;
}

Polygon::operator double() const {
    return findArea();
}

Polygon& Polygon::operator=(const Polygon& other) {
    if (this != &other) {
        n = other.n;
        x = other.x;
        y = other.y;
        radius = other.radius;
        vect = other.vect;
    }
    return *this;
}

Polygon& Polygon::operator=(Polygon&& other) {
    if (this != &other) {
        n = other.n;
        x = other.x;
        y = other.y;
        radius = other.radius;
        vect = std::move(other.vect);
        other.n = 0;
        other.x = 0.0;
        other.y = 0.0;
        other.radius = 0.0;
    }
    return *this;
}

Figure& Polygon::operator=(const Figure& other) {
    const Polygon* p = dynamic_cast<const Polygon*>(&other);
    if (p == 0) {
        throw std::invalid_argument("Невозможно присвоить объект другого типа");
    } else {
        this->operator=(*p);
        return *this;
    }
}

Figure& Polygon::operator=(Figure&& other) {
    Polygon* p = dynamic_cast<Polygon*>(&other);
    if (p == 0) {
        throw std::invalid_argument("Невозможно переместить объект другого типа");
    } else {
        this->operator=(std::move(*p));
        return *this;
    }
}

bool Polygon::equals(const Figure& other) const {
    const Polygon* p = dynamic_cast<const Polygon*>(&other);
    if (p == 0) {
        return false;
    } else if (n != p->n) {
        return false;
    } else if (std::abs(x - p->x) > 1e-9) {
        return false;
    } else if (std::abs(y - p->y) > 1e-9) {
        return false;
    } else if (std::abs(radius - p->radius) > 1e-9) {
        return false;
    } else {
        return true;
    }
}

const std::vector<Point>& Polygon::vertices() const noexcept {
    return vect;
}

void Polygon::findVertices() {
    vect.clear();
    vect.reserve(static_cast<std::size_t>(n));
    const double PI = 3.14159265358979323846;
    double step = (2.0 * PI) / static_cast<double>(n);
    double start = 0.0;
    for (int i = 0; i < n; ++i) {
        double a = start + step * static_cast<double>(i);
        double x = x + radius * std::cos(a);
        double y = y + radius * std::sin(a);
        Point p;
        p.x = x;
        p.y = y;
        vect.push_back(p);
    }
}

double Polygon::findArea() const {
    double sum = 0.0;
    std::size_t m = vect.size();
    if (m < 3) {
        return 0.0;
    } else {
        for (std::size_t i = 0; i < m; ++i) {
            std::size_t j = (i + 1) % m;
            sum += vect[i].x * vect[j].y - vect[j].x * vect[i].y;
        }
        return std::abs(sum) * 0.5;
    }
}

Pentagon::Pentagon()
    : Polygon(5, 0.0, 0.0, 1.0)
{
}

Pentagon::Pentagon(double cx, double cy, double r)
    : Polygon(5, cx, cy, r)
{
}

Figure* Pentagon::clone() const {
    return new Pentagon(*this);
}

Hexagon::Hexagon()
    : Polygon(6, 0.0, 0.0, 1.0)
{
}

Hexagon::Hexagon(double cx, double cy, double r)
    : Polygon(6, cx, cy, r)
{
}

Figure* Hexagon::clone() const {
    return new Hexagon(*this);
}

Octagon::Octagon()
    : Polygon(8, 0.0, 0.0, 1.0)
{
}

Octagon::Octagon(double cx, double cy, double r)
    : Polygon(8, cx, cy, r)
{
}

Figure* Octagon::clone() const {
    return new Octagon(*this);
}

FiguresList::FiguresList()
    : figures(nullptr), count(0), capacity(0)
{
}

FiguresList::FiguresList(const FiguresList& other)
    : figures(nullptr), count(0), capacity(0)
{
    if (other.count > 0) {
        capacity = other.count;
        figures = new Figure*[capacity];
        for (std::size_t i = 0; i < other.count; ++i) {
            figures[i] = other.figures[i]->clone();
        }
        count = other.count;
    }
}

FiguresList::FiguresList(FiguresList&& other)
    : figures(other.figures), count(other.count), capacity(other.capacity)
{
    other.figures = nullptr;
    other.count = 0;
    other.capacity = 0;
}

FiguresList::~FiguresList() noexcept {
    if (figures != nullptr) {
        for (std::size_t i = 0; i < count; ++i) {
            delete figures[i];
        }
        delete[] figures;
    }
}

FiguresList& FiguresList::operator=(const FiguresList& other) {
    if (this != &other) {
        if (figures != nullptr) {
            for (std::size_t i = 0; i < count; ++i) {
                delete figures[i];
            }
            delete[] figures;
            figures = nullptr;
            count = 0;
            capacity = 0;
        }
        if (other.count > 0) {
            capacity = other.count;
            figures = new Figure*[capacity];
            for (std::size_t i = 0; i < other.count; ++i) {
                figures[i] = other.figures[i]->clone();
            }
            count = other.count;
        }
    }
    return *this;
}

FiguresList& FiguresList::operator=(FiguresList&& other) {
    if (this != &other) {
        if (figures != nullptr) {
            for (std::size_t i = 0; i < count; ++i) {
                delete figures[i];
            }
            delete[] figures;
        }
        figures = other.figures;
        count = other.count;
        capacity = other.capacity;
        other.figures = nullptr;
        other.count = 0;
        other.capacity = 0;
    }
    return *this;
}

void FiguresList::pushBack(Figure* figure) {
    expand();
    figures[count] = figure;
    ++count;
}

void FiguresList::removeAt(std::size_t index) {
    if (index >= count) {
        throw std::out_of_range("Индекс вне диапазона");
    } else {
        delete figures[index];
        for (std::size_t i = index; i + 1 < count; ++i) {
            figures[i] = figures[i + 1];
        }
        --count;
    }
}

std::size_t FiguresList::size() const {
    return count;
}

Figure* FiguresList::get(std::size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Индекс вне диапазона");
    } else {
        return figures[index];
    }
}

double FiguresList::totalArea() const {
    double sum = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        sum += static_cast<double>(*figures[i]);
    }
    return sum;
}

std::ostream& FiguresList::printAll(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        os << "Фигура[" << i << "]\n";
        Point c = figures[i]->center();
        os << " центр = (" << c.x << ", " << c.y << ")\n";
        os << " площадь = " << static_cast<double>(*figures[i]) << "\n";
        os << " вершины: ";
        figures[i]->print(os);
        os << "\n";
    }
    return os;
}

std::ostream& FiguresList::printCenters(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        Point c = figures[i]->center();
        os << "Фигура[" << i << "] центр = (" << c.x << ", " << c.y << ")\n";
    }
    return os;
}

std::ostream& FiguresList::printVertices(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        os << "Фигура[" << i << "] вершины: ";
        figures[i]->print(os);
    }
    return os;
}

std::ostream& FiguresList::printAreas(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        os << "Фигура[" << i << "] площадь = " << static_cast<double>(*figures[i]) << "\n";
    }
    return os;
}

void FiguresList::expand() {
    if (count + 1 <= capacity) {
        return;
    } else {
        std::size_t newcap;
        if (capacity == 0) {
            newcap = 4;
        } else {
            newcap = capacity * 2;
        }
        Figure** nd = new Figure*[newcap];
        for (std::size_t i = 0; i < count; ++i) {
            nd[i] = figures[i];
        }
        delete[] figures;
        figures = nd;
        capacity = newcap;
    }
}
