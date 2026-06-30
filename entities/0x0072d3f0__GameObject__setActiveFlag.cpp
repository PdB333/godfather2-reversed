// FUNC_NAME: GameObject::setActiveFlag
void __thiscall GameObject::setActiveFlag(int* thisPtr, char active)
{
    // Call virtual function at vtable+0x2fc that returns a pointer to a component/child object
    // param: thisPtr + 0x3ac (since int* offset 0xeb = 0xeb*4 = 0x3ac)
    int* component = (**(code (__thiscall**)(int*))(*(int*)thisPtr + 0x2fc))(thisPtr + 0xeb);

    if (component != 0) {
        // Set or clear bit 0 of the component's flags at offset 0x58
        if (active == '\0') {
            *(uint*)(component + 0x58) &= 0xfffffffe;  // Clear bit 0
        } else {
            *(uint*)(component + 0x58) |= 1;            // Set bit 0
        }
        // Allocate/debug output with size 0x100
        someAllocFunc(0x100);
    }

    // Debug log using return address (caller identification)
    debugLog(unaff_retaddr + 0x20);

    // Set bit 2 of thisPtr's flags at offset 0x894 (thisPtr[0x225])
    thisPtr[0x225] |= 4;  // Mark dirty/state changed
}