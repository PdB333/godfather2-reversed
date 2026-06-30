// FUNC_NAME: Entity::copyDataFrom
void Entity::copyDataFrom(Entity* source)
{
    // Copy fields from offset 0x10 to 0x2c (7 dwords = 28 bytes)
    *(uint32*)((uint8*)this + 0x10) = *(uint32*)((uint8*)source + 0x10);
    *(uint32*)((uint8*)this + 0x14) = *(uint32*)((uint8*)source + 0x14);
    *(uint32*)((uint8*)this + 0x18) = *(uint32*)((uint8*)source + 0x18);
    *(uint32*)((uint8*)this + 0x1c) = *(uint32*)((uint8*)source + 0x1c);
    *(uint32*)((uint8*)this + 0x20) = *(uint32*)((uint8*)source + 0x20);
    *(uint32*)((uint8*)this + 0x24) = *(uint32*)((uint8*)source + 0x24);
    *(uint32*)((uint8*)this + 0x28) = *(uint32*)((uint8*)source + 0x28);
    *(uint32*)((uint8*)this + 0x2c) = *(uint32*)((uint8*)source + 0x2c);

    // Copy a single byte at offset 0x30
    *(uint8*)((uint8*)this + 0x30) = *(uint8*)((uint8*)source + 0x30);

    // Copy a dword at offset 0x60
    *(uint32*)((uint8*)this + 0x60) = *(uint32*)((uint8*)source + 0x60);

    // Call function on the field at offset 0x64 (probably a pointer to something)
    FUN_00591cb0(*(uint32*)((uint8*)source + 0x64)); // called with value from source
    // Copy destination field at 0x68 from source
    *(uint32*)((uint8*)this + 0x68) = *(uint32*)((uint8*)source + 0x68);
}