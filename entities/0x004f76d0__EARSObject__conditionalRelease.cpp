// FUNC_NAME: EARSObject::conditionalRelease
// Function at 0x004f76d0: Decrements reference count and optionally deletes object based on a condition.
// Parameters:
//   this (unused) - possibly a class instance (not used in this static-like function)
//   arg1 (EDX) - argument passed to virtual function at vtable+8
//   obj (stack) - pointer to object with vtable at offset 0 and refcount at offset 4
// Returns: pointer to a sentinel (local variable) if condition met and object still exists, else null.

void* __fastcall EARSObject::conditionalRelease(void* this, int arg1, int* obj)
{
    int* refCountPtr;
    char conditionResult;
    int sentinel = 0; // local sentinel, returned as non-null pointer

    if (obj != nullptr)
    {
        // Call virtual function at vtable+8 (likely a "canRelease" or "shouldRelease" check)
        conditionResult = (**(code**)(*obj + 8))(arg1);
        if (conditionResult != 0)
        {
            // Condition met: decrement refcount
            refCountPtr = obj + 1; // +0x04: refcount field
            *refCountPtr = *refCountPtr - 1;
            if (*refCountPtr == 0)
            {
                // Refcount reached zero: call destructor at vtable+4
                (**(code**)(*obj + 4))();
            }
            // Return pointer to sentinel (non-null) to indicate success
            return (void*)&sentinel;
        }
        // Condition not met: still decrement refcount and possibly destruct
        refCountPtr = obj + 1;
        *refCountPtr = *refCountPtr - 1;
        if (*refCountPtr == 0)
        {
            (**(code**)(*obj + 4))();
        }
    }
    return nullptr;
}