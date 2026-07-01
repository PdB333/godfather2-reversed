// FUNC_NAME: ObjectRef::Attach
void __thiscall ObjectRef::Attach(undefined4 *this, int *target, int existingHandle)
{
    // Store target pointer at offset 0
    *this = target;
    // Call virtual method at vtable offset +8 (likely Initialize or AddRef)
    (*(code **)(*target + 8))();

    if (existingHandle != 0)
    {
        // Create a handle from the target object using FUN_004265d0
        // (likely a wrapper/refcount acquisition function)
        this[1] = FUN_004265d0(existingHandle, *this);
        return;
    }
    // No handle provided, set handle field to null
    this[1] = 0;
    return;
}