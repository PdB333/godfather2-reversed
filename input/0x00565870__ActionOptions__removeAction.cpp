// FUNC_NAME: ActionOptions::removeAction
void ActionOptions::removeAction(byte* actionName) {
    // +0x20: m_pOwner pointer (some parent)
    // +0x128: vtable pointer (virtual function table)
    // +0x23C: m_actionStrings[5] - array of 5 action name strings (each 0x84 bytes, first byte indicates presence)
    // +0x2BC: m_actionCounts[5] - array of 5 ints (each 0x84 apart, representing counts/priorities)
    // Additional slot flags at +0x2C0, +0x344, +0x3C8, +0x44C (these are the first bytes of strings for slots 1-4)
    // Additional counts at +0x340, +0x3C4, +0x448, +0x4CC

    int index = 0;
    byte* slotStringBase = (byte*)(this + 0x23C);
    byte* currentSlotString = slotStringBase;

    while (true) {
        // Compare the current slot's string with the input actionName (2-byte characters, null-terminated)
        byte* s1 = currentSlotString;
        byte* s2 = actionName;
        int cmpResult;

        do {
            byte b1 = *s1;
            byte b2 = *s2;
            if (b1 == b2) {
                if (b1 == 0) {
                    cmpResult = 0;
                    break;
                }
                // Compare second byte
                b1 = s1[1];
                b2 = s2[1];
                if (b1 == b2) {
                    if (b1 == 0) {
                        cmpResult = 0;
                        break;
                    }
                    s1 += 2;
                    s2 += 2;
                } else {
                    cmpResult = (b1 < b2) ? -1 : 1;
                    break;
                }
            } else {
                cmpResult = (b1 < b2) ? -1 : 1;
                break;
            }
        } while (true);

        if (cmpResult == 0) {
            // Found a match: remove this action slot
            // Call some helper with m_pOwner and the name
            FUN_00569b40(*(undefined4*)(this + 0x20), actionName);
            // Call a virtual function (vtable+4) with the name
            (**(code**)(**(int**)(this + 0x128) + 4))(actionName);

            // Get the count value of the matched slot (from the counts array)
            int removedCount = *(int*)(index * 0x84 + 0x2BC + (int)this);
            // Clear the first byte of the matched slot's string (mark as empty)
            *(byte*)(index * 0x84 + 0x23C + (int)this) = 0;

            // Decrement counts of other slots if their strings are non-empty and have a higher count than the removed one
            // Slot 0
            if (*(char*)(this + 0x23C) != '\0' && removedCount < *(int*)(this + 0x2BC)) {
                *(int*)(this + 0x2BC) -= 1;
            }
            // Slot 1
            if (*(char*)(this + 0x2C0) != '\0' && removedCount < *(int*)(this + 0x340)) {
                *(int*)(this + 0x340) -= 1;
            }
            // Slot 2
            if (*(char*)(this + 0x344) != '\0' && removedCount < *(int*)(this + 0x3C4)) {
                *(int*)(this + 0x3C4) -= 1;
            }
            // Slot 3
            if (*(char*)(this + 0x3C8) != '\0' && removedCount < *(int*)(this + 0x448)) {
                *(int*)(this + 0x448) -= 1;
            }
            // Slot 4
            if (*(char*)(this + 0x44C) != '\0' && removedCount < *(int*)(this + 0x4CC)) {
                *(int*)(this + 0x4CC) -= 1;
            }

            // Reset the matched slot's count to 15 (0xF)
            *(int*)(index * 0x84 + 0x2BC + (int)this) = 0xF;
            return;
        }

        index++;
        if (index > 4) {
            return;  // No match found
        }
        currentSlotString = slotStringBase + index * 0x84;
    }
}