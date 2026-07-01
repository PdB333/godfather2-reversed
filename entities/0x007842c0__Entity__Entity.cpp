// FUNC_NAME: Entity::Entity

// Note: param_1 is the 'this' pointer, handled implicitly.
// param_2 is a creation/flag byte passed to the constructor.
// FUN_00783980 is likely the base class constructor (e.g., object or engine base).
// FUN_009c8eb0 is a secondary initializer, called only when the flag has bit 0 set.

Entity* __thiscall Entity::Entity(byte creationFlags) {
    // Call base class constructor (assumed to be Object or EngineBase)
    FUN_00783980();  // Base::Base()

    // If the low bit is set, perform additional initialization
    if ((creationFlags & 1) != 0) {
        FUN_009c8eb0(this);  // likely allocate or init internal data
    }

    return this;
}