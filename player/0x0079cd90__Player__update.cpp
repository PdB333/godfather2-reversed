// FUNC_NAME: Player::update
void __fastcall Player::update(int *thisPtr)
{
    // Call base class virtual update at vtable+0x70 (likely Entity::update)
    (**(void (__thiscall **)(int *))(*thisPtr + 0x70))();

    // Check if we have a current vehicle (pointer at +0x74c)
    int *vehiclePtr = (int *)thisPtr[0x1d3]; // offset 0x74c
    if (vehiclePtr != 0)
    {
        // Adjust to get vehicle base pointer (subtract 0x48, likely to get containing object)
        int *vehicleBase = (int *)(vehiclePtr - 0x48); // offset -0x48 from vehiclePtr
        if (vehicleBase != 0)
        {
            // Check flag at +0x8e0 (bit 10) and isDead flag at +0x161
            if ((((uint)thisPtr[0x238] >> 10) & 1) != 0 && *(char *)((int)thisPtr + 0x161) == '\0')
            {
                // Call vehicle's virtual update at vtable+0x70
                (**(void (__thiscall **)(int *))(*vehicleBase + 0x70))();
            }
        }
    }

    // Check if a state/timer at +0x1ef8 is not -1
    if (thisPtr[0x7be] != -1) // offset 0x1ef8
    {
        // Call cleanup/removal function (e.g., removeFromWorld)
        FUN_00805c00(0);
    }
}