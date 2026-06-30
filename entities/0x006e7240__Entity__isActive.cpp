// FUNC_NAME: Entity::isActive
byte __fastcall Entity::isActive(Entity* this)
{
    // Check initialization flag at +0x8a bit 5 (0x20)
    if ((*(byte*)((uintptr_t)this + 0x8a) & 0x20) == 0)
    {
        // Lazy initialization: call initialization function if not yet done
        // FUN_006e6700 likely Entity::initialize
        FUN_006e6700();
    }
    // Return active flag at +0x89 bit 4 (0x10)
    return (*(byte*)((uintptr_t)this + 0x89) >> 4) & 1;
}