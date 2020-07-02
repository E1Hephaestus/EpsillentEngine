#ifndef DRAW_CALL_H
#define DRAW_CALL_H

#include "SFML/Graphics.hpp"
#include "engine/core/typedefs.hpp"

class DrawCallInterface{
private:
    static DrawCallInterface * smp_singleton;
    sf::RenderWindow* window;
    uint64 draw_calls;
public:
    DrawCallInterface(sf::RenderWindow*);
    ~DrawCallInterface();
    static void draw(const sf::Drawable&, const sf::Transform&);
    static void draw(const sf::Drawable&);
    static void swap_buffers();
    static void clear();
};

#endif