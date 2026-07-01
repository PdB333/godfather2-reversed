// FUNC_NAME: InventoryManager::selectItem
void __thiscall InventoryManager::selectItem(int* thisPtr, InventorySlot* slot) {
    char* counter;
    float slotPriority;
    float currentPriority;
    int* currentSlot;
    byte newType;
    byte oldType;
    bool isSelected;

    oldType = *(byte*)((int)slot + 0x12);  // +0x12: slot's current type/ID
    newType = FUN_007ee560(*thisPtr);       // get desired type based on some context (e.g., picked weapon)
    if (newType != oldType) {
        // Update type counters: decrement old, increment new
        counter = (char*)(oldType + 0x14 + (int)thisPtr);
        *counter = *counter - 1;
        counter = (char*)(newType + 0x14 + (int)thisPtr);
        *counter = *counter + 1;
        *(byte*)((int)slot + 0x12) = newType; // store updated type
    }

    isSelected = false;
    // Skip selection if the player is in a restricted state (e.g., menu, cutscene)
    if ((*(byte*)(*thisPtr + 0x8e6) & 1) != 0) {
        // "Restricted" state: if this slot is the primary active slot, clear it
        if ((int*)thisPtr[1] == slot) {
            thisPtr[1] = 0;
        } else if ((int*)thisPtr[2] == slot) {
            // else if it's the secondary slot, clear it
            thisPtr[2] = 0;
        }
        // (no action taken if neither)
    } else {
        // Not restricted
        if (FUN_007f7c50() != 0) { // check if player is local?
            if (FUN_007fd760() == *thisPtr) goto skipSelection; // some identity check
        }
        currentSlot = (int*)thisPtr[1];
        if (currentSlot != slot) {
            if (currentSlot != nullptr) {
                slotPriority = (float)slot[3];          // +0xC: priority/distance of new slot
                currentPriority = (float)currentSlot[3]; // +0xC: priority of current primary
                if (slotPriority <= currentPriority) {
                    // Priority not better; check secondary slot
                    if ((int*)thisPtr[2] == slot) {
                        // Slot is already secondary? Only select if primary is "dual wield" mode (2)
                        if (*(int*)thisPtr[4] == 2) {
                            isSelected = true;
                            goto setFlag;
                        }
                        goto clearSecondary;
                    }
                    if ((int*)thisPtr[2] == nullptr) {
                        // No secondary slot; attempt to set it
                        if (FUN_00690150(0x51) != 0) { // check global flag (maybe "allow second weapon")
                            if (FUN_007ee730() != 0) { // additional condition (e.g., no conflicting action)
                                thisPtr[2] = (int)slot;
                                isSelected = true;
                            }
                        }
                        goto setFlag;
                    }
                    // Secondary slot exists; compare priorities again
                    if (slotPriority == currentPriority) {
                        // Equal priority; check additional flags (global state)
                        if (FUN_00690150(0x2e) == 0) { // if not in some state
                            if (FUN_00690150(0x2e) != 0) goto setFlag; // double check? (maybe copy-paste artifact)
                        }
                        goto setFlag;
                    }
                    // If slotPriority is lower than global min or currentPriority higher than global max, skip
                    if ((slotPriority < g_minSelectPriority) || (g_maxSelectPriority < currentPriority))
                        goto setFlag;
                    // Fall through: replace current primary if its flag allows overwrite
                    if ((*(byte*)(currentSlot + 4) & 1) != 0) {
                        *(ushort*)(currentSlot + 4) &= 0xfffe; // clear selected flag
                    }
                }
                // Deselect the current primary slot
                FUN_007ee940(currentSlot);
            }
            // Set new primary slot
            thisPtr[1] = (int)slot;
            isSelected = true;
        }
    }

skipSelection:
    if ((int*)thisPtr[2] == slot) {
clearSecondary:
        thisPtr[2] = 0;
    }

setFlag:
    if (isSelected != (*(byte*)(slot + 4) & 1)) {
        if (isSelected) {
            *(ushort*)(slot + 4) |= 1;   // set 'selected' flag (+0x4)
        } else {
            *(ushort*)(slot + 4) &= 0xfffe; // clear 'selected' flag
        }
    }
}