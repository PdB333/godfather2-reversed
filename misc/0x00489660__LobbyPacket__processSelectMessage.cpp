// FUNC_NAME: LobbyPacket::processSelectMessage
void __thiscall LobbyPacket::processSelectMessage(void) {
    char *nameString;
    int cmpResult;
    int objectHandle;
    byte loopIndex;

    // +0x03: selectedIndex, default -1 (no selection)
    this->selectedIndex = -1;

    // Check packet header: first byte = 0xFE, second = 0x02
    if ((this->header1 == -2) && (this->header2 == 0x02)) {
        // Relocate pointer to name array (offset 4) if non-zero
        if (this->nameArrayOffset != 0) {
            this->nameArray = (char *)((int)this + this->nameArrayOffset);
        }
        // Relocate pointer to data array (offset 8) if non-zero
        if (this->dataArrayOffset != 0) {
            this->dataArray = (int *)((int)this + this->dataArrayOffset);
        }

        // Global matchmaking state: gMatchmakingData at DAT_012234a4
        // +0x3c: current selection index
        // +0x20: pointer to a table of selection names (each 0x61 bytes)
        // +0xa4: total number of selectable names
        // +0xac: base pointer to name table
        uint selectionIndex = *(uint *)(DAT_012234a4 + 0x3c);
        uint nameTableSize = *(uint *)(*(int *)(DAT_012234a4 + 0x20) + 0xa4);
        if (selectionIndex < nameTableSize) {
            nameString = (char *)(selectionIndex * 0x61 + *(int *)(*(int *)(DAT_012234a4 + 0x20) + 0xac));
        } else {
            nameString = &DAT_01222260; // Fallback empty/placeholder string
        }

        loopIndex = 0;
        // +0x02: number of entries in this packet
        if (this->numEntries != 0) {
            while (true) {
                // Compare two‑character name ID with the current selection name
                cmpResult = __strnicmp(nameString, (char *)(this->nameArray + loopIndex * 2), 2);
                if (cmpResult == 0) break;
                loopIndex++;
                if (this->numEntries <= loopIndex) {
                    return;
                }
            }
            // Found matching entry – get its associated data (4‑byte handle)
            objectHandle = FUN_004059b0(*(undefined4 *)(this->dataArray + loopIndex));
            if (objectHandle != 0) {
                objectHandle = FUN_004025a0(objectHandle); // Dereference handle to object pointer
                if (objectHandle == 0) {
                    objectHandle = -1;
                } else {
                    objectHandle = *(int *)(objectHandle + 0x24); // Read object type field
                }
                // If object type is 0, 1, or 3, abort without taking action
                if (objectHandle == 3) return;
                if (objectHandle == 0) return;
                if (objectHandle == 1) return;
            }
            // Object type is acceptable – perform action (e.g., validate/confirm selection)
            FUN_00404280(*(undefined4 *)(this->dataArray + loopIndex), 0, 0);
            // Record the index of the selected entry
            this->selectedIndex = loopIndex;
        }
    }
    return;
}