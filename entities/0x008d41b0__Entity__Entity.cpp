// FUNC_NAME: Entity::Entity
// Address: 0x008d41b0
// Brief: Constructor for Entity class. Calls a global initialization routine (possibly static setup for vtable or memory pool).
//         If the first bit of flags is set, also calls a sub-initializer (e.g., for derived class members) on this pointer.

__thiscall Entity* Entity::Entity(byte flags) {
    // Global base initialization (no 'this' passed, likely static/global setup)
    ::entityBaseInit();
    // Conditional additional initialization (e.g., for a subclass or specific component)
    if (flags & 1) {
        ::entityDerivedInit(this);
    }
    return this;
}