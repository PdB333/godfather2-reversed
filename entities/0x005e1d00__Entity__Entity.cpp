// FUNC_NAME: Entity::Entity
// Address: 0x005e1d00
// Role: Constructor with allocation/common initialization flag. Calls base initializer, then optionally performs cleanup/deallocation if the low bit of parameter is set.

// Forward declarations of callee functions
void Entity::BaseInitialize(Entity *this); // at 0x005e1d20
void Entity::Deallocate(Entity *this);     // at 0x009c8eb0

Entity * __thiscall Entity::Entity(byte flags) {
    // Call base class/common initializer
    BaseInitialize(this);
    
    // If the allocation flag (bit 0) is set, perform cleanup
    // (likely for heap‑allocated objects or special case handling)
    if (flags & 1) {
        Deallocate(this);
    }
    
    // Return pointer to constructed object
    return this;
}