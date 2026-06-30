// FUNC_NAME: activateComponent
// Address: 0x004df590
// Role: Sets a flag (0x20000) on a component and clears another flag (0x40000).
// The function takes a pointer to a pointer to a component structure.
// If the component pointer is non-null and the flag 0x20000 is not already set,
// it sets the flag and calls a initialization function (likely for first-time activation).
// Then it clears the flag 0x40000 (which may indicate a pending deactivation).
void __fastcall activateComponent(int* componentPtrPtr)
{
    int* component = reinterpret_cast<int*>(*componentPtrPtr);
    if (component != nullptr) {
        uint flags = *reinterpret_cast<uint*>(reinterpret_cast<char*>(component) + 0xc);
        // +0x0c: flags field
        if ((flags & 0x20000) == 0) {
            *reinterpret_cast<uint*>(reinterpret_cast<char*>(component) + 0xc) = flags | 0x20000;
            FUN_0051b120(); // Likely first-time initialization for the component
        }
        // Clear flag 0x40000 (bit 18)
        *reinterpret_cast<uint*>(reinterpret_cast<char*>(component) + 0xc) &= 0xfffbffff;
    }
}