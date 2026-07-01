// FUNC_NAME: Entity::registerFields
// Function address: 0x00988490
// Role: Registers object fields for reflection/serialization, binding global field identifiers to member offsets
void __fastcall Entity::registerFields(Entity* this)
{
    // Base class initialization (likely registers its own fields)
    BaseClass::init();

    // Register int field at +0x54 with identifier DAT_00d873d4, size=1, no callback, flags=0
    FieldSystem::registerField(&DAT_00d873d4, (void*)((uintptr_t)this + 0x54), 1, nullptr, 0, 0);
    // Register int field at +0x58 with identifier DAT_00d873cc, size=1, no callback, flags=1
    FieldSystem::registerField(&DAT_00d873cc, (void*)((uintptr_t)this + 0x58), 1, nullptr, 0, 1);
    // Register int field at +0x5c with identifier DAT_00d91354, size=1, no callback, flags=0
    FieldSystem::registerField(&DAT_00d91354, (void*)((uintptr_t)this + 0x5c), 1, nullptr, 0, 0);
    // Register field at +0x68 with callback function at 0x00988410, size=1, flags=0
    FieldSystem::registerField(&DAT_00d873bc, (void*)((uintptr_t)this + 0x68), 1, (void*)0x988410, 0, 0);
    // Register 3-component field at +0xe4 (e.g., Vector3) with identifier DAT_00d9134c, flags=1
    FieldSystem::registerField(&DAT_00d9134c, (void*)((uintptr_t)this + 0xe4), 3, nullptr, 0, 1);
    // Register 3-component field at +0x108 with identifier DAT_00d91344, flags=1
    FieldSystem::registerField(&DAT_00d91344, (void*)((uintptr_t)this + 0x108), 3, nullptr, 0, 1);
}