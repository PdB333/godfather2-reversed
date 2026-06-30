// FUNC_NAME: Entity::Entity
// Address: 0x006bdbe0
// Role: Constructor for basic game entity with optional memory allocation

Entity* __thiscall Entity::Entity(byte allocFlag)
{
    // Call base class constructor (likely EARSObject or similar)
    EARSObject::EARSObject();

    // If bit 0 of allocFlag is set, allocate memory for the entity (size 0xE0 = 224 bytes)
    if (allocFlag & 1) {
        this->allocateMemory(0xE0);  // Custom allocation function
    }

    return this;
}