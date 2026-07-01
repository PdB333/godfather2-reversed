// FUNC_NAME: NetSession::handleStateUpdate
// Address: 0x00970560
// Role: Handles state transitions in the network session, including disconnection and cleanup.

void __fastcall NetSession::handleStateUpdate(int thisPtr)
{
    int stateMachine;
    int* vtablePtr;
    int allocResult;

    switch (*(int*)(thisPtr + 0xdc)) // +0xdc: current state
    {
    case 1: // State 1: Active session
        // Call vtable function at offset 0x8c on the object at +0x2ec
        (**(code**)(*(int*)(thisPtr + 0x2ec) + 0x8c))();
        if (*(int*)(thisPtr + 0x1e4) == 2) // +0x1e4: some condition (e.g., host migration)
        {
            *(unsigned int*)(thisPtr + 0x6f4) |= 2; // Set flag bit 1
            FUN_0096f920(*(int*)(thisPtr + 0x1a0), *(int*)(thisPtr + 0x19c)); // +0x1a0, +0x19c: parameters
            *(unsigned int*)(thisPtr + 0x6f4) &= 0xffefffff; // Clear flag bit 0x100000
            return;
        }
        FUN_0096a2f0(); // Clear some state
        // Fall through to default
    default:
        *(unsigned int*)(thisPtr + 0x6f4) &= 0xffefffff;
        return;

    case 4: // State 4: Disconnected
        goto handleDisconnect;

    case 5: // State 5: Lost connection
    case 7: // State 7: Reconnecting
        break;

    case 0xb: // Debug state
        FUN_005a04a0("DestroyCrewWeapons", 0, &DAT_00d8cdec, 0); // Debug log
    case 0xc: // Debug state
        FUN_005a04a0("ClearGamertagPopup", 0, &DAT_00d8cdec, 0); // Debug log
    }

    // Common path for states 5,7,0xb,0xc
    stateMachine = FUN_00965910(); // Get state machine object
    if (stateMachine != 0)
    {
        vtablePtr = (int*)FUN_00965910(); // Re-fetch? Possibly a different call
        (**(code**)(*vtablePtr + 0x8c))(); // Call vtable function
    }

handleDisconnect:
    if (*(char*)(thisPtr + 0x220) == '\0') // +0x220: flag indicating UI is active
    {
        FUN_00983190(); // Reset some state
        allocResult = FUN_009c8e50(0xf0); // Allocate 0xF0 bytes
        if (allocResult == 0)
        {
            allocResult = 0;
        }
        else
        {
            allocResult = FUN_00982280(0); // Initialize allocated object
        }
        *(int*)(allocResult + 0xc) = 0xb; // Set state to 0xb
        FUN_00982400(1); // Set some flag
        FUN_00981eb0("$mp_lost_conn_host_left"); // Show disconnect message
        *(int*)(allocResult + 0x14) = (int)&LAB_00968080; // Set callback
        FUN_00982e10(); // Update UI
        if (*(char*)(thisPtr + 0x220) == '\0')
        {
            vtablePtr = (int*)(thisPtr + 0x378); // +0x378: alternative vtable pointer
            goto callVtable;
        }
    }
    vtablePtr = (int*)(thisPtr + 0x2ec); // +0x2ec: primary vtable pointer

callVtable:
    (**(code**)(*vtablePtr + 0x8c))(); // Call vtable function
    int savedValue = *(int*)(thisPtr + 0x1e0); // +0x1e0: saved state
    FUN_0095e840(); // Update something
    *(int*)(thisPtr + 0x1e0) = savedValue; // Restore
    FUN_0096a2f0(); // Clear state
    *(unsigned int*)(thisPtr + 0x6f4) &= 0xffefffff; // Clear flag
    return;
}