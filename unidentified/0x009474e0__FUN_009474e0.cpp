// FUNC_NAME: UnknownClass::scalarDeletingDestructor

// Function at 0x009474e0: Scalar deleting destructor for an object of size 0x160.
// param_2: deletion flag (bit0 set means call operator delete after destructor)
void* __thiscall scalarDeletingDestructor(void* this, byte flag) {
    // Call actual destructor (likely virtual dispatch or base destructor)
    FUN_009470d0();

    // If deletion flag is set, free memory with operator delete
    if ((flag & 1) != 0) {
        operator delete(this, 0x160); // 0x160 = size of object
    }

    return this;
}