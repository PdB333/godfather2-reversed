// FUNC_NAME: NetSession::validateSessionID
// Address: 0x00789600
// Role: Validates a session GUID and registers a node for event callbacks.
// The function checks if the session's GUID (stored at offsets 0x84, 0x88, 0x8C, 0x90) is either all zeros or a specific sentinel value. If invalid, it does nothing.
// If valid, it resolves the GUID, queries a hash (0x2017e685) via a virtual method, and then either retrieves a global singleton (if param2==0) or links the provided node into a stack-based list.
// Finally, it broadcasts notifications via FUN_00408a00 and FUN_00408bf0.

int __thiscall NetSession::validateSessionID(int thisPtr, void* sessionNode) {
    uint nodeAddr = (uint)sessionNode;
    int* pGuid = (int*)(thisPtr + 0x84);

    // Check if the GUID at offsets 0x84-0x90 is either all zeros or matches the sentinel value.
    // The sentinel is -0x45245246, -0x41104111, -0x153ea5ab, -0x6eeff6ef
    if ( ((pGuid[0] != 0) || (*(int*)(thisPtr + 0x88) != 0) || (*(int*)(thisPtr + 0x8C) != 0) || (*(int*)(thisPtr + 0x90) != 0)) &&
         ((pGuid[0] != -0x45245246) || (*(int*)(thisPtr + 0x88) != -0x41104111) || (*(int*)(thisPtr + 0x8C) != -0x153EA5AB) || (*(int*)(thisPtr + 0x90) != -0x6EEFF6EF)) )
    {
        // Resolve the GUID to an object pointer (likely a virtual table or interface).
        int* resolvedPtr = (int*)FUN_00446100(pGuid, 0);
        uint tempParam = 0;
        // Virtual call at vtable+0x10: query the object with hash 0x2017e685.
        char isValid = (**(code**)(*resolvedPtr + 0x10))(0x2017e685, &tempParam);

        // Stack structures for callbacks. They reference global data.
        // PTR_FUN_00d5dbbc is a vtable/function pointer table.
        // DAT_01205228 is a global callback structure.
        int stackNode1[5];
        stackNode1[0] = (int)&PTR_FUN_00d5dbbc;  // +0x00: callback vtable pointer
        stackNode1[1] = 0;                        // +0x04: next?
        stackNode1[2] = *(int*)((isValid != 0 ? tempParam : 0) + 0x50); // +0x08: value from resolved
        stackNode1[3] = 0;                        // +0x0C: unused?
        stackNode1[4] = DAT_01205228;            // +0x10: global callback data

        if (nodeAddr == 0) {
            // If no node provided, get a global singleton (e.g., GodfatherGameManager).
            int gameManager = FUN_00471610();
            stackNode1[4] = 1;  // flag or type
            // Read fields at +0x30 and +0x38 from the singleton.
            *(uint64*)(&stackNode1[2]) = *(uint64*)(gameManager + 0x30);
            stackNode1[3] = *(int*)(gameManager + 0x38);
        }
        else if (nodeAddr + 0x48 != 0) {
            // If node has a valid next pointer (offset +0x48), link it into a local list.
            // Save the old value at nodeAddr+0x4C (prev pointer) and insert the stack node.
            *(int*)(nodeAddr + 0x4C) = (int)&stackNode1[1]; // set prev to our list head
            stackNode1[1] = nodeAddr + 0x48;               // next points to the node's next
        }

        // First notification with stack callback structure.
        int callbackBuf1[2] = { DAT_0112ad8c, (int)&stackNode1 };
        FUN_00408a00(callbackBuf1, 0);

        // If the local list was modified, clean up the old node.
        if (stackNode1[1] != 0) {
            FUN_004daf90(&stackNode1[1]);
        }
    }

    // Second part: always execute, creates another stack-based list for a different callback.
    // Prepare another stack node referencing PTR_FUN_00e31e2c.
    int stackNode2[3];
    stackNode2[0] = (int)&PTR_FUN_00e31e2c;  // callback vtable pointer
    if (nodeAddr == 0) {
        stackNode2[1] = 0;   // next pointer
    } else {
        stackNode2[1] = nodeAddr + 0x48;   // use the node's next field
    }
    stackNode2[2] = 0;   // prev pointer placeholder

    // Link the second stack node into itself (circular? or replace prev).
    if (stackNode2[1] != 0) {
        int oldPrev = *(int*)(stackNode2[1] + 4);
        *(int**)(stackNode2[1] + 4) = &stackNode2[1]; // point prev to itself? Actually store address of our local.
        stackNode2[2] = oldPrev; // restore? But oldPrev is not used.
    }

    // Build callback array for FUN_00408a00.
    int callbackBuf2[3] = { *(int*)(thisPtr + 0x74), (int)&stackNode2, 0 };
    FUN_00408a00(callbackBuf2, 0);

    // Another notification with a different global flag.
    int callbackBuf3[3] = { DAT_0112afa0, (int)&stackNode2, 0 };
    int offset = 0;
    if (*(int*)(thisPtr + 0xC) != 0) {
        offset = *(int*)(thisPtr + 0xC) + 0x3C;
    }
    FUN_00408bf0(callbackBuf3, offset, 0);

    // Clean up the temporary list node if it was set.
    if (stackNode2[1] != 0) {
        FUN_004daf90(&stackNode2[1]);
    }

    return 1;
}