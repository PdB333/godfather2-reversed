// FUNC_NAME: Entity::updateIfActive
void __thiscall Entity::updateIfActive(Entity* this)
{
    // Retrieve the vtable pointer (first member of object)
    char* vtable = *(char**)this;

    // Virtual function at offset 0x178: likely checks if entity is active/can update
    bool (__thiscall* isActive)(Entity*) = (bool (__thiscall*)(Entity*))(*(void**)(vtable + 0x178));
    if (isActive(this))
    {
        // Virtual function at offset 0x1a0: performs the actual update
        void (__thiscall* update)(Entity*) = (void (__thiscall*)(Entity*))(*(void**)(vtable + 0x1a0));
        update(this);
    }
}