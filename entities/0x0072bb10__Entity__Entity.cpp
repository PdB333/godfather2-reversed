// FUNC_NAME: Entity::Entity
// Address: 0x0072bb10
// Role: Constructor for Entity class with optional buffer allocation

Entity* __thiscall Entity::Entity(byte flags)
{
    // Call base class constructor (likely for EARS::Framework::Object)
    baseConstructor(); // FUN_0072b0b0

    // If bit 0 is set, allocate an internal buffer of a fixed size (10000)
    if (flags & 1)
    {
        initBuffer(10000); // FUN_0043b960 - initialize/reserve buffer
    }

    return this;
}