// FUNC_NAME: HasSubObjectActive
// Address: 0x0045f3f0
// Role: Checks if a sub-object at +0x218 exists and if a pointer at +0xB4 within that sub-object is non-null.
// Returns true if both are non-zero, false otherwise.

bool HasSubObjectActive() __thiscall
{
    // +0x218: pointer to sub-object (e.g., weapon, ability, or attachment)
    if (*(int*)(this + 0x218) != 0)
    {
        // +0xB4: within the sub-object, likely a pointer or flag indicating active state
        if (*(int*)(*(int*)(this + 0x218) + 0xB4) != 0)
        {
            return true;
        }
    }
    return false;
}