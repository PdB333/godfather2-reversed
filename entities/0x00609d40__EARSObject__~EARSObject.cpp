// FUNC_NAME: EARSObject::~EARSObject
int __thiscall EARSObject::~EARSObject(int this, byte param_2)
{
    // Free the resource pointed to by member at offset +0x8
    if (*(int *)(this + 0x8) != 0) {
        FUN_009c8f10(*(int *)(this + 0x8));
    }
    // If the flag (bit 0) is set, deallocate the object itself
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return this;
}