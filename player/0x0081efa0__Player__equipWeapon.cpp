// FUNC_NAME: Player::equipWeapon
void __thiscall Player::equipWeapon(Player* this, int weaponId)
{
    // +0x114: currentWeaponPtr (pointer to current weapon entity or 0)
    int* pCurrentWeapon = (int*)(this + 0x114);
    int currentWeaponId = 0;
    
    if (*pCurrentWeapon != 0) {
        // The pointer stored at +0x114 appears to be offset by 0x48 from the actual weapon ID
        currentWeaponId = *pCurrentWeapon - 0x48;
    }
    
    // If the requested weapon is already equipped, stop
    if (weaponId == currentWeaponId) {
        return;
    }
    
    // Get global player manager and this player
    int* playerManager = *(int**)(DAT_012233a0 + 4); // likely gPlayerManager
    int thisPlayerPtr = 0;
    int* inventoryList = 0;
    
    if (playerManager == 0) {
        thisPlayerPtr = 0;
    } else {
        thisPlayerPtr = (int)*playerManager - 0x1f30; // offset to this player object
        if (thisPlayerPtr == 0) {
            // fall through
        } else {
            // Get some global inventory list via handle DAT_01130fb0
            inventoryList = (int*)FUN_0043b870(DAT_01130fb0);
        }
    }
    
    bool alreadyEquipped = false;
    bool isDifferent = false;
    
    // Check if current weapon state allows change
    if ((*pCurrentWeapon == 0) || (*pCurrentWeapon == 0x48) || 
        (FUN_0043b870(DAT_0112af98) == 0)) 
    {
        // If we have a weapon to equip, scan inventory for it
        if (weaponId != 0) {
            int* invArray = (int*)(inventoryList[10]); // +10 offset: array of weapon entries
            int invCount = inventoryList[0xb];         // +11 offset: count
            int* invEnd = invArray + invCount;
            
            for (int* iter = invArray; iter != invEnd; ++iter) {
                int* weaponObj = (int*)*iter;
                int entryId = 0;
                if (*(int*)(weaponObj + 0x30) != 0) {
                    entryId = *(int*)(weaponObj + 0x30) - 0x48; // ID extraction
                }
                if (entryId == weaponId) {
                    // Check if we can use this weapon (FUN_009b11f0 likely a validation function)
                    char canUse = FUN_009b11f0();
                    if (canUse != 0) {
                        alreadyEquipped = true;
                        break;
                    }
                }
            }
        }
    } else {
        int* playerHandle = FUN_0043b870(DAT_0112af98); // get player from handle
        if (playerHandle != 0) {
            int* playerObj = (int*)*(playerHandle + 0xe8);
            if (playerObj != 0 && playerObj != 0x48) {
                alreadyEquipped = true;
            }
            if (((*(byte*)(playerHandle + 0x50) & 1) == 0) && !alreadyEquipped) {
                // If player is not in a state that blocks weapon change, show a message?
                FUN_00789d10();
            }
        }
    }
    
    // If there's an active action (like throwing? check +0xf0), stop it
    if (*(int*)(this + 0xf0) != 0) {
        FUN_004df600(); // stop current action
        FUN_00939960(); // stop sound?
    }
    
    // Check global state flag at thisPlayerPtr + 0x8e6
    if ((*(byte*)(thisPlayerPtr + 0x8e6) & 1) != 0) {
        return;
    }
    
    // Handle weapon change logic for a specific weapon
    if (weaponId != 0) {
        int* playerHandle2 = FUN_0043b870(DAT_0112af98);
        
        if (playerHandle2 == 0 || ((*(byte*)(playerHandle2 + 0x50) & 1) != 0)) {
            // Player is in a blocking state? (bit 0 set)
            // Check if weapon is a throwable
            bool isThrowable = false;
            char check1 = FUN_009a98b0(weaponId); // isWeapon?
            if (check1 != 0) {
                char check2 = FUN_009a9820(4, 1); // check flag 4
                if (check2 != 0) {
                    int throwableType = 0x75af262f; // some hash
                    // play throw animation? skip for now
                    isThrowable = true;
                    goto playSound;
                }
            }
            
            char check3 = FUN_009a9b80(weaponId); // isThrowable?
            if (check3 != 0) {
                char check4 = FUN_009a9820(0x80, 1); // check flag 0x80
                if (check4 != 0) {
                    FUN_006bc8d0(weaponId, 0x369ac561); // play animation?
                    int* p0 = FUN_00471610(); // get some position vector?
                    int* p1 = FUN_00471610();
                    int* p2 = FUN_00471610();
                    
                    // Cross product to determine if throwing is forward?
                    float dot = (*(float*)(p0 + 0x24)) * (*(float*)(p2 + 0x34) - *(float*)(p1 + 0x34))
                              + (*(float*)(p0 + 0x20)) * (*(float*)(p2 + 0x30) - *(float*)(p1 + 0x30))
                              + (*(float*)(p0 + 0x28)) * (*(float*)(p2 + 0x38) - *(float*)(p1 + 0x38));
                    if (dot >= 0.0f) {
                        int throwableType = 0x2d65afa1;
                        // Call virtual function at vtable+0x28 to start throw
                        (**(code**)(*inventoryList + 0x28))(0xf17389ab, 0, 0x80, 0);
                        isThrowable = true;
                        goto playSound;
                    }
                }
            }
        } else {
            // Player not blocking
            char check5 = FUN_009a9820(*(int*)(playerHandle2 + 0x10), 1);
            if (check5 != 0) {
                int soundToPlay = *(int*)(playerHandle2 + 0xa8); // some sound hash
            }
            if (!alreadyEquipped) {
                FUN_0081edf0(*(int*)(playerHandle2 + 0x10), check5); // unequip current weapon?
            }
            // Check if player is in a state where they should drop weapon?
            if (((*(byte*)(playerHandle2 + 0x34) & 4) != 0) &&
                (int* playerFromWeapon = FUN_006ad790(weaponId, 0x36cac259), playerFromWeapon != 0) &&
                (FUN_008b6ae0() != 0)) {
                FUN_0079f100(0x32, 0); // show hint "cannot equip while in water"?
            }
            FUN_0079f100(0x25, 0); // show hint "weapon equipped"?
        }
        
playSound:
        if (isThrowable) {
            if (!alreadyEquipped) {
                FUN_00939930(throwableType); // play sound?
            }
            goto done;
        }
    }
    
    // Stop any ongoing sounds
    FUN_00939960();
    
done:
    // Update current weapon pointer
    int newPtr = 0;
    if (weaponId != 0) {
        newPtr = weaponId + 0x48; // Convert ID back to pointer offset
    }
    
    if (*pCurrentWeapon != newPtr) {
        if (*pCurrentWeapon != 0) {
            FUN_004daf90(pCurrentWeapon); // release reference?
        }
        *pCurrentWeapon = newPtr;
        
        if (newPtr != 0) {
            // Update linked list: +0x4 is next pointer in weapon object
            *(int*)(this + 0x118) = *(int*)(newPtr + 4);
            *(int**)(newPtr + 4) = pCurrentWeapon;
        }
    }
    
    // If weapon is equipped and player is not blocking, refresh model?
    if ((*pCurrentWeapon != 0) && (*pCurrentWeapon != 0x48)) {
        int* playerHandle3 = FUN_0043b870(DAT_0112af98);
        if (playerHandle3 != 0 && ((*(byte*)(playerHandle3 + 0x50) & 1) == 0)) {
            FUN_007893c0(); // refresh weapon visual?
        }
    }
}