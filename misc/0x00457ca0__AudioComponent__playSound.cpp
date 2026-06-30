// FUNC_NAME: AudioComponent::playSound
void __thiscall AudioComponent::playSound(void)
{
    float fVar1;
    int iVar2;
    double dVar3;
    int thisPtr;
    int iVar4;
    uint uVar5;
    SoundParams params; // local_4c, 8 bytes (could be position or ID)
    double duration; // local_44
    double volume; // local_3c
    char *soundName; // local_34
    int pSoundData; // local_2c
    uint flags; // local_24
    uint extraFlags; // local_1c, initialized to 0xfab591a1 (some bitmask)
    uint enableFlag; // local_14, initialized to 0

    thisPtr = in_EAX;
    iVar2 = *(int *)(thisPtr + 0x14); // +0x14: pointer to inner data/state
    
    // Check if sound can be played based on state bytes at +0x1e0 and +0x1e3
    if ((*(byte *)(iVar2 + 0x1e0) > 3) ||
        ((*(byte *)(iVar2 + 0x1e0) != 1 && (*(byte *)(iVar2 + 0x1e3) > 8)))) {
        *(byte *)(iVar2 + 0x200) = 1; // +0x200: flag indicating sound was suppressed
        return;
    }
    
    // Start sound preparation: pass global sound system, type index from vtable at +0x10, slot 5, and output params
    FUN_00c9cbe0(DAT_01143360,                         // global sound system
                 *(int *)(**(int **)(iVar2 + 0x10) + 0x10), // sound type from vtable
                 5,                                    // slot/channel index
                 &params);                             // output params struct
    
    // Duration: convert int at +0x1e8 to double (tick count or time value)
    duration = (double)*(int *)(iVar2 + 0x1e8);
    pSoundData = iVar2 + 0x1f0; // +0x1f0: pointer to sound data block
    enableFlag = 0;
    if (*(int *)(iVar2 + 0x1e8) < 0) {
        duration = duration + _DAT_00e44708; // add some constant (maybe 2^? for negative handling)
    }
    
    // Sound name string: use pointer at +0x138, fallback to default "DAT_0120546e" (likely empty string)
    soundName = *(char **)(iVar2 + 0x138);
    if (soundName == (char *)0x0) {
        soundName = &DAT_0120546e;
    }
    
    // Params: copy 8 bytes from +0x100 (probably a position vector)
    params = *(SoundParams *)(iVar2 + 0x100);
    extraFlags = 0xfab591a1; // some flag mask
    
    // Determine flags based on movement or action state at +0x1d8 and +0x1dc
    if (*(int *)(iVar2 + 0x1d8) == 0 && *(int *)(iVar2 + 0x1dc) == 0) {
        flags = 0;
    } else {
        flags = *(uint *)(iVar2 + 0x1cc); // +0x1cc: action/flags data
    }
    
    // Compute volume parameter (local_3c) based on several fields
    if (((*(int *)(iVar2 + 0x1dc) != 0) || (*(int *)(iVar2 + 0x1d8) != 0)) &&
        (*(char *)(iVar2 + 0x15c) != '\0')) {
        fVar1 = *(float *)(iVar2 + 0x160); // +0x160: some float parameter
        if (fVar1 == 0.0) {
            // Use random time if fVar1 is zero
            FUN_00427180(); // maybe random seed or setup
            iVar4 = FUN_00b9a1c0(); // random integer
            volume = (double)iVar4 * DAT_00e446c8; // DAT_00e446c8: multiplier to convert to time/volume
            goto LAB_00457dfd;
        }
        if (0.0 < fVar1) {
            // Use fVar1 directly
            volume = (double)fVar1;
            goto LAB_00457dfd;
        }
        // Negative fVar1: combine with int at +0x1e4
        dVar3 = (double)*(int *)(iVar2 + 0x1e4);
        if (*(int *)(iVar2 + 0x1e4) < 0) {
            dVar3 = dVar3 + _DAT_00e44708;
        }
        volume = dVar3 * DAT_00e446c8 + (double)fVar1;
        if (0.0 <= volume) goto LAB_00457dfd;
    }
    // Default volume
    volume = 0.0;
    
LAB_00457dfd:
    // Finalize sound parameters
    FUN_00c9eac0();                // begin sound engine command batch
    FUN_00c9cd40(5, &params);     // send finalized params to slot 5
    uVar5 = FUN_00c9eb20();       // obtain sound handle
    *(uint *)(iVar2 + 0x164) = uVar5;  // +0x164: sound handle
    FUN_00c9eae0();               // end sound engine command batch
    
    // Set result state fields
    *(uint *)(iVar2 + 0x158) = enableFlag; // +0x158: enable flag (0)
    *(uint *)(iVar2 + 0x16c) = 1;          // +0x16c: active flag (1)
    *(uint *)(iVar2 + 0x168) = 0;          // +0x168: loop flag (0)
    
    return;
}