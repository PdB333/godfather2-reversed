// FUNC_NAME: Entity::constructor

// Address: 0x006f4820
// This function is a constructor for a class derived from BaseClass.
// The 'flags' parameter controls optional additional initialization (bit 0).

/**
 * @brief Constructs an Entity (or derived) object.
 * @param this Pointer to uninitialized memory for the object.
 * @param flags Bit 0 set -> perform extra setup (e.g., allocate owned resources).
 * @return Pointer to constructed object (same as this).
 */
void* __thiscall Entity::constructor(Entity* this, byte flags) {
    // Base class constructor (FUN_006f4710)
    BaseClass::constructor(this);

    // If bit 0 is set, run additional initialization
    if (flags & 1) {
        // Assign or allocate internally owned storage (FUN_009c8eb0)
        this->initOwnedMemory();
    }

    return this;
}