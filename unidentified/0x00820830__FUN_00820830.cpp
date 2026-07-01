// FUNC_NAME: SomeClass::copyFrom
void __thiscall SomeClass::copyFrom(SomeClass* this, SomeClass* other)
{
    // Check for self-assignment
    if (this == other) {
        return;
    }

    // +0x00: vtable pointer (not copied)
    // +0x04: pointer to shared data or sub-object
    // If the pointers differ, copy the first block (offsets +0x04 to +0x18)
    if (*(void**)(this + 4) != *(void**)(other + 4)) {
        *(int*)(this + 4) = *(int*)(other + 4);
        *(int*)(this + 8) = *(int*)(other + 8);
        *(int*)(this + 0x0C) = *(int*)(other + 0x0C);
        *(int*)(this + 0x10) = *(int*)(other + 0x10);
        *(int*)(this + 0x14) = *(int*)(other + 0x14);
        *(int*)(this + 0x18) = *(int*)(other + 0x18);
    }

    // Always copy the second block (offsets +0x1C to +0x48)
    *(int*)(this + 0x1C) = *(int*)(other + 0x1C);
    *(int*)(this + 0x20) = *(int*)(other + 0x20);
    *(int*)(this + 0x24) = *(int*)(other + 0x24);
    *(int*)(this + 0x28) = *(int*)(other + 0x28);
    *(int*)(this + 0x2C) = *(int*)(other + 0x2C);
    *(int*)(this + 0x30) = *(int*)(other + 0x30);
    *(int*)(this + 0x34) = *(int*)(other + 0x34);
    *(int*)(this + 0x38) = *(int*)(other + 0x38);
    *(int*)(this + 0x3C) = *(int*)(other + 0x3C);
    *(int*)(this + 0x40) = *(int*)(other + 0x40);
    *(int*)(this + 0x44) = *(int*)(other + 0x44);
    *(int*)(this + 0x48) = *(int*)(other + 0x48);
}