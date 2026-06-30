// FUNC_NAME: SimNpc::SimNpc
// Function address: 0x004c8270
// Role: Constructor for SimNpc class. Sets vtable pointer, calls base Entity constructor, and optionally registers the object if heap-allocated (param_2 & 1).

#include <cstdint>

// Forward declarations of known functions
void __thiscall Entity::Entity(void *this, uint8_t allocated);
void __thiscall SimNpc::registerSimNpc(void *this);  // Registers object with manager if heap-allocated

class SimNpc {
public:
    void *vtable;  // +0x00
    // ... other members ...
};

void * __thiscall SimNpc::SimNpc(void *this, uint8_t allocated) {
    // Set vtable pointer for SimNpc
    *(void **)this = (void *)0x00e365e0;  // SimNpc vtable (PTR_FUN_00e365e0)

    // Call base class constructor (Entity)
    Entity::Entity(this, allocated);

    // If the object was heap-allocated (allocated bit 0 set), register it
    if ((allocated & 1) != 0) {
        SimNpc::registerSimNpc(this);  // FUN_009c8eb0
    }

    return this;
}