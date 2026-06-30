// FUNC_NAME: EARS::Entity::Entity

// Global entity count or active instance flag
int g_entityCount = 0;

// Constructor for base Entity class (0x006d5d50)
void* __thiscall Entity::Entity(void* this, bool constructorFlag)
{
    // Set up vtable pointers for multiple base classes (virtual inheritance / COM-style interfaces)
    *(void**)this = &PTR_FUN_00d5f3f0;             // primary vtable at +0x00
    *(void**)((char*)this + 0x3C) = &PTR_LAB_00d5f3e0;   // base class vtable 1 at +0x3C
    *(void**)((char*)this + 0x48) = &PTR_LAB_00d5f3dc;   // base class vtable 2 at +0x48
    *(void**)((char*)this + 0x50) = &PTR_LAB_00d5f3d8;   // base class vtable 3 at +0x50
    *(void**)((char*)this + 0x58) = &PTR_LAB_00d5f3d0;   // base class vtable 4 at +0x58 (overwrites previous assignment)

    // Reset global state
    g_entityCount = 0;

    // Call base class constructor or initialization routine
    baseClassConstructor();

    // If the object was externally allocated, perform final registration / initialisation
    if (constructorFlag & 1)
    {
        // Internal function: size 0x230 = total entity object size
        registerEntity(this, 0x230);
    }

    return this;
}