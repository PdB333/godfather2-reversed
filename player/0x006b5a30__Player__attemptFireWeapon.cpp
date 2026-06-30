// FUNC_NAME: Player::attemptFireWeapon
// Function address: 0x006b5a30
// Role: Checks if the player can fire their weapon and initiates firing if conditions are met.
// Returns 1 if firing was initiated, 0 otherwise.

int __thiscall Player::attemptFireWeapon(Player* this)
{
    int state; // from +0x16c
    int weaponStatus; // from weapon object

    state = *(int*)((uint)this + 0x16c); // +0x16c: current state (e.g., 2=aiming, 3=firing, 4=reloading)

    // Check flags at +0x34: bits 0x120000 (0x120000 = 0x12 << 16? Actually 0x120000 = 0x12 << 16, but likely two separate bits: 0x20000 and 0x100000? Wait 0x120000 = 0x12 * 0x10000 = 0x12 << 16, but bits 17 and 20? Better to treat as mask)
    // Also check lowest bit (bit 0) is clear.
    if (((*(uint*)((uint)this + 0x34) & 0x120000) == 0) && ((*(byte*)((uint)this + 0x34) & 1) == 0))
    {
        // Check if weapon pointer at +0x40 is non-null
        if (*(int*)((uint)this + 0x40) != 0)
        {
            // Get weapon status from weapon object
            weaponStatus = FUN_008c74d0(*(int*)((uint)this + 0x40)); // likely getWeaponStatus or getWeaponData
            if ((weaponStatus != 0) && ((~(byte)(*(uint*)(weaponStatus + 0x84) >> 5) & 1) != 0)) // check bit 5 of +0x84 (e.g., isLoaded)
            {
                // State must be 2, 3, or 4 (aiming, firing, reloading)
                if ((state == 2) || (state == 3) || (state == 4))
                {
                    FUN_006b4e30(0, 0); // playFireSound or startFiring
                    return 1;
                }
            }
        }
    }
    return 0;
}