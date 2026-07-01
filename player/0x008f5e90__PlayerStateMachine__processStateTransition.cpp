// FUNC_NAME: PlayerStateMachine::processStateTransition
void __thiscall PlayerStateMachine::processStateTransition(PlayerStateMachine* this_, int param_2, int param_3, int isEntering)
{
    // Offsets relative to this_:
    //   -0x2084: currentState (int)
    //   -0x2080: flags (uint, bit 3 used here)
    //   -0x44:   somePointer (used for condition)
    //   -0x2068: pOwnerVTable (pointer to owner object's vtable)
    //   -0x2060: data1 (used in state 2)
    //   -0x205c: data2 (used in state 2)
    //   -0x2078: contextData (used in state 4)
    //   +0x0C: pAllocatedObj (pointer to a heap object, freed here)
    //   +0x1E0: timerOrCooldown (byte, reset in state 4)

    undefined* stringPtr = nullptr;  // puVar3, initially null
    int unk1 = 0;                    // uVar4
    int unk2 = 0;                    // uVar5

    // Check current state and some pointer condition
    if (*(int*)((char*)this_ - 0x2084) == 2 && *(int*)((char*)this_ - 0x44) != 0)
    {
        int audioData = FUN_008f1ff0();         // Likely fetch audio context
        FUN_004d3d90(audioData);                // Play or stop sound
    }

    // Release allocated object if present
    if (*(int*)((char*)this_ + 0xC) != 0)
    {
        // Call virtual function (index 1) on owner object to free the resource
        (**(code**)(**(int**)((char*)this_ - 0x2068) + 4))(*(int*)((char*)this_ + 0xC), 0x40C);
        *(int*)((char*)this_ + 0xC) = 0;
    }

    // Update state active flag based on isEntering parameter
    if (isEntering == 1)
    {
        *(int*)((char*)this_ - 0x2080) |= 8;       // Set bit 3: state active
    }
    else
    {
        *(int*)((char*)this_ - 0x2080) &= 0xFFFFFFF7; // Clear bit 3
        FUN_008f1fc0();                              // Deactivate or cleanup
    }

    // State-specific updates
    switch (*(int*)((char*)this_ - 0x2084))
    {
    case 2:
        if (*(int*)((char*)this_ - 0x44) != 0)
        {
            // Play animation or trigger event with type 3
            FUN_008f1e20(3, *(int*)((char*)this_ - 0x2060), *(int*)((char*)this_ - 0x205C));
            stringPtr = (undefined*)0x0;
            if (stringPtr == (undefined*)0x0)
            {
                stringPtr = &DAT_0120546e;           // Some string constant (e.g., "sound_event")
            }
            FUN_008f5d30(stringPtr, 0);              // Play sound or start chatter
        }
        break;

    case 5:
        FUN_008f37a0();  // Likely update specific state logic
        break;

    case 4:
        *(char*)((char*)this_ + 0x1E0) = 0;          // Reset timer/cooldown
        FUN_008f2cf0(*(int*)((char*)this_ - 0x2078)); // Set up next transition
        break;

    case 7:
        FUN_008f4650();  // Handle state 7 behavior
        break;

    case 8:
        FUN_008f1d80(2); // Trigger transition to state 2
        break;
    }

    // Note: The original code had a suspicious null pointer call here.
    // Likely a decompilation artifact of a debug assert or an inlined debug function.
    // It is omitted as it does not affect logic.
    return;
}