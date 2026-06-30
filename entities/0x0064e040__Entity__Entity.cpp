// FUNC_NAME: Entity::Entity
// Function address: 0x0064e040
// Role: Constructor for Entity class. Calls base constructor (likely EARSObject base) and optional initialization based on flag.

int __thiscall Entity::Entity(Entity *this, byte flags)
{
    // Call base class constructor (EARSObject or similar)
    FUN_0064e060(this);

    // If flag bit 0 is set, perform additional initialization
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this);
    }

    return this;
}