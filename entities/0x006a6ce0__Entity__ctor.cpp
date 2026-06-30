// FUNC_NAME: Entity::ctor
#include <cstdint>

// Constructor for Entity class (base EARSObject)
// param_2 (flags): Bit 0 indicates heap allocation; calls post-construct setup
uint32 __thiscall Entity::ctor(Entity* this, uint8 flags) {
    // Invoke base class constructor
    EARSObject::ctor(this);
    if ((flags & 1) != 0) {
        // Additional initialization for heap-allocated objects
        Entity::postHeapConstruct(this);
    }
    return reinterpret_cast<uint32>(this);
}