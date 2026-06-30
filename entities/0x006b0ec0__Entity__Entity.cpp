// FUNC_NAME: Entity::Entity
#include <cstdint>

class Object
{
public:
    void * operator new(size_t size);
    Object();
    // ...
};

class Entity : public Object
{
public:
    void * operator new(size_t size);
    Entity(uint8_t param_2);
    // ...
    void postConstructor(); // called when param_2 & 1 is set
};

Entity::Entity(uint8_t param_2)
{
    // Call base class constructor (Object::Object at 0x006b0580)
    Object::Object();

    // If the low bit is set, perform additional initialization
    if ((param_2 & 1) != 0) {
        // This likely finishes or customizes construction (0x009c8eb0)
        postConstructor();
    }
}