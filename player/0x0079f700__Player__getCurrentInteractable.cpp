// FUNC_NAME: Player::getCurrentInteractable
// Address: 0x0079f700
// Role: Returns a pointer to the current interactable object (e.g., vehicle, weapon, or multiplayer target) by checking multiple component slots.
// Offsets: +0x2528 = m_pVehicleComponent, +0x1c78 = m_pWeaponComponent, +0x24fc = m_pMultiplayerTargetComponent
// The stored pointers point to a sub-object at offset +0x48 within the actual interactable object, so we subtract 0x48 to get the base.

void* __thiscall Player::getCurrentInteractable(void* thisPtr)
{
    char isMultiplayer;
    void* result;

    // Check vehicle component slot
    if (*(int*)((int)thisPtr + 0x2528) != 0)
    {
        result = (void*)(*(int*)((int)thisPtr + 0x2528) - 0x48);
        if (result != 0)
            return result;
    }

    // Check weapon component slot
    if (*(int*)((int)thisPtr + 0x1c78) != 0)
    {
        result = (void*)(*(int*)((int)thisPtr + 0x1c78) - 0x48);
        if (result != 0)
            return result;
    }

    // Global multiplayer check (e.g., isMultiplayerMode())
    isMultiplayer = FUN_007f7c50();
    if (isMultiplayer != 0)
    {
        if (*(int*)((int)thisPtr + 0x24fc) != 0)
        {
            return (void*)(*(int*)((int)thisPtr + 0x24fc) - 0x48);
        }
        return 0;
    }

    return result; // result is 0 from earlier fallthrough
}