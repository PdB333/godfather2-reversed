// FUN_004e89e0: ReleaseRefCount (in EA EARS engine reference counted object helper)
// This function decrements the reference count of an object and deletes it if the count reaches zero.
// It is a static helper used by smart pointer implementations.
// Parameters:
//   object: pointer to the object with a vtable (at +0x00)
//   refCountBlock: pointer to a struct { void* object; int refCount; } (+0x00 object ptr, +0x04 ref count)
// The function is called with __fastcall: object in ECX, refCountBlock in EDX (param_1 unused).

void* __fastcall ReleaseRefCount(void* param_1, void* object, int* refCountBlock)
{
    // param_1 is unused; it might be the smart pointer's 'this' in some contexts.
    int result = 0; // placeholder for successful release (returned as address of this zero)

    if (refCountBlock != nullptr)
    {
        // Call virtual function at vtable offset 8 (likely isAlive/IsReferenced or similar)
        // This function takes the object pointer as argument.
        char isReferenced = (*(char (__thiscall**)(void*))(*(int*)object + 8))(object);
        if (isReferenced != 0)
        {
            // Decrement the reference count stored at refCountBlock[1] (offset +0x04)
            int* countPtr = refCountBlock + 1;
            (*countPtr)--;
            if (*countPtr == 0)
            {
                // If count reached zero, call virtual destructor at vtable offset 4
                (*(void (__thiscall**)(void*))(*(int*)object + 4))(object);
            }
            // Return a non-null pointer (address of local zero) to indicate success
            return (void*)&result;
        }
        // If object is not alive, still decrement count and potentially delete
        int* countPtr = refCountBlock + 1;
        (*countPtr)--;
        if (*countPtr == 0)
        {
            (*(void (__thiscall**)(void*))(*(int*)object + 4))(object);
        }
    }
    // Return null if refCountBlock was null or failed
    return nullptr;
}