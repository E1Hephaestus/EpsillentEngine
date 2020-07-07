#include "scenes/scene_cluster.hpp"


void SceneCluster::update(float dt){
    for(Component* comp: components){
        comp->update(dt);
    }
}

void SceneCluster::render(){
    renderer2d.render();
}