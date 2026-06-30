// FUNC_NAME: Entity::updateState

void __thiscall Entity::updateState()
{
    // Get component pointer at +0x2D4 (int* offset 0xB5)
    int* componentPtr = *(int**)((char*)this + 0x2D4);

    // Check if valid and not a special sentinel value (0x48)
    if (componentPtr != nullptr && componentPtr != (int*)0x48)
    {
        // The component pointer points into a larger structure; get its base by subtracting 0x48
        int* componentBase = (int*)((char*)componentPtr - 0x48);

        // QueryInterface with GUID 0x383225a1
        int* interfacePtr = nullptr;
        char result = ((char (__thiscall*)(int*, int, int**))(*componentBase + 0x10))(
                          componentBase, 0x383225a1, &interfacePtr);

        if (result != 0 && interfacePtr != nullptr)
            goto STATE_UPDATE_BLOCK; // Skip the first cleanup branch
    }

    // Check state byte at +0x39E; if non-negative, do a sub-update and return
    signed char stateFlags = *(signed char*)((char*)this + 0x39E);
    if (stateFlags >= 0)
    {
        // Update sub-object at +0x3C (int* offset 0xF)
        FUN_004088c0((int*)((char*)this + 0x3C));
        return;
    }

STATE_UPDATE_BLOCK:
    // Check bit 6 at +0x39E; if not set, perform state initialization
    byte* flagsByte = (byte*)((char*)this + 0x39E);
    if ((*flagsByte & 0x40) == 0)
    {
        // Set field at +0x310 (int* offset 0xC4) to global value
        *(int*)((char*)this + 0x310) = DAT_00d6144c;

        // Set bit 6 in state flags
        *flagsByte |= 0x40;

        // Conditional virtual call at vtable+0x6c if flag at +0x161 is zero
        if (*(char*)((char*)this + 0x161) == 0)
        {
            (**(void (__thiscall**)(int*))(*((int*)this) + 0x6c))((int*)this);
        }

        // Transition state machine with parameter 9
        FUN_0043c5b0((int*)this, 9);
    }
}