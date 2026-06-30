// FUN_NAME: GodfatherGameManager::processInitCommands
void __thiscall GodfatherGameManager::processInitCommands(void) {
    // param_1 is this pointer to GodfatherGameManager
    // Called with a debug marker sentinel
    FUN_0043aff0(in_EAX, 0x197c1972); // likely beginSection or pushDebugMarker

    bool bWorkDone = false;
    undefined4** ppNextNode = local_1c;     // linked list node pointer (if list mode)
    uint uIndex = local_6c;                 // array index (if array mode)

    do {
        bool bIterEnd;
        if (local_78 == '\0') {
            // Linked list mode: terminate when current node is null
            bIterEnd = (*ppNextNode == (undefined4*)0x0);
        } else {
            // Array mode: terminate when index reaches element count
            bIterEnd = (uIndex == local_68);
        }

        if (bIterEnd) {
            if (bWorkDone) {
                FUN_005467e0(); // finalize pending work
            }
            return;
        }

        undefined4** ppEntry;
        if (local_78 == '\0') {
            // Linked list: entry is the current node
            ppEntry = ppNextNode;
        } else {
            // Array: entry pointer is taken from local_64 (preset)
            ppEntry = &local_64;
        }

        // Decode command type from entry
        uint cmdType;
        if (*(short*)((int)ppEntry + 6) == 0x25e3) {
            // Special case: type stored as ushort at offset 4 (relative to original entry?)
            cmdType = (uint)*(ushort*)(ppEntry + 1);
        } else {
            cmdType = (uint)ppEntry[1];
        }

        // Apply assignments based on command type
        switch (cmdType) {
        case 0:
            // Flag work done if byte at +8 is non-zero
            if (*(char*)(ppEntry + 2) != '\0') {
                bWorkDone = true;
            }
            break;
        case 1:
            // No operation
            break;
        case 2: {
            int iMgr1 = *(int*)((int)this + 0x2E8); // +0x2E8: manager pointer 1
            *(undefined4**)(iMgr1 + 0x84) = ppEntry[2]; // set field at +0x84
            break;
        }
        case 3:
            // Manager1 +0x88
            *(undefined4**)(*(int*)((int)this + 0x2E8) + 0x88) = ppEntry[2];
            break;
        case 4:
            // Manager2 +0x80 (manager at +0x368)
            *(undefined4**)(*(int*)((int)this + 0x368) + 0x80) = ppEntry[2];
            break;
        case 5:
            // Manager2 +0x60
            *(undefined4**)(*(int*)((int)this + 0x368) + 0x60) = ppEntry[2];
            break;
        case 6:
            // Manager2 +0x64 (100 = 0x64)
            *(undefined4**)(*(int*)((int)this + 0x368) + 0x64) = ppEntry[2];
            break;
        case 7:
            // Manager2 +0x68
            *(undefined4**)(*(int*)((int)this + 0x368) + 0x68) = ppEntry[2];
            break;
        case 8:
            // Manager2 +0x6C
            *(undefined4**)(*(int*)((int)this + 0x368) + 0x6C) = ppEntry[2];
            break;
        case 9:
            // Manager2 +0x70
            *(undefined4**)(*(int*)((int)this + 0x368) + 0x70) = ppEntry[2];
            break;
        case 10: {
            int iMgr2 = *(int*)((int)this + 0x368);
            // Manager2 +0x84
            *(undefined4**)(iMgr2 + 0x84) = ppEntry[2];
            break;
        }
        }

        // Advance to next entry
        if (local_78 == '\0') {                     // linked list mode
            if ((int)uIndex < 0) {
                // Jump by offset stored in first word of node
                local_1c = (undefined4**)((int)ppNextNode + (int)*ppNextNode);
                FUN_0043b140();                      // next node processing helper
                ppNextNode = local_1c;
                uIndex = local_6c;
            } else if ((int)uIndex < (int)(local_68 - 1)) {
                local_6c = uIndex + 1;
                local_1c = (undefined4**)((int)ppNextNode + (int)*ppNextNode);
                ppNextNode = (undefined4**)((int)ppNextNode + (int)*ppNextNode);
                uIndex = local_6c;
            } else {
                local_1c = (undefined4**)&DAT_01163cf8; // sentinel terminator
                ppNextNode = (undefined4**)&DAT_01163cf8;
            }
        } else {                                    // array mode
            local_6c = uIndex + 1;
            uIndex = local_6c;
            if (local_6c != local_68) {
                local_60 = (short)local_6c;         // store as short (maybe for bitmask)
                // Skip entries whose bit is set in the bitmap at local_74
                if ((*(byte*)((local_6c >> 3) + local_74) & (byte)(1 << ((byte)local_6c & 7))) == 0) {
                    local_5c = *local_70;           // copy value from array pointer
                    local_64 = local_70;            // set entry to current array element
                    local_70 = local_70 + 1;        // advance array pointer
                } else {
                    local_64 = (undefined4*)0x0;
                    local_5c = 0;
                }
            }
        }
    } while (true);
}