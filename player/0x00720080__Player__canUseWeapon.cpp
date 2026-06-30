// FUNC_NAME: Player::canUseWeapon
// Address: 0x00720080
// Role: Determines if the player can use/activate a weapon based on state and time constraints.
// The function checks various conditions including weapon type, time limits, and special cases.

bool __thiscall Player::canUseWeapon(int *this, int *context, int paramTime) {
    bool canUse = false;
    
    // Validate the context and parameter
    if (!isContextValid(context, paramTime)) {
        return false;
    }
    
    // Get weapon state or action pointer from this object
    int *weaponStatePtr = (int *)this[1]; // +0x04 offset
    if (weaponStatePtr == 0) {
        weaponStatePtr = 0;
    } else {
        weaponStatePtr = (int *)((char *)weaponStatePtr - 0x48); // adjust base
    }
    
    int weaponState = 0;
    if (weaponStatePtr != 0) {
        weaponState = weaponStatePtr[0x200c / 4]; // offset 0x200c, likely weapon index or state
    }
    
    // weaponState must be nonzero and not 0x3c (maybe invalid)
    if (weaponState == 0 || weaponState == 0x3c) {
        return false;
    }
    
    // Check time condition
    int elapsed = getElapsedTime(context);
    int maxTime = getMaxTime();
    if (elapsed + paramTime <= maxTime) {
        canUse = true;
    } else {
        return false;
    }
    
    if (canUse) {
        // Additional condition check
        if (isSpecialConditionActive()) {
            // Lookup weapon data from global array indexed by weapon type (offset +0x14)
            int weaponType = *(int *)(weaponState + 0x14);
            int globalIndex = weaponType * 8; // each entry 8 bytes
            void *data1 = *(void **)(&DAT_00e517bc + globalIndex);
            int data2 = *(int *)(weaponState + 0x10);
            return lookupWeaponData(data1, data2);
        }
        
        // Switch on weapon type (offset +0x14)
        int weaponType = *(int *)(weaponState + 0x14);
        switch (weaponType) {
            case 0:  // No weapon
            case 6:  // Pistol? 
            case 7:  // Shotgun?
            case 8:  // SMG?
            case 10: // Grenade? (breaks, so allowed)
                break;
                
            case 9:  // Special weapon (e.g., rocket launcher)
            {
                float fVar1 = (**(float (__thiscall **)(int *))(*context + 0xc0))(context);
                float fVar2 = (**(float (__thiscall **)(int *))(*context + 0xc4))(context);
                if (fVar1 < fVar2) {
                    return true;
                }
                int result = checkSomeCondition(context);
                if (result != 0 && isGlobalConditionMet()) {
                    return true;
                }
                // Fall through to default
            }
            default:
                canUse = false; // disallow for other types
                break;
        }
    }
    
    return canUse;
}