// FUNC_NAME: Entity::Entity(bool allocate)

// Address: 0x005679f0
// Constructor for Entity class. Takes a bool flag; if true, registers the object
// with the memory manager (likely to track allocations in the EARS engine).
void Entity::Entity(bool allocate)
{
    // Call base class constructor or per-instance initialization (0x00567a20)
    // Likely sets up ref count, type info, or other default fields.
    this->initialize();

    if (allocate)
    {
        // Register this object with the engine's memory tracking system (0x009c8eb0)
        // This ensures the object is properly tracked and freed during shutdown.
        this->registerObject();
    }
    // Implicit return of `this` (no explicit return needed in C++ constructors)
}