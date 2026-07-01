// FUNC_NAME: FlaggedDeletionObject::~FlaggedDeletionObject
void __thiscall FlaggedDeletionObject::~FlaggedDeletionObject(byte deleteFlag)
{
    // Call base class destructor (FUN_00901720)
    this->baseDestructor();
    // If the object was heap-allocated (flag bit 0 set), free memory with known size 0x98 (152 bytes)
    if (deleteFlag & 1)
    {
        freeObjectMemory(this, 0x98);
    }
    // Note: Ghidra shows return this, likely an artifact; actual signature is void
}