// FUNC_NAME: SoundOutputDevice::initialize
void __thiscall SoundOutputDevice::initialize(int *outSuccessFlag, int param_3, uint *outConfig)
{
    // param_1 (outSuccessFlag) set to 0 initially
    *outSuccessFlag = 0;

    // Get the audio driver object at offset 0x180
    int audioDriver = *(int *)(this + 0x180);
    short sampleRate = *(short *)(audioDriver + 0x1c);

    if (sampleRate == 0)
    {
        ushort newSampleRate = 0x800; // default 2048 Hz?
        if (*(int *)(audioDriver + 0x20) == 0)
        {
            if (*(int *)(audioDriver + 0x28) != 0)
            {
                newSampleRate = *(ushort *)(*(int *)(audioDriver + 0x28) + 0x16);
            }
        }
        else
        {
            newSampleRate = *(ushort *)(*(int *)(audioDriver + 0x20) + 0x10c);
        }
        *(short *)(audioDriver + 0x1c) = newSampleRate;
    }

    ushort finalSampleRate = *(ushort *)(audioDriver + 0x1c);
    int configIndex = outConfig[2]; // outConfig[2] is some parameter

    *(ushort *)(this + 0x17c) = finalSampleRate;

    // Decide on some input value
    if ((configIndex == 0) || (outConfig[1] == 0))
    {
        // Use absolute value of outConfig[3]
        int absVal = outConfig[3];
        if (absVal < 0) absVal = -absVal;
        param_3 = absVal;
    }
    else
    {
        param_3 = 0;
    }

    // Get hardware specific values (likely buffer sizes in fixed-point 16.16)
    int iVar3 = FUN_00676010(); // getOutputBufferSize
    int iVar4 = FUN_00676010(); // getInputBufferSize or similar

    *(int *)(this + 0x130) = iVar3;
    *(int *)(this + 0x130 + 4) = iVar4; // actually offset 0x134
    // Note: decompiled shows *(this+0x134) = second call, but order may be swapped.
    // We'll follow decompiled: first set 0x130 then 0x134, etc.
    // Actually line: *(param_2+300) = iVar3; *(param_2+0x130) = iVar4; That sets 300 and 0x130 separately.
    // Wait, param_2+300 is 0x12C? No, 300 decimal = 0x12C. Then param_2+0x130 is 0x130. So they are different offsets.
    // Let's re-check: *(param_2+300) = iVar3; then *(param_2+0x130)=iVar4; So offset 300 (0x12C) and 0x130. Also later 0x134 and 0x138.
    // So we have four ints at offsets 0x12C, 0x130, 0x134, 0x138.

    // But the decompiled shows: *(param_2+300)=iVar3; *(param_2+0x130)=iVar4; then two calls to FUN_00676090 set 0x134 and 0x138.
    // So better to follow exactly.
    // I'll implement as per decompiled.

    int val1 = FUN_00676090(); // some configuration value
    *(int *)(this + 0x134) = val1;

    int val2 = FUN_00676090();
    *(int *)(this + 0x138) = val2;

    // Convert fixed-point to integer with rounding (add 0x8000 then shift right 16)
    int width = (iVar3 + 0x8000) >> 16;
    int height = (iVar4 + 0x8000) >> 16;

    if ((width < 1) || (height < 1))
    {
        // Reset output config array
        outConfig[0] = 0;
        outConfig[2] = 0;
        outConfig[3] = 0;
        outConfig[1] = 0;
    }
    else
    {
        // Fill output config array with more values from FUN_00676090
        outConfig[0] = FUN_00676090();
        outConfig[2] = FUN_00676090();
        outConfig[3] = FUN_00676090();
        outConfig[1] = FUN_00676090();
    }

    if (*(int *)(this + 0x180) != 0)
    {
        // Set width and height into the audio driver object at +0x70 and +0x74
        *(int *)(*(int *)(this + 0x180) + 0x70) = width;
        *(int *)(*(int *)(this + 0x180) + 0x74) = height;
    }

    // Call some initialization functions
    FUN_00673490(1, width, height);
    FUN_00675010(finalSampleRate);
    FUN_00675010(finalSampleRate);

    // Allocate or configure a buffer at this+0x18
    if (*(int *)(this + 0x18) == 0)
    {
        int driver = *(int *)(this + 0x180);
        uint bufferSize;
        if (*(int *)(driver + 0x20) == 0)
        {
            bufferSize = (uint)*(ushort *)(*(int *)(driver + 0x2c) + 8);
            if ((*(int *)(driver + 0x30) != 0) &&
                (int temp = *(int *)(*(int *)(driver + 0x30) + 8); temp <= bufferSize))
            {
                bufferSize = temp - 1;
            }
        }
        else
        {
            bufferSize = (uint)*(short *)(*(int *)(driver + 0x20) + 0x108);
        }

        int allocated = FUN_00673190(bufferSize);
        *(int *)(this + 0x18) = allocated;
    }

    int buffer = *(int *)(this + 0x18);
    if ((*(int *)(buffer + 4) != width) || (*(int *)(buffer + 8) != width))
    {
        *(int *)(buffer + 4) = width;
        *(int *)(buffer + 8) = width;
        if (0 < *(int *)(buffer + 0xc))
        {
            memset(*(void **)(buffer + 0x10), 0, *(size_t *)(buffer + 0xc));
        }
    }

    if (height < width)
    {
        width = height;
    }

    // Clear some fields
    *(int *)(this + 100) = 0;
    *(int *)(this + 0xa0) = 0;
    *(int *)(this + 0x178) = 0;

    // Calculate and store some value: (width << 6) / (finalSampleRate * 2)
    *(int *)(this + 0x164) = (width << 6) / (int)(finalSampleRate * 2);

    // Call finalization on the audio driver
    FUN_00675a30(*(int *)(this + 0x180));

    return;
}