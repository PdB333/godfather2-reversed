// FUNC_NAME: AudioStream::updateStream
void __fastcall AudioStream::updateStream(int param_1)
{
    uint uVar1;
    int iVar2;
    uint uVar3;
    int iVar4;
    uint uVar5;
    float fVar6;

    // Check current state (0 = uninitialized, 1 = loading, 2 = playing)
    if (*(int *)(param_1 + 0xc4) == 0) // State == 0: Initialize from primary source
    {
        iVar2 = FUN_0084b430(*(uint *)(param_1 + 0x38)); // Get stream info from ID
        if (iVar2 == 0) goto LAB_006b622b;

        *(uint *)(param_1 + 0xc8) = *(uint *)(iVar2 + 4);   // +0xC8: some data
        *(uint *)(param_1 + 0x40) = *(uint *)(iVar2 + 8);   // +0x40: audio buffer handle
        *(uint *)(param_1 + 0x3c) = *(uint *)(iVar2 + 8);   // +0x3c: copy of same
        *(uint *)(param_1 + 0x48) = *(uint *)(iVar2 + 0xc); // +0x48: callback object
        *(uint *)(param_1 + 0xd0) = *(uint *)(iVar2 + 0x10); // +0xD0: extra data
        *(uint *)(param_1 + 0x60) = *(uint *)(iVar2 + 0x14); // +0x60: read size / duration
        uVar1 = *(uint *)(iVar2 + 0x18);                     // +0x18: sample count?
        *(uint *)(param_1 + 100) = uVar1;                    // +0x64: stored sample count
        uVar5 = *(uint *)(iVar2 + 0x1c);                     // +0x1c: another count
        if (uVar1 <= uVar5) {
            uVar5 = uVar1;
        }
        uVar1 = *(uint *)(param_1 + 0x60);                   // Read size
        if (uVar5 < uVar1) {
            *(uint *)(param_1 + 0x6c) = uVar1 - uVar5;      // +0x6c: decoded samples remaining
        }
        *(uint *)(param_1 + 0x58) = uVar1;                   // +0x58: total samples?
        uVar3 = *(uint *)(param_1 + 0x40);
        *(uint *)(param_1 + 0x54) = *(uint *)(iVar2 + 0x2c); // +0x54: sample rate or config
    }
    else
    {
        if ((*(int *)(param_1 + 0xc4) != 1) || // State != 1: maybe error
            (iVar2 = FUN_0084b400(*(uint *)(param_1 + 0x38)), iVar2 == 0)) goto LAB_006b622b;

        // State 1: Initialize from different source (streaming)
        *(uint *)(param_1 + 0x4c) = *(uint *)(iVar2 + 4);    // +0x4c: stream offset?
        *(uint *)(param_1 + 0xc8) = *(uint *)(iVar2 + 8);    // +0xC8: data
        *(uint *)(param_1 + 0x40) = *(uint *)(iVar2 + 0x10); // +0x40: buffer
        *(uint *)(param_1 + 0x3c) = *(uint *)(iVar2 + 0x10); // +0x3c: copy
        *(uint *)(param_1 + 0x48) = *(uint *)(iVar2 + 0x14); // +0x48: callback
        *(uint *)(param_1 + 0x60) = *(uint *)(iVar2 + 0x18); // +0x60: read size
        uVar1 = *(uint *)(iVar2 + 0x1c);                     // +0x1c: sample count
        *(uint *)(param_1 + 100) = uVar1;
        uVar5 = *(uint *)(iVar2 + 0x20);                     // +0x20: another count
        if (uVar1 <= uVar5) {
            uVar5 = uVar1;
        }
        uVar1 = *(uint *)(param_1 + 0x60);
        if (uVar5 < uVar1) {
            *(uint *)(param_1 + 0x6c) = uVar1 - uVar5;
        }
        *(uint *)(param_1 + 0x58) = uVar1;
        *(uint *)(param_1 + 0x54) = *(uint *)(iVar2 + 0x30); // +0x54: sample rate
        uVar3 = FUN_0084aea0(*(uint *)(iVar2 + 0xc));         // Allocate or register buffer
        *(uint *)(param_1 + 0xc0) = uVar3;
        FUN_0084aae0(param_1);                                // Setup decoder
        uVar3 = *(uint *)(param_1 + 0x40);
    }

    // Convert sample rate or time value to float
    fVar6 = (float)FUN_008c7750(uVar3);                        // Likely converts sample rate -> time
    *(float *)(param_1 + 0x80) = fVar6;                       // +0x80: time per sample unit

LAB_006b622b:
    FUN_006b1520(param_1);                                     // Check for completion or reset

    // Register callback if present
    if (*(int *)(param_1 + 0x48) != 0) {
        FUN_00849ee0(*(int *)(param_1 + 0x48), param_1);     // Register callback with this
    }

    // If buffer handle is valid
    if ((*(int *)(param_1 + 0x40) != 0) &&
        (iVar2 = FUN_008c74d0(*(int *)(param_1 + 0x40)), iVar2 != 0)) // Get decoder from buffer
    {
        FUN_008c4250(param_1);                                 // Decode/advance stream
        FUN_008c0b10(*(uint *)(param_1 + 0x38), uVar5, 1);    // Report progress (ID, count, flag)
        *(int *)(param_1 + 0x74) += *(int *)(param_1 + 0x60); // Accumulate samples read

        // Check global time threshold or flag
        if ((_DAT_00d577a0 < *(float *)(param_1 + 0x80)) ||
            ((*(uint *)(param_1 + 0x34) >> 0x1d & 1) != 0))   // Bit 29 of flags
        {
            FUN_006b2f70();                                    // Start playback
        }
        else
        {
            FUN_006b59f0();                                    // Stop/pause playback
        }

        // Calculate remaining time/delay
        if (*(uint *)(param_1 + 0x6c) < *(uint *)(param_1 + 0x68)) {
            iVar4 = *(uint *)(param_1 + 0x68) - *(uint *)(param_1 + 0x6c); // Delta
        } else {
            iVar4 = 0;
        }
        FUN_008be440(iVar4);                                   // Update playback position/delay

        FUN_006b59f0();                                        // Another playback control

        if (*(int *)(param_1 + 0xc4) == 2) {                  // State == 2 (playing)
            *(uint *)(iVar2 + 0x22c) = *(uint *)(param_1 + 0x38); // Store stream ID in decoder
        }
    }

    // Final check: if stream is not paused, buffer valid, and decoder not stopped
    if ((((*(byte *)(param_1 + 0x34) & 1) == 0) &&            // Bit 0 not set (not paused?)
         (*(int *)(param_1 + 0x40) != 0)) &&
        (iVar2 = FUN_008c74d0(*(int *)(param_1 + 0x40)), iVar2 != 0) &&
        ((~(byte)(*(uint *)(iVar2 + 0x84) >> 5) & 1) != 0))  // Decoder bit 5 not set (still active?)
    {
        FUN_006b5170();                                        // Handle meta data or continue
        return;
    }
    return;
}