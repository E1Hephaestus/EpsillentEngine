#ifndef UI_LAYER_H
#define UI_LAYER_H

#include "config/config.hpp"
#include "core/layer.hpp"
#include "ui/view.hpp"
#include "ui/ui_controller.hpp"

class ENGINE_API UILayer: public Layer{
private:
    UIController * m_controller;
public:
    UILayer();
    ~UILayer();
    void on_update(float dt);
    void on_render();

    void set_controller(UIController*);
};

#endif