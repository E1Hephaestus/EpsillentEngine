#ifndef RENDER_H
#define RENDER_H

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include "engine/components/sprite_2d.hpp"

class Renderer2D{
private:
    std::list<Sprite2D> m_sprites;
public:
    Renderer2D(const Renderer2D&)=delete;
    Renderer2D& operator=(const Renderer2D&)=delete;


    Renderer2D();
    ~Renderer2D();

    void render();

    Sprite2D* sprite_new(GameObject*);
    void sprite_delete(Sprite2D*);

};




#endif