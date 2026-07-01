// FUNC_NAME: ObjectA::~ObjectA
int* __thiscall ObjectA::~ObjectA(ObjectA* this, byte deleteFlags)
{
    // +0x3C: pointer to a dynamically allocated member
    if (this->field_0x3C != 0) {
        freeMem(this->field_0x3C);
    }
    // Global static cleanup for objects of this type
    globalStaticCleanup();
    // +0x14: another allocated pointer
    freeMem(this->field_0x14);
    // +0x00: pointer to a sub‑allocation block
    int* subBlock = this->field_0x00;
    if (subBlock != 0) {
        // +0x30 within that sub‑allocation
        freeMem(*(int*)(subBlock + 0x30 / 4));
        freeMemArray(subBlock);
    }
    // If the caller wants us to delete the object itself
    if ((deleteFlags & 1) != 0) {
        freeMemArray(this);
    }
    return this;
}