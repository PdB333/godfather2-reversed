// FUNC_NAME: Entity::Entity

#include <cstdint>

// External symbols for vtable pointers
extern void* PTR_FUN_00d744c4;
extern void* PTR_LAB_00d744b4;
extern void* PTR_LAB_00d744b0;

// Base class initializer (address 0x0046c590)
void __cdecl BaseEntityInit(uint32_t param);

// Constructor at address 0x0083fb90
Entity* __thiscall Entity::Entity(Entity* this, uint32_t entityData) {
    // Call base class constructor / initialization with entity data
    BaseEntityInit(entityData);

    // Set primary vtable pointer at offset 0x00
    this->vfptr = &PTR_FUN_00d744c4;

    // Set secondary vtable pointer at offset 0x3C (0x0F * 4)
    *(void**)((uint8_t*)this + 0x3C) = &PTR_LAB_00d744b4;

    // Set tertiary vtable pointer at offset 0x48 (0x12 * 4)
    *(void**)((uint8_t*)this + 0x48) = &PTR_LAB_00d744b0;

    return this;
}