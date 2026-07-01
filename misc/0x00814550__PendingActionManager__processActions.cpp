// FUNC_NAME: PendingActionManager::processActions

void __thiscall PendingActionManager::processActions(int this, unsigned short actionMask, int entityId, int unusedParam, bool activateEntity)
{
    // Structure: PendingActionManager
    // +0x08: pointer to array of Entry (8 bytes each)
    // +0x0C: count of entries
    unsigned int index = 0;
    if (*(unsigned int*)(this + 0xC) != 0) {
        int* entry = *(int**)(this + 0x8);
        do {
            // Each entry: int id, unsigned short flagsA, unsigned short flagsB  (offsets +0, +4, +6)
            if (*entry == entityId) {
                unsigned short combinedFlags = *(unsigned short*)((int)entry + 6) | *(unsigned short*)(entry + 1);
                if ((actionMask & combinedFlags) != 0) {
                    // Check if entity is alive (returns 0 if alive)
                    bool isAlive = (FUN_00405720(entityId, 0) == 0);
                    unsigned short remainingFlagsA = *(unsigned short*)(entry + 1) | *(unsigned short*)((int)entry + 6);
                    // Process lowest set bit present in both combined and actionMask
                    if (((-remainingFlagsA & remainingFlagsA & actionMask) != 0) {
                        if ((*(unsigned short*)(entry + 1) & actionMask) != 0) {
                            if (isAlive) {
                                FUN_00447b50(entityId, activateEntity ? 1 : 0 /* param_5?*/);
                            } else {
                                FUN_00406280(entityId, 1);
                            }
                        }
                        if ((*(unsigned short*)((int)entry + 6) & actionMask) != 0) {
                            if (isAlive) {
                                FUN_00447b50(entityId, activateEntity ? 1 : 0);
                            } else {
                                FUN_00406280(entityId, 0);
                            }
                        }
                    }
                    // Clear the processed bits from both flag fields
                    *(unsigned short*)(entry + 1) = *(unsigned short*)(entry + 1) & ~actionMask;
                    unsigned short updatedFlagsB = *(unsigned short*)((int)entry + 6) & ~actionMask;
                    *(unsigned short*)((int)entry + 6) = updatedFlagsB;
                    unsigned short newCombined = *(unsigned short*)(entry + 1) | updatedFlagsB;
                    if (newCombined == 0) {
                        // Remove this entry by swapping with last and decrement count
                        int count = *(int*)(this + 0xC);
                        if (index != count - 1) {
                            int* base = *(int**)(this + 0x8);
                            *(unsigned int*)(base + index * 2) = *(unsigned int*)(base + (count - 1) * 2);
                            *(unsigned short*)((int)(base + index * 2) + 4) = *(unsigned short*)((int)(base + (count - 1) * 2) + 4);
                            *(unsigned short*)((int)(base + index * 2) + 6) = *(unsigned short*)((int)(base + (count - 1) * 2) + 6);
                        }
                        *(int*)(this + 0xC) = count - 1;
                    } else {
                        // If the lowest set bit of newCombined is in updatedFlagsB, fire callback
                        if ((updatedFlagsB & (-newCombined & newCombined)) != 0) {
                            if (isAlive) {
                                FUN_00447ab0(entityId, 0, activateEntity ? 1 : 0);
                            } else {
                                FUN_00406230(entityId, 0);
                            }
                        }
                        // Similarly for flagsA
                        if ((*(unsigned short*)(entry + 1) & (-newCombined & newCombined)) != 0) {
                            if (isAlive) {
                                FUN_00447ab0(entityId, 1, activateEntity ? 1 : 0);
                            } else {
                                FUN_00406230(entityId, 1);
                            }
                        }
                    }
                }
                break;
            }
            index++;
            entry += 2;
        } while (index < *(unsigned int*)(this + 0xC));
    }
    // If activateEntity flag is set, perform finalization
    if ((char)activateEntity != 0) {
        if (FUN_004061f0(entityId) != 0) {
            FUN_00814120(entityId);
            return;
        }
        int somePtr = FUN_004059b0(entityId);
        if (somePtr != 0) {
            int obj = FUN_004025a0(somePtr);
            if (obj != 0) {
                FUN_00404c40(obj);
            }
        }
    }
}