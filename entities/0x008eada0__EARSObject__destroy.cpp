// FUNC_NAME: EARSObject::destroy
int __thiscall EARSObject::destroy(int this, byte deallocateFlag)
{
    // Check if sub-object at offset +0x20 exists and release it
    if (*(int *)(this + 0x20) != 0) {
        // Call sub-object destructor/release function
        FUN_004daf90(this + 0x20);
    }
    // If deallocate flag is set, free the object's memory
    if ((deallocateFlag & 1) != 0) {
        // Operator delete or memory deallocation
        FUN_009c8eb0(this);
    }
    return this;
}