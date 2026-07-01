// FUNC_NAME: Entity::Entity
// Address: 0x00797b10
// Role: Constructor for an entity-type object. Sets the virtual type ID to 0xF and zeroes all member fields.

void __thiscall Entity::ctor(void *this)
{
    // Call virtual function at vtable+4 with argument 0xF (likely setTypeID or similar)
    (*(void (__thiscall **)(void *, int))(*(int *)this + 4))(this, 0xF);

    // Zero out fields from offset +0x0C (index 3) to +0x70 (index 0x1C)
    // Offsets are in 4-byte increments from the 'this' pointer
    *(int *)((int)this + 0x0C) = 0;  // +0x0C (field 3)
    *(int *)((int)this + 0x10) = 0;  // +0x10 (field 4)
    *(int *)((int)this + 0x34) = 0;  // +0x34 (field 0xD)
    *(int *)((int)this + 0x14) = 0;  // +0x14 (field 5)
    *(int *)((int)this + 0x54) = 0;  // +0x54 (field 0x15)
    *(int *)((int)this + 0x38) = 0;  // +0x38 (field 0xE)
    *(int *)((int)this + 0x18) = 0;  // +0x18 (field 6)
    *(int *)((int)this + 0x58) = 0;  // +0x58 (field 0x16)
    *(int *)((int)this + 0x3C) = 0;  // +0x3C (field 0xF)
    *(int *)((int)this + 0x1C) = 0;  // +0x1C (field 7)
    *(int *)((int)this + 0x5C) = 0;  // +0x5C (field 0x17)
    *(int *)((int)this + 0x40) = 0;  // +0x40 (field 0x10)
    *(int *)((int)this + 0x20) = 0;  // +0x20 (field 8)
    *(int *)((int)this + 0x60) = 0;  // +0x60 (field 0x18)
    *(int *)((int)this + 0x44) = 0;  // +0x44 (field 0x11)
    *(int *)((int)this + 0x24) = 0;  // +0x24 (field 9)
    *(int *)((int)this + 0x64) = 0;  // +0x64 (field 0x19)
    *(int *)((int)this + 0x48) = 0;  // +0x48 (field 0x12)
    *(int *)((int)this + 0x28) = 0;  // +0x28 (field 10)
    *(int *)((int)this + 0x68) = 0;  // +0x68 (field 0x1A)
    *(int *)((int)this + 0x4C) = 0;  // +0x4C (field 0x13)
    *(int *)((int)this + 0x2C) = 0;  // +0x2C (field 0xB)
    *(int *)((int)this + 0x6C) = 0;  // +0x6C (field 0x1B)
    *(int *)((int)this + 0x50) = 0;  // +0x50 (field 0x14)
    *(int *)((int)this + 0x30) = 0;  // +0x30 (field 0xC)
    *(int *)((int)this + 0x70) = 0;  // +0x70 (field 0x1C)
}