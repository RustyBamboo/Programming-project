#ifndef GAMEMATH
#define GAMEMATH
#include <iostream>
#include <cmath>

namespace gmath {
//I hate math.
inline float dotProduct(const sf::Vector2f &a, const sf::Vector2f &b) {
    return (a.x * b.x + a.y * b.y);
}
inline sf::Vector2f normalize(const sf::Vector2f &a) {
    float b = sqrt(a.x * a.x + a.y * a.y);
    return sf::Vector2f(a.x / b, a.y / b);
}
inline sf::Vector2f getNormal(const sf::Vector2f &a, const sf::Vector2f &b) {
    return normalize(a + b); //No clue if this is valid
}
inline std::vector<sf::Vector2f> getAllNormals(const std::vector<sf::Vector2f> &points) {
    std::vector<sf::Vector2f> v;
    for (unsigned int i = 0; i < points.size() - 1; ++i) {
        v.push_back(getNormal(points[i], points[i + 1]));
    }
    v.push_back(getNormal(points[0], points[points.size() - 1]));
    return v;
}
inline sf::Vector2f projection(const sf::Vector2f &b, const sf::Vector2f &a) { //b onto a
    return dotProduct(a, b) * a;
}
inline float scalarProjection(const sf::Vector2f &b, const sf::Vector2f &a) { //b onto a
    return dotProduct(a, b);
}
}
#endif
