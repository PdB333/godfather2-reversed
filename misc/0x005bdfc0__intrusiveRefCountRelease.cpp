// FUNC_NAME: intrusiveRefCountRelease
// Function at 0x005bdfc0: Release an intrusive reference-counted object with an optional condition check.
// The object layout: vtable pointer at offset 0, refcount (int32) at offset 4.
// vtable[2] (offset 8) is a condition function: bool __fastcall(void* context) called with param_2 (EDX).
// vtable[1] (offset 4) is the destructor (called when refcount reaches 0).
// Returns non-null if condition allowed release, null otherwise. In both cases refcount is decremented.

typedef char (__fastcall *ConditionFunc)(void* context);
typedef void (__fastcall *DestructorFunc)();

void* __fastcall intrusiveRefCountRelease(
    int unused,                // ECX, ignored
    void* conditionContext,     // EDX, passed to vtable[2]
    int* objectPtr              // pointer to refcounted object (vtable first, then refcount)
)
{
    int* refCountPtr;
    char conditionResult;
    int dummy = 0;

    if (objectPtr != nullptr)
    {
        // Check the condition via vtable[2]
        ConditionFunc checkFunc = *(ConditionFunc*)(*objectPtr + 8);
        conditionResult = checkFunc(conditionContext);
        if (conditionResult != '\0')
        {
            // Condition met: decrement refcount
            refCountPtr = objectPtr + 1;
            (*refCountPtr)--;
            if (*refCountPtr == 0)
            {
                // No more references, call destructor via vtable[1]
                DestructorFunc destructor = *(DestructorFunc*)(*objectPtr + 4);
                destructor();
            }
            // Return pointer to dummy (success indicator)
            return (void*)&dummy;
        }
        // Condition not met: still decrement refcount
        refCountPtr = objectPtr + 1;
        (*refCountPtr)--;
        if (*refCountPtr == 0)
        {
            DestructorFunc destructor = *(DestructorFunc*)(*objectPtr + 4);
            destructor();
        }
    }
    // objectPtr was null or condition failed
    return nullptr;
}