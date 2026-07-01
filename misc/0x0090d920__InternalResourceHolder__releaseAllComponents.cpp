// FUNC_NAME: InternalResourceHolder::releaseAllComponents
void __fastcall InternalResourceHolder::releaseAllComponents()
{
    // The object stores two deleter function pointers at +0x4c and +0x38.
    // +0x38 points to an int (used as a fallback deleter argument), +0x4c is a primary deleter function.
    int* fallbackArg = reinterpret_cast<int*>((int)this + 0x38);
    int* primaryDeleter = reinterpret_cast<int*>((int)this + 0x4c);

    // If either deleter is non-null, invoke the appropriate one.
    if (*primaryDeleter != 0 || *fallbackArg != 0) {
        if (*primaryDeleter == 0) {
            // No primary: call fallback with constant 3 (likely a destroy/cleanup command)
            reinterpret_cast<void (*)(int)>(*fallbackArg)(3);
        } else {
            // Primary exists: call it with the fallback argument pointer as parameter
            reinterpret_cast<void (*)(int*)>(*primaryDeleter)(fallbackArg);
        }
    }

    // Destroy sub-object at +0x30 (simple free/delete via external function)
    if (*(int*)((int)this + 0x30) != 0) {
        FUN_004daf90((int)this + 0x30);
    }

    // Destroy sub-object at +0x20 using its stored destructor at +0x2c
    if (*(int*)((int)this + 0x20) != 0) {
        void (*destructor)(int) = *reinterpret_cast<void (**)(int)>((int)this + 0x2c);
        destructor(*(int*)((int)this + 0x20));
    }

    // Destroy sub-object at +0x10 using its stored destructor at +0x1c
    if (*(int*)((int)this + 0x10) != 0) {
        void (*destructor)(int) = *reinterpret_cast<void (**)(int)>((int)this + 0x1c);
        destructor(*(int*)((int)this + 0x10));
    }
}