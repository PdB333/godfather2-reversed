// FUNC_NAME: SomeClass::SomeClass(const SomeClass&)
// Address: 0x006a46f0
// Role: Copy constructor for a simple data container (size 46 bytes). Copies 11 dwords (0-8,10) and two bytes at offsets 44-45, but overrides the vtable pointer (dword at offset 0x24, index 9) with a fixed global pointer.

void __thiscall SomeClass::SomeClass(SomeClass* this, const SomeClass* other)
{
    // Copy first 9 dwords (offsets 0x00 to 0x20)
    *(int*)((int)this + 0x00) = *(int*)((int)other + 0x00); // field0
    *(int*)((int)this + 0x04) = *(int*)((int)other + 0x04); // field1
    *(int*)((int)this + 0x08) = *(int*)((int)other + 0x08); // field2
    *(int*)((int)this + 0x0C) = *(int*)((int)other + 0x0C); // field3
    *(int*)((int)this + 0x10) = *(int*)((int)other + 0x10); // field4
    *(int*)((int)this + 0x14) = *(int*)((int)other + 0x14); // field5
    *(int*)((int)this + 0x18) = *(int*)((int)other + 0x18); // field6
    *(int*)((int)this + 0x1C) = *(int*)((int)other + 0x1C); // field7
    *(int*)((int)this + 0x20) = *(int*)((int)other + 0x20); // field8

    // Set vtable pointer at offset 0x24 (index 9) to own class vtable
    *(void**)((int)this + 0x24) = &PTR_LAB_00d5d708;

    // Copy dword at offset 0x28 (index 10)
    *(int*)((int)this + 0x28) = *(int*)((int)other + 0x28); // field10

    // Copy two bytes at offsets 0x2C and 0x2D (padding or small fields)
    *(char*)((int)this + 0x2C) = *(char*)((int)other + 0x2C);
    *(char*)((int)this + 0x2D) = *(char*)((int)other + 0x2D);
}