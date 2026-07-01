// FUNC_NAME: Entity::Entity

// Constructor for Entity class.
// Address: 0x00831a40
// Sets up vtable pointers for base class and an interface, then optionally allocates from a memory pool.

Entity * __thiscall Entity::Entity(byte constructFlags)
{
    // Set main vtable pointer (primary class)
    this->vtable = (void *)&PTR_FUN_00d7388c; // +0x00

    // Call base Object constructor
    BaseObject::BaseObject(this); // FUN_0082ba50

    // Set secondary vtable pointer (likely for an interface like INetObject)
    this->vtable2 = (void *)&PTR_LAB_00e32854; // +0x30

    // Call interface or secondary base constructor
    InterfaceClass::InterfaceClass(this); // FUN_00821f60

    // If constructFlags bit 0 is set, allocate from the object's memory pool
    if ((constructFlags & 1) != 0) {
        // Get the memory pool allocator for this class
        MemoryPool *pool = (MemoryPool *)MemoryManager::getAllocator(); // FUN_009c8f80
        // Allocate and construct at this address with size 0xA0 (160 bytes)
        pool->construct(this, 0xA0);
    }

    return this;
}