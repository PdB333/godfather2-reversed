// FUNC_NAME: UnknownClass::scalarDeletingDestructor
// Address: 0x00937de0
// Description: Scalar deleting destructor (MSVC pattern). Calls the destructor (0x009377a0) 
// then optionally operator delete (0x005c4480) if the low bit of flags is set.

int __thiscall UnknownClass::scalarDeletingDestructor(void* thisPtr, byte flags) {
    // Call the base destructor (implicit this passed via ecx)
    this->~UnknownClass();                  // Actually calls FUN_009377a0
    if (flags & 1) {
        // Call operator delete
        operator delete(thisPtr);           // Actually calls FUN_005c4480
    }
    return (int)thisPtr;                    // Return unchanged 'this'
}