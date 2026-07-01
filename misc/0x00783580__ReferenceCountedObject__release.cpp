// FUNC_NAME: ReferenceCountedObject::release
// Address: 0x00783580
// This function is part of the reference-counting/cleanup system.
// It decrements the reference count, then performs deferred cleanup if the
// object was marked for release. The second parameter (likely in EDX) appears
// to be an "owner" or "context" pointer used for notification.

void __fastcall ReferenceCountedObject::release(int this, void* param2)
{
    // Call virtual function at vtable+0: likely Release() or DecRef() with argument 1.
    // The vtable pointer is stored at offset 0x0C.
    (*(code**) **(void***)(this + 0x0C))(1);

    // Check if the "deferred cleanup" flag (bit 0) is set.
    // This flag might indicate that the object has been scheduled for release
    // but hasn't been fully cleaned up yet.
    if ((*(byte*)(this + 100) & 1) != 0)
    {
        // Clear the flag
        *(uint*)(this + 100) &= 0xFFFFFFFE;

        // Call a global cleanup function (likely Manager::removeObject or similar)
        FUN_004086d0(&DAT_0112ad84);

        // Check if there is a "parent" or "container" pointer stored at this-4.
        // This negative offset suggests the object is part of an intrusive list
        // where the list node is located before the object's data.
        if ((*(int*)(this - 4) != 0) &&
            (FUN_0043b870(DAT_01131018) != 0)) // Check if global manager exists
        {
            // Call finalization function (e.g., unlink from containers)
            FUN_009af0a0(this);
        }
    }

    // Check if the "need notification" flag (bit 1) is set.
    // If set, and param2 points to a valid object (not null and not a special
    // sentinel value 0x48), then send a notification to that object.
    if (((*(uint*)(this + 100) >> 1) & 1) != 0 &&
        (*(int*)(param2 + 0x0C) != 0) &&
        (*(int*)(param2 + 0x0C) != 0x48))
    {
        // Compute the base of the receiving object by subtracting 0x48 from the
        // pointer stored at param2+0x0C. This is likely a member offset to
        // get the owning object from a nested structure.
        int* base = *(int*)(param2 + 0x0C);
        if (base != 0)
        {
            base = (int*)(base - 0x48);
        }
        // Call virtual function at vtable+0x10 (offset 16) with message ID 0x55859EFA
        // and a stack variable (likely ignored or used for return).
        (**(code**)(*base + 0x10))(0x55859EFA, &stack0x00000000);
    }

    return;
}