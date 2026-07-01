// FUNC_NAME: Entity::Entity
// Address: 0x008290d0
// Role: Constructor for Entity object. Takes a flags byte; if bit 0 is set, performs additional initialization (e.g., register with manager, allocate resources).

unsigned int __thiscall Entity::Entity(unsigned int this, unsigned char initFlags)
{
    // Call base class constructor (mostly likely Object or SimObject)
    Object::Object(); // FUN_00828d60

    if (initFlags & 0x01)
    {
        // Additional setup – possibly on‑create hook or resource allocation
        Entity::postInit(this); // FUN_009c8eb0
    }

    return this;
}