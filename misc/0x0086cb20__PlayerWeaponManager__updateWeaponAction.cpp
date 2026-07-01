// FUNC_NAME: PlayerWeaponManager::updateWeaponAction
// Function at 0x0086cb20 - Updates weapon visibility/holster state based on player state and weapon flags.
// Accesses fields at offsets: +0x50 (m_pWeapon), +0xC4 (m_weaponState), +0xC8 (m_weaponFlags byte).
// Also reads weapon object at m_pWeapon - 0x48 (base class adjustment for multiple inheritance) and checks bit at +0xC88.

void __thiscall PlayerWeaponManager::updateWeaponAction(CPlayerWeaponManager* this) // parameter: this as int in fastcall? Actually __thiscall
{
    int iVar1;
    int weaponPtr;

    // Get weapon pointer from this
    weaponPtr = *(int*)((byte*)this + 0x50);
    
    // If weapon pointer is valid and not a dummy value (0x48 sentinel)
    if ((weaponPtr != 0) && (weaponPtr != 0x48)) 
    {
        if (*(int*)((byte*)this + 0xC4) == 2) // weapon state == HOLSTERED (likely enum value 2)
        {
            // Check if aiming flag (bit 6 of weapon flags) is not set
            if ((*(byte*)((byte*)this + 0xC8) >> 6 & 1) == 0) 
            {
                // Compute base pointer for weapon data (adjustment for derived class offset)
                if (weaponPtr == 0) 
                {
                    iVar1 = 0;
                } 
                else 
                {
                    iVar1 = weaponPtr - 0x48; // Retrieve weapon base object from derived class
                }
                
                // Check weapon's internal holster/equip flag (bit 21 at offset 0xC88)
                if ((*(uint*)(iVar1 + 0xC88) >> 0x15 & 1) != 0) 
                {
                    // Notify weapon that it should become visible/active (parameter 1 = true)
                    setWeaponHolstered(true); // FUN_0087bd50(1)
                }
                
                // Force weapon mesh update (always happens in this branch)
                updateWeaponMesh(true); // FUN_0087d560(1)
                return;
            }
            // If aiming flag is set, fall through to do nothing? Actually the code returns without doing anything if bit is set.
        }
        else // weapon state != HOLSTERED (e.g., ACTIVE)
        {
            // Always hide/disable weapon mesh (parameter 0 = false)
            if (weaponPtr != 0) 
            {
                updateWeaponMesh(false); // FUN_0087d560(0)
                return;
            }
            updateWeaponMesh(false); // FUN_0087d560(0)
        }
    }
    // No action if weapon pointer invalid or dummy
    return;
}

// Helper functions (not defined here, assumed from callee addresses):
// FUN_0087bd50: void setWeaponHolstered(bool holstered);
// FUN_0087d560: void updateWeaponMesh(bool visible);