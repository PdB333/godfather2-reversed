// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(Entity* this, byte createFlags)
{
    // Call base class constructor (likely SimObject or similar)
    FUN_004fa0b0();
    // If bit 0 is set, perform additional initialization (e.g., allocate resources, register for updates)
    if ((createFlags & 1) != 0) {
        FUN_009c8eb0(this);
    }
    // Return this pointer for chaining
    return this;
}