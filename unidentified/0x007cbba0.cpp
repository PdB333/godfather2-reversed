// FUN_007cbba0: ResourceHolder::releaseOwnedObject

void __thiscall ResourceHolder::releaseOwnedObject(void)
{
    // Check if owned flag is set at +0x1f0
    if (*(int *)(this + 0x1f0) != 0)
    {
        int local_70 = 0;
        char local_6c[108]; // buffer for string/name processing

        // Call unknown helper (likely resets some internal state)
        FUN_005e30c0();

        // Get owned pointer at +0x1ec, fallback to global empty string if null
        char *ownedPtr = *(char **)(this + 0x1ec);
        if (ownedPtr == (char *)0x0)
        {
            ownedPtr = &DAT_0120546e; // global empty/default string
        }

        // Perform some operation (e.g., format or copy) using the owned pointer and the buffer
        FUN_005e2a50(&local_70, ownedPtr, local_6c);

        // If the owned pointer is non-null, call its virtual destructor via vtable offset +0x1f8
        if (*(int *)(this + 0x1ec) != 0)
        {
            (**(void (__thiscall **)(int))(this + 0x1f8))(*(int *)(this + 0x1ec));
        }

        // Clear fields
        *(int *)(this + 0x1ec) = 0; // owned pointer
        *(int *)(this + 500) = 0;   // +0x1f4: size/count
        *(int *)(this + 0x1f0) = 0; // owned flag
    }
    return;
}