#include "network/network_object.hpp"
#include "network/objects_protocol.hpp"
#include "network/network_scene.hpp"
#include "engine.hpp"
std::unordered_map<std::string,NetworkObjectsDB::ObjectCreator> NetworkObjectsDB::m_objects;

NetworkObjectsDB::ObjectCreator NetworkObjectsDB::creator(const std::string &class_name){
    ASSERT_ERROR(m_objects.find(class_name)!=m_objects.end(),"NetworkObjectDB: unregistered object: " + class_name);
    return m_objects.find(class_name)->second;
}

NetworkVariableTraits::NetworkVariableTraits(std::size_t s,void* d):
    size(s), variable(d)
{}

void NetworkObject::_on_introduce(){
    if(m_type == Type::Originator){
        static_cast<NetworkScene*>(scene())->object_new(this);
    }
}
void NetworkObject::_on_destroy(){
    static_cast<NetworkScene*>(scene())->object_delete(this);
}

void NetworkObject::on_network_variable(const Event &e){

}
void NetworkObject::on_network_translate(const Event &e){
    set_local_position((*(EventObjectTranslate*)&e).position);
}

NetworkObject::NetworkObject():
    m_guid(),
    m_type(Type::Originator),
    m_delay(0)
{ 
    
}

NetworkObject::NetworkObject(const GUID &guid):
    m_guid(guid),
    m_type(Type::Imitator)
{ 
}


void NetworkObject::network_translate(const sf::Vector2f &offset){
    translate(offset);
    float delay = 0.01f;
    m_delay+=Engine::get_singleton()->delta_time();
    if(m_delay>=delay){
        m_delay-=delay;
        EventObjectTranslate e;
        e.guid=m_guid;
        e.position=local_position();
        static_cast<NetworkScene*>(scene())->send(&e,sizeof(e));
    }
}
void NetworkObject::network_translate(float x_offset, float y_offset){
    network_translate(sf::Vector2f(x_offset,y_offset));
}


void NetworkObject::network_event(const Event &e){
    static_cast<NetworkScene*>(scene())->event(e);
}

void NetworkObject::originator_event(const OriginatorEvent &e){
    EventObjectOriginator event;
    event.type = protocol::DatagramType::Event;
    event.code.event = EventCode(Events::ObjectOriginatorEvent);
    event.guid = m_guid;
    event.content = e;
    static_cast<NetworkScene*>(scene())->send(&event,sizeof(EventObjectOriginator));
}
void NetworkObject::on_originator_event(const OriginatorEvent &e){

}

std::string NetworkObject::static_network_class(){  
    return std::string("NetworkObject");              
}                                           
std::string NetworkObject::network_class(){        
    return std::string("NetworkObject");              
}

NetworkObject::Type NetworkObject::type(){
    return m_type;
}

NetworkObject *NetworkObject::set_guid(const GUID &guid){
    m_guid = guid;
    return this;
}
const GUID &NetworkObject::guid()const{
    return m_guid;
}