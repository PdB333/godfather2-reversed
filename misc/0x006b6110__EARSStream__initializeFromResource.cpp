// FUNC_NAME: EARSStream::initializeFromResource

void __thiscall EARSStream::initializeFromResource(int thisPtr) // thisPtr is 'this'
{
    uint stateType; // *(thisPtr + 0xc4) - stream type (0,1,2)
    int resourceData;
    int devicePtr;
    uint sizeA;
    uint sizeB;
    float volume;

    stateType = *(uint *)(thisPtr + 0xc4); // offset +0xC4: stream state/type

    if (stateType == 0) {
        // Load from first resource type
        resourceData = FUN_0084b430(*(int *)(thisPtr + 0x38)); // offset +0x38: resource handle
        if (resourceData == 0) goto LAB_006b622b;
        *(int *)(thisPtr + 200) = *(int *)(resourceData + 4);   // offset +0xC8: some pointer
        *(int *)(thisPtr + 0x40) = *(int *)(resourceData + 8);  // offset +0x40: wave data ptr
        *(int *)(thisPtr + 0x3c) = *(int *)(resourceData + 8);  // offset +0x3C: same
        *(int *)(thisPtr + 0x48) = *(int *)(resourceData + 0xc);// offset +0x48: format info
        *(int *)(thisPtr + 0xd0) = *(int *)(resourceData + 0x10); // offset +0xD0: additional data
        *(int *)(thisPtr + 0x60) = *(int *)(resourceData + 0x14); // offset +0x60: total size
        sizeA = *(uint *)(resourceData + 0x18);                 // offset +0x64: some size
        *(uint *)(thisPtr + 100) = sizeA;
        sizeB = *(uint *)(resourceData + 0x1c);                 // offset +0x1C: block size?
        if (sizeA <= sizeB) {
            sizeB = sizeA;
        }
        // Ensure we don't exceed total size
        if (sizeB < *(uint *)(thisPtr + 0x60)) {
            *(uint *)(thisPtr + 0x6c) = *(uint *)(thisPtr + 0x60) - sizeB; // offset +0x6C: remaining
        }
        *(uint *)(thisPtr + 0x58) = *(uint *)(thisPtr + 0x60); // offset +0x58: current offset?
        *(int *)(thisPtr + 0x54) = *(int *)(resourceData + 0x2c); // offset +0x54: sample rate?
    }
    else if (stateType == 1) {
        // Load from second resource type (e.g., compressed)
        resourceData = FUN_0084b400(*(int *)(thisPtr + 0x38)); // offset +0x38: resource handle
        if (resourceData == 0) goto LAB_006b622b;
        *(int *)(thisPtr + 0x4c) = *(int *)(resourceData + 4);   // offset +0x4C: some data
        *(int *)(thisPtr + 200) = *(int *)(resourceData + 8);    // offset +0xC8: pointer
        *(int *)(thisPtr + 0x40) = *(int *)(resourceData + 0x10); // offset +0x40: wave data ptr
        *(int *)(thisPtr + 0x3c) = *(int *)(resourceData + 0x10); // offset +0x3C: same
        *(int *)(thisPtr + 0x48) = *(int *)(resourceData + 0x14); // offset +0x48: format info
        *(int *)(thisPtr + 0x60) = *(int *)(resourceData + 0x18); // offset +0x60: total size
        sizeA = *(uint *)(resourceData + 0x1c);                 // offset +0x1C: size
        *(uint *)(thisPtr + 100) = sizeA;
        sizeB = *(uint *)(resourceData + 0x20);                 // offset +0x20: block size
        if (sizeA <= sizeB) {
            sizeB = sizeA;
        }
        if (sizeB < *(uint *)(thisPtr + 0x60)) {
            *(uint *)(thisPtr + 0x6c) = *(uint *)(thisPtr + 0x60) - sizeB;
        }
        *(uint *)(thisPtr + 0x58) = *(uint *)(thisPtr + 0x60);
        *(int *)(thisPtr + 0x54) = *(int *)(resourceData + 0x30); // offset +0x54: sample rate?
        // Call function to set up additional data (e.g., decompression?)
        *(int *)(thisPtr + 0xc0) = FUN_0084aea0(*(int *)(resourceData + 0xc)); // offset +0xC0: context ptr
        FUN_0084aae0(thisPtr);
    }

    // Compute volume based on some formula
    volume = (float)FUN_008c7750(*(int *)(thisPtr + 0x40)); // convert to float, maybe distance
    *(float *)(thisPtr + 0x80) = volume; // offset +0x80: volume/attenuation

LAB_006b622b:
    FUN_006b1520(thisPtr); // Prepare stream for playback

    if (*(int *)(thisPtr + 0x48) != 0) {
        FUN_00849ee0(*(int *)(thisPtr + 0x48), thisPtr); // Set callback or register format
    }

    if ((*(int *)(thisPtr + 0x40) != 0) &&
        (devicePtr = FUN_008c74d0(*(int *)(thisPtr + 0x40)), devicePtr != 0)) {
        FUN_008c4250(thisPtr); // Initialize audio device (e.g., create buffer)
        FUN_008c0b10(*(int *)(thisPtr + 0x38), sizeB, 1); // Update resource consumption
        *(int *)(thisPtr + 0x74) += *(int *)(thisPtr + 0x60); // offset +0x74: accumulated position?

        // Check global volume threshold or user override
        if ((_DAT_00d577a0 < *(float *)(thisPtr + 0x80)) ||
            ((*(uint *)(thisPtr + 0x34) >> 0x1d & 1) != 0)) { // bit 29 of flags
            FUN_006b2f70(); // Play normally
        } else {
            FUN_006b59f0(); // Play with low volume or silence?
        }

        // Compute seek amount based on difference between position and remaining
        int seekAmount;
        if (*(uint *)(thisPtr + 0x6c) < *(uint *)(thisPtr + 0x68)) {
            seekAmount = *(uint *)(thisPtr + 0x68) - *(uint *)(thisPtr + 0x6c);
        } else {
            seekAmount = 0;
        }
        FUN_008be440(seekAmount); // Seek to position
        FUN_006b59f0(); // Play again?

        if (*(int *)(thisPtr + 0xc4) == 2) {
            *(int *)(devicePtr + 0x22c) = *(int *)(thisPtr + 0x38); // Store resource handle in device
        }
    }

    // Check if stream should be stopped or looped
    if ((((*(byte *)(thisPtr + 0x34) & 1) == 0) && // bit 0 clear (no loop?)
         (*(int *)(thisPtr + 0x40) != 0)) &&
        (devicePtr = FUN_008c74d0(*(int *)(thisPtr + 0x40)), devicePtr != 0) &&
        ((~((*(uint *)(devicePtr + 0x84) >> 5) & 1) & 1) != 0)) { // bit 5 clear
        FUN_006b5170(); // Stop or pause the stream
    }
    return;
}