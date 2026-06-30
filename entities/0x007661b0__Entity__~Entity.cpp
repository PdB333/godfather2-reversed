// FUNC_NAME: Entity::~Entity

// Destructor for a base Entity class. Sets vtable to base pointer,
// destroys a sub-object at offset 0x68, calls a global cleanup function,
// and optionally deletes this object if the flag is set (delete operator).
void __thiscall Entity::~Entity(uint8_t isDeleting)
{
    // Set vtable to base class's static pointer (prevents virtual calls during destruction)
    *reinterpret_cast<void**>(this) = &PTR_LAB_00d63090;

    // Check if a sub-object exists at offset 0x68 (0x1a * 4 bytes)
    void** subObject = reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x68);
    if (*subObject != nullptr)
    {
        // Destroy the sub-object (likely a component or resource handle)
        destructSubObject(subObject); // FUN_004daf90
    }

    // Perform global engine-level cleanup (e.g., singleton shutdown)
    globalCleanupFunction(); // FUN_0080ea60

    // If the destructor was called from a delete expression (flag bit 0 set)
    if ((isDeleting & 0x01) != 0)
    {
        // Free the memory of this object
        operatorDelete(this); // FUN_00624da0
    }
}