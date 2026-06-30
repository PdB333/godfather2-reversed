// FUNC_NAME: SomeManager::~SomeManager
void __thiscall SomeManager::~SomeManager(void)
{
    int iVar1;
    uint uVar2;

    // Set vtable pointers (likely to base class vtables or custom RTTI)
    this->vtable0 = &PTR_LAB_00d5ebb0;   // +0x00
    this->vtable1 = &PTR_LAB_00d5eb9c;   // +0x04

    // If state is not 0 or 1 (meaning initialized?), free a sub-object
    if (this->state != 0 && this->state != 1) {   // +0x40
        FUN_0093ea60(*(undefined4 *)(this->somePointer + 0x38)); // +0x10, +0x38
    }

    // Check bit 1 of flags at +0x34; if set and global conditions hold, reset something at +0x04
    if (((this->flags >> 1 & 1) != 0) &&             // +0x34
        (**(int **)(DAT_012233a0 + 4) != 0) &&
        (**(int **)(DAT_012233a0 + 4) != 0x1f30) &&
        (iVar1 = FUN_0043b870(DAT_01131018), iVar1 != 0))
    {
        FUN_009af0a0(this + 1);   // operates on vtable1 at +0x04
    }

    // Release all items in first array (count at +0x20)
    uVar2 = 0;
    if (this->firstCount != 0) {   // +0x20
        do {
            FUN_00791350(this);
            uVar2 = uVar2 + 1;
        } while (uVar2 < (uint)this->firstCount);
    }

    // Release all items in second array (count at +0x2c)
    uVar2 = 0;
    if (this->secondCount != 0) {   // +0x2c
        do {
            FUN_00791350(this);
            uVar2 = uVar2 + 1;
        } while (uVar2 < (uint)this->secondCount);
    }

    // Global singleton cleanup
    FUN_006b5790();

    // Free allocated buffers
    if (this->ptr1 != 0) {   // +0x28
        FUN_009c8f10(this->ptr1);
    }
    if (this->ptr2 != 0) {   // +0x1c
        FUN_009c8f10(this->ptr2);
    }

    return;
}