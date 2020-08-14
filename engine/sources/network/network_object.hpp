#ifndef NETWORK_OBJECT_H
#define NETWORK_OBJECT_H


#include <unordered_map>
#include "config/config.hpp"
#include "core/guid.hpp"
#include "core/net/protocol.hpp"
#include "scenes/scene.hpp"
#include "utils/debug.hpp"
#include "network/objects_protocol.hpp"

class NetworkScene;
class NetworkObjectsDB;

#define NETWORK_CLASS(Name,Inherited)           \
public:                                         \
    static std::string static_network_class(){  \
        return std::string(#Name);              \
    }                                           \
    virtual std::string network_class()override{\
        return std::string(#Name);              \
    }                                           \
    explicit Name(const GUID& guid): Inherited(guid) {}\
private:

struct NetworkVariableTraits{
    std::size_t size;
    void *variable;
    explicit NetworkVariableTraits(std::size_t size,void* data);
};

class NetworkObject: public GameObject{
public:
    enum Type : uint8{
        Originator,
        Imitator
    };
private:
    Type m_type;
    GUID m_guid;
    std::vector<NetworkVariableTraits> m_net_variables;
    float m_delay;
    friend class NetworkScene;
    friend class NetworkObjectsDB;
private:
    void _on_introduce()override;
    void _on_destroy()override;
    void on_network_variable(const Event &e);
    void on_network_translate(const Event &e);
public:
    NetworkObject();
    explicit NetworkObject(const GUID &guid);
    virtual ~NetworkObject() = default;

    void network_translate(const sf::Vector2f &offset);
    void network_translate(float x_offset, float y_offset);


    //anything you want to send into network
    void network_event(const Event &);

    //send an event to imitator objects
    void originator_event(const OriginatorEvent &);
    //handle an event from originator object
    virtual void on_originator_event(const OriginatorEvent &);
    Type type();

    static std::string static_network_class();               
    virtual std::string network_class();

    NetworkObject *set_guid(const GUID &);
    const GUID &guid()const;                                          
};

class NetworkObjectsDB{
private:
    typedef NetworkObject* (*ObjectCreator)(BaseScene*,const GUID &);
    static std::unordered_map<std::string,ObjectCreator> m_objects;

public:
    template <typename T>
    static NetworkObject* _obj_creator(BaseScene *scene, const GUID &guid){
        return (NetworkObject*)(scene->object_introduce(new T(guid)));
    }
    template <typename T>
    static void register_object(){
        m_objects.emplace(T::static_network_class(),&NetworkObjectsDB::_obj_creator<T>);
    }
    static ObjectCreator creator(const std::string &class_name);
};




#endif