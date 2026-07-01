// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_StrategyGame_AcceptSelectedMember
// FUNC_NAME: DonControlGadget::sendPauseCommand
void __fastcall DonControlGadget::sendPauseCommand(DonControlGadget* this)
{
    // Alloca probe for large stack buffer (4112 bytes)
    uint* selectedCrewMemberFlags;
    int i;
    undefined4 actionType; // Local variable for mapped action ID
    undefined4* crewMemberList;
    undefined1* commandStr;
    int listCount;
    int listCapacity;
    code* deallocFunc;
    undefined4 hashKey;
    undefined4 someParam;
    undefined4 unused;
    undefined1 local_1024;
    int local_1020; // List pointer
    int local_101c; // List count
    int local_1018; // List capacity
    undefined1 commandBuffer[4112]; // Large buffer for something
    undefined4 uStack_4;

    // Initialize list management
    local_1020 = 0;
    local_1018 = 0;
    // Build a key from global data
    hashKey = DAT_00e44758;
    someParam = 0;
    unused = 0;
    local_1024 = 0;
    local_101c = 0;
    // Initialize memory allocator (0 = default arena)
    FUN_009c8f10(0);

    // Read action type from this+0x64 (offset 100)
    int actionTypeRaw = *(int*)(this + 100);
    local_1020 = 0;
    local_1018 = 0;

    // Map action type to a integer used elsewhere
    if (actionTypeRaw == 1) {
        // Guard/Defend? -> 4
        someParam = 4;
    }
    else if (actionTypeRaw == 2) {
        // Attack -> 1
        someParam = 1;
    }
    else if (actionTypeRaw == 3) {
        // Bomb -> 2
        someParam = 2;
    }

    // Read crew member target from this+0x134 (offset 308)
    unused = *(undefined4*)(this + 0x134);

    // Iterate over global crew member array (0x24 bytes per entry, 0xfc total = 11 entries)
    for (i = 0; i < 0xfc; i += 0x24) {
        selectedCrewMemberFlags = (uint*)(i + 0x18 + DAT_0112989c);
        // Check each slot's flag at bit 2 (selected?)
        if ((selectedCrewMemberFlags != (uint*)0x0) && (((*selectedCrewMemberFlags >> 2) & 1) != 0)) {
            // Get crew member handle from slot
            int crewHandle = FUN_0090a5a0();
            if (crewHandle != 0) {
                // If member has some property (byte at +0x5f bit 0), do something
                if ((*(byte*)(crewHandle + 0x5f) & 1) != 0) {
                    FUN_0090a700();
                }
                // Get the actual crew member object (handle)
                int crewMemberObj = FUN_0090a5a0();
                // Append to dynamic list (similar to std::vector pattern)
                if (local_101c == local_1018) {
                    // Grow list if needed
                    if (local_1018 == 0) {
                        i = 1;
                    }
                    else {
                        i = local_1018 * 2;
                    }
                    // Reallocate list (function likely does realloc)
                    FUN_006b1e10(i);
                }
                // Store member object at current index
                undefined4* listPos = (undefined4*)(local_1020 + local_101c * 4);
                local_101c++;
                if (listPos != (undefined4*)0x0) {
                    *listPos = crewMemberObj;
                }
            }
        }
    }

    // If no crew members selected, skip everything
    if (local_101c == 0) goto cleanup;

    // Send some event with hash key?
    FUN_008c7cb0(0x637b907, &hashKey);

    // Play appropriate sound based on action type
    if (*(int*)(this + 100) == 3) {
        // Bomb action sound
        FUN_00894c90(0x67fe879c);
    }
    else if (*(int*)(this + 100) == 2) {
        // Attack action sound
        FUN_00894c90(0x6e887d62);
    }

    // Prepare UI state
    FUN_00604be0();

    // Set up command string for UI element
    undefined4 someGlobal = DAT_012234a4;
    commandStr = (undefined1*)0x0;
    // These locals are used for building the command string
    undefined4 local_103c = 0;
    undefined4 local_1038 = 0;
    deallocFunc = (code*)0x0;

    // Get a base string pointer
    undefined4* uiStringPtr = (undefined4*)FUN_006b2160();
    undefined1* baseString = (undefined1*)*uiStringPtr;
    if (baseString == (undefined1*)0x0) {
        baseString = &DAT_0120546e; // Empty string default
    }
    // Set UI element at index 0x76 to that string
    FUN_00604c10(0x76, baseString);

    // Based on number of selected crew members, pick command string
    if (local_101c == 1) {
        // Single target command
        undefined4* singleStringPtr = (undefined4*)FUN_00790610();
        undefined1* singleString = (undefined1*)*singleStringPtr;
        if (singleString == (undefined1*)0x0) {
            singleString = &DAT_0120546e;
        }
        FUN_00604c10(0x6e, singleString);

        int action = *(int*)(this + 100);
        if (action == 1) {
            // Guard or Defend based on target's property
            if (*(int*)(*(int*)(this + 0x134) + 0xfc) == 0) {
                commandStr = (undefined1*)"$pause_send_guard_single";
            }
            else {
                commandStr = (undefined1*)"$pause_send_defend_single";
            }
            goto sendCommand;
        }
        if (action == 2) {
            commandStr = (undefined1*)"$pause_send_attack_single";
            goto sendCommand;
        }
        if (action == 3) {
            commandStr = (undefined1*)"$pause_send_bomb_single";
            goto sendCommand;
        }
    }
    else {
        // Multi-target command
        int action = *(int*)(this + 100);
        if (action == 1) {
            if (*(int*)(*(int*)(this + 0x134) + 0xfc) == 0) {
                commandStr = (undefined1*)"$pause_send_guard_multi";
            }
            else {
                commandStr = (undefined1*)"$pause_send_defend_multi";
            }
        }
        else if (action == 2) {
            commandStr = (undefined1*)"$pause_send_attack_multi";
        }
        else if (action == 3) {
            commandStr = (undefined1*)"$pause_send_bomb_multi";
        }
        else {
            // Fallthrough, skip send
            goto skipSend;
        }
sendCommand:
        // Actually send the command via some system
        FUN_006038a0(someGlobal, commandBuffer, &commandStr, commandStr);
    }

skipSend:
    // Get a UI object from the system
    int uiObj = FUN_009c8e50(0xf0);
    if (uiObj == 0) {
        uiObj = 0;
    }
    else {
        uiObj = FUN_00982280(0);
    }

    undefined1* strToUse = commandStr;
    if (commandStr == (undefined1*)0x0) {
        strToUse = &DAT_0120546e;
    }
    // Set the command text on the UI object
    FUN_00981eb0(strToUse);

    // Configure the UI object for refresh
    *(undefined4*)(uiObj + 0xc) = 3; // Some state
    *(undefined4*)(uiObj + 0x20) = 0x510c352b; // Hash identifier
    *(undefined1**)(uiObj + 0x14) = &LAB_0097f580; // Pointer to refresh callback

    // Trigger UI refresh?
    FUN_00982e10();

    // If we allocated a command string, free it
    if (commandStr != (undefined1*)0x0) {
        (*deallocFunc)(commandStr);
    }

    // Cleanup UI state
    FUN_00604c00();

cleanup:
    // Free the dynamic list if allocated
    if (local_1020 != 0) {
        FUN_009c8f10(local_1020);
    }
    return;
}