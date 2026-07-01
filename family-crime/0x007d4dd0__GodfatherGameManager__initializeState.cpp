// FUNC_NAME: GodfatherGameManager::initializeState
void __fastcall GodfatherGameManager::initializeState(int thisPtr)
{
    int dataPtr = *(int *)(thisPtr + 0x58); // +0x58: m_pData (pointer to large game state)
    int currentTime = FUN_007ff880(); // Get current time or frame counter
    int tempVar = 0;
    *(int *)(thisPtr + 0x7c) = currentTime; // +0x7c: m_lastUpdateTime

    FUN_0079f100(0x2c, 0); // Allocate memory? (size 0x2c, flags 0)
    FUN_0093af80(); // Some initialization routine
    FUN_006c1360(); // Another init routine

    int flag1 = *(int *)(dataPtr + 0x2ba4); // +0x2ba4: m_flag1
    int flag2 = *(int *)(dataPtr + 0x2ba8); // +0x2ba8: m_flag2
    int flag3 = *(int *)(dataPtr + 0x2bac); // +0x2bac: m_flag3
    int flag4 = *(int *)(dataPtr + 0x2bb0); // +0x2bb0: m_flag4

    if (flag1 == 0 && flag2 == 0 && flag3 == 0 && flag4 == 0) {
        // All flags zero: perform first-time initialization
        int allocParams[3] = {2, 0x10, 0}; // {type, size, flags}
        int allocResult = FUN_009c8ed0(0x1b0, allocParams); // Allocate object of size 0x1b0
        int newObj;
        if (allocResult == 0) {
            newObj = 0;
        } else {
            newObj = FUN_006c2840(); // Initialize the allocated object
        }
        FUN_007d3ad0(newObj); // Register or attach the object

        int subObj = *(int *)(thisPtr + 0x8c); // +0x8c: m_pSubObject
        if (subObj == 0) {
            subObj = 0;
        } else {
            subObj = subObj - 0x48; // Adjust pointer to base of sub-object
        }
        *(char *)(subObj + 0x54) = 1; // Set some flag in sub-object
        FUN_007d3470(); // Apply changes
    } else {
        // Flags are set: use them to get a value
        int value = FUN_00446130(&flag1, 0); // Convert flags to some value
        FUN_007d3ad0(value); // Register/attach

        int subObj = *(int *)(thisPtr + 0x8c);
        if (subObj != 0 && subObj != 0x48) {
            subObj = *(int *)(thisPtr + 0x8c);
            if (subObj == 0) {
                FUN_006c16d0(0x68); // Free memory at offset 0x68
            } else {
                FUN_006c16d0(subObj + 0x20); // Free memory at subObj+0x20
            }
        }
    }

    // Listener/observer pattern: update linked list
    int newListener = FUN_007ff880(); // Get current listener target
    int listenerTarget;
    if (newListener != 0) {
        listenerTarget = newListener + 0x48;
    } else {
        listenerTarget = 0;
    }

    // local_120 is a linked list node (on stack)
    if (local_120 != listenerTarget) {
        if (local_120 != 0) {
            FUN_004daf90(&local_120); // Remove from list
        }
        local_120 = listenerTarget;
        if (listenerTarget != 0) {
            local_11c = *(int *)(listenerTarget + 4); // Save next pointer
            *(int **)(listenerTarget + 4) = &local_120; // Insert at head
        }
    }

    FUN_007f63e0(0x4f); // Debug/log message ID 0x4f
    FUN_006c16d0(local_148); // Free temporary buffer (local_148 is a char[40])

    int subObj2 = *(int *)(thisPtr + 0x8c);
    if (subObj2 == 0) {
        subObj2 = 0;
    } else {
        subObj2 = subObj2 - 0x48;
    }

    // Call logging function with global data
    FUN_00424dc0(*(int *)(&DAT_00002494 + dataPtr), subObj2, DAT_00d5eee4, 6, 0);

    if (local_120 != 0) {
        FUN_004daf90(&local_120); // Cleanup listener node
    }
    return;
}