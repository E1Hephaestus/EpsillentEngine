#ifndef SCENE_H
#define SCENE_H

#include "engine/core/component.hpp"

//temp
#include "engine/render/renderer_2d.hpp"
#include "engine/scenes/scene_graph.hpp"

#include "engine/physics/collider2d.hpp"
// to achieve at least something in MY word
// you HAVE TO inherit from THIS class

class SceneManager;

class BaseScene{
protected:
    SceneGraph scene_graph;
    std::list<GameObject*> garbage;
    Renderer2D scene_renderer;
    std::list<Collider2D*> physics;
    BaseScene();
    ~BaseScene();
private:
    friend class GameObject;
    friend class SceneManager;
    //WARNNING!
    //mark as garbage an ALREADY "destroy()-ed" object
    void mark_garbage(GameObject*);
    bool has_grabage(){return !garbage.empty();}
    void clear_garbage();
public:
    //Engine purpose function
    //Override only if you REALLY understand what is going ond
    virtual void update(const float);
    //Engine purpose function
    //Override only if you REALLY understand what is going on
    virtual void render();
    
    virtual void on_update(const float){};
    virtual void on_init(){};
    // ALL PROCESSORS INITIALIZATIONS SHOULD BE DONE HERE
    virtual void on_start(){};
    virtual void on_destroy(){};


    void object_introduce(GameObject*);

    Renderer2D& renderer(){return scene_renderer;}

};

#endif