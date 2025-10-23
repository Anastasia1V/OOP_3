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
    : n(3), cx(0.0), cy(0.0), radius(1.0), verts()
{
    findVertices();
}

Polygon::Polygon(int sides, double x, double y, double r)
    : n(sides), cx(x), cy(y), radius(r), verts()
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
    : n(other.n), cx(other.cx), cy(other.cy), radius(other.radius), verts(other.verts)
{
}

Polygon::Polygon(Polygon&& other)
    : n(other.n), cx(other.cx), cy(other.cy), radius(other.radius), verts(std::move(other.verts))
{
    other.n = 0;
    other.cx = 0.0;
    other.cy = 0.0;
    other.radius = 0.0;
}

Polygon::~Polygon() {
}

Figure* Polygon::clone() const {
    return new Polygon(*this);
}

Point Polygon::center() const {
    Point p;
    p.x = cx;
    p.y = cy;
    return p;
}

std::ostream& Polygon::print(std::ostream& os) const {
    os << "Полигон n = " << n << " центр = (" << cx << ", " << cy << ") радиус = " << radius << "\n";
    os << "Координаты вершин: ";
    for (std::size_t i = 0; i < verts.size(); ++i) {
        os << "(" << verts[i].x << ", " << verts[i].y << ")";
        if (i + 1 < verts.size()) {
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
        cx = x;
        cy = y;
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
        cx = other.cx;
        cy = other.cy;
        radius = other.radius;
        verts = other.verts;
    }
    return *this;
}

Polygon& Polygon::operator=(Polygon&& other) {
    if (this != &other) {
        n = other.n;
        cx = other.cx;
        cy = other.cy;
        radius = other.radius;
        verts = std::move(other.verts);
        other.n = 0;
        other.cx = 0.0;
        other.cy = 0.0;
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
    } else if (std::abs(cx - p->cx) > 1e-9) {
        return false;
    } else if (std::abs(cy - p->cy) > 1e-9) {
        return false;
    } else if (std::abs(radius - p->radius) > 1e-9) {
        return false;
    } else {
        return true;
    }
}

const std::vector<Point>& Polygon::vertices() const noexcept {
    return verts;
}

void Polygon::findVertices() {
    verts.clear();
    verts.reserve(static_cast<std::size_t>(n));
    const double PI = 3.14159265358979323846;
    double step = (2.0 * PI) / static_cast<double>(n);
    double start = 0.0;
    for (int i = 0; i < n; ++i) {
        double a = start + step * static_cast<double>(i);
        double x = cx + radius * std::cos(a);
        double y = cy + radius * std::sin(a);
        Point p;
        p.x = x;
        p.y = y;
        verts.push_back(p);
    }
}

double Polygon::findArea() const {
    double sum = 0.0;
    std::size_t m = verts.size();
    if (m < 3) {
        return 0.0;
    } else {
        for (std::size_t i = 0; i < m; ++i) {
            std::size_t j = (i + 1) % m;
            sum += verts[i].x * verts[j].y - verts[j].x * verts[i].y;
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
    : figuresData(nullptr), count(0), capacity(0)
{
}

FiguresList::FiguresList(const FiguresList& other)
    : figuresData(nullptr), count(0), capacity(0)
{
    if (other.count > 0) {
        capacity = other.count;
        figuresData = new Figure*[capacity];
        for (std::size_t i = 0; i < other.count; ++i) {
            figuresData[i] = other.figuresData[i]->clone();
        }
        count = other.count;
    }
}

FiguresList::FiguresList(FiguresList&& other)
    : figuresData(other.figuresData), count(other.count), capacity(other.capacity)
{
    other.figuresData = nullptr;
    other.count = 0;
    other.capacity = 0;
}

FiguresList::~FiguresList() noexcept {
    if (figuresData != nullptr) {
        for (std::size_t i = 0; i < count; ++i) {
            delete figuresData[i];
        }
        delete[] figuresData;
    }
}

FiguresList& FiguresList::operator=(const FiguresList& other) {
    if (this != &other) {
        if (figuresData != nullptr) {
            for (std::size_t i = 0; i < count; ++i) {
                delete figuresData[i];
            }
            delete[] figuresData;
            figuresData = nullptr;
            count = 0;
            capacity = 0;
        }
        if (other.count > 0) {
            capacity = other.count;
            figuresData = new Figure*[capacity];
            for (std::size_t i = 0; i < other.count; ++i) {
                figuresData[i] = other.figuresData[i]->clone();
            }
            count = other.count;
        }
    }
    return *this;
}

FiguresList& FiguresList::operator=(FiguresList&& other) {
    if (this != &other) {
        if (figuresData != nullptr) {
            for (std::size_t i = 0; i < count; ++i) {
                delete figuresData[i];
            }
            delete[] figuresData;
        }
        figuresData = other.figuresData;
        count = other.count;
        capacity = other.capacity;
        other.figuresData = nullptr;
        other.count = 0;
        other.capacity = 0;
    }
    return *this;
}

void FiguresList::pushBack(Figure* figure) {
    expand();
    figuresData[count] = figure;
    ++count;
}

void FiguresList::removeAt(std::size_t index) {
    if (index >= count) {
        throw std::out_of_range("Индекс вне диапазона");
    } else {
        delete figuresData[index];
        for (std::size_t i = index; i + 1 < count; ++i) {
            figuresData[i] = figuresData[i + 1];
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
        return figuresData[index];
    }
}

double FiguresList::totalArea() const {
    double sum = 0.0;
    for (std::size_t i = 0; i < count; ++i) {
        sum += static_cast<double>(*figuresData[i]);
    }
    return sum;
}

std::ostream& FiguresList::printAll(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        os << "Фигура[" << i << "]\n";
        Point c = figuresData[i]->center();
        os << " центр = (" << c.x << ", " << c.y << ")\n";
        os << " площадь = " << static_cast<double>(*figuresData[i]) << "\n";
        os << " вершины: ";
        figuresData[i]->print(os);
        os << "\n";
    }
    return os;
}

std::ostream& FiguresList::printCenters(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        Point c = figuresData[i]->center();
        os << "Фигура[" << i << "] центр = (" << c.x << ", " << c.y << ")\n";
    }
    return os;
}

std::ostream& FiguresList::printVertices(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        os << "Фигура[" << i << "] вершины: ";
        figuresData[i]->print(os);
    }
    return os;
}

std::ostream& FiguresList::printAreas(std::ostream& os) const {
    for (std::size_t i = 0; i < count; ++i) {
        os << "Фигура[" << i << "] площадь = " << static_cast<double>(*figuresData[i]) << "\n";
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
            nd[i] = figuresData[i];
        }
        delete[] figuresData;
        figuresData = nd;
        capacity = newcap;
    }
}
