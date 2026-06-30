// FUNC_NAME: encodeSignFlags
void __fastcall encodeSignFlags(float* data) // this pointer in EAX
{
    float* const input0 = &data[0];   // +0x00: first vector
    float* const input1 = &data[4];   // +0x10: second vector
    float* const input2 = &data[8];   // +0x20: third vector
    float* const input3 = &data[12];  // +0x30: fourth vector
    float* const input4 = &data[16];  // +0x40: fifth vector
    float* const input5 = &data[20];  // +0x50: sixth vector

    // Output fields (each set produces two floats)
    float* const out0a = &data[25];   // +0x64
    float* const out0b = &data[26];   // +0x68
    float* const out1a = &data[27];   // +0x6c
    float* const out1b = &data[28];   // +0x70
    float* const out2a = &data[29];   // +0x74
    float* const out2b = &data[30];   // +0x78
    float* const out3a = &data[31];   // +0x7c
    float* const out3b = &data[32];   // +0x80
    float* const out4a = &data[33];   // +0x84
    float* const out4b = &data[34];   // +0x88
    float* const out5a = &data[35];   // +0x8c
    float* const out5b = &data[36];   // +0x90

    // Process first set (input0[0..2])
    {
        uint bitsPos = 0;
        uint bitsNeg = 0;
        // Component X
        if (input0[0] >= 0.0f)
            bitsPos = 1;
        else
            bitsNeg = 1;
        // Component Y
        if (input0[1] >= 0.0f)
            bitsPos |= 2;
        else
            bitsNeg |= 2;
        // Component Z
        if (input0[2] >= 0.0f)
            bitsPos |= 1;
        else
            bitsNeg |= 1;
        *out0a = *reinterpret_cast<float*>(&bitsPos);
        *out0b = *reinterpret_cast<float*>(&bitsNeg);
    }

    // Process second set (input1[0..2])
    {
        uint bitsPos = 0;
        uint bitsNeg = 0;
        if (input1[0] >= 0.0f)
            bitsPos = 1;
        else
            bitsNeg = 1;
        if (input1[1] >= 0.0f)
            bitsPos |= 2;
        else
            bitsNeg |= 2;
        if (input1[2] >= 0.0f)
            bitsPos |= 1;
        else
            bitsNeg |= 1;
        *out1a = *reinterpret_cast<float*>(&bitsPos);
        *out1b = *reinterpret_cast<float*>(&bitsNeg);
    }

    // Process third set (input2[0..2])
    {
        uint bitsPos = 0;
        uint bitsNeg = 0;
        if (input2[0] >= 0.0f)
            bitsPos = 1;
        else
            bitsNeg = 1;
        if (input2[1] >= 0.0f)
            bitsPos |= 2;
        else
            bitsNeg |= 2;
        if (input2[2] >= 0.0f)
            bitsPos |= 1;
        else
            bitsNeg |= 1;
        *out2a = *reinterpret_cast<float*>(&bitsPos);
        *out2b = *reinterpret_cast<float*>(&bitsNeg);
    }

    // Process fourth set (input3[0..2])
    {
        uint bitsPos = 0;
        uint bitsNeg = 0;
        if (input3[0] >= 0.0f)
            bitsPos = 1;
        else
            bitsNeg = 1;
        if (input3[1] >= 0.0f)
            bitsPos |= 2;
        else
            bitsNeg |= 2;
        if (input3[2] >= 0.0f)
            bitsPos |= 1;
        else
            bitsNeg |= 1;
        *out3a = *reinterpret_cast<float*>(&bitsPos);
        *out3b = *reinterpret_cast<float*>(&bitsNeg);
    }

    // Process fifth set (input4[0..2])
    {
        uint bitsPos = 0;
        uint bitsNeg = 0;
        if (input4[0] >= 0.0f)
            bitsPos = 1;
        else
            bitsNeg = 1;
        if (input4[1] >= 0.0f)
            bitsPos |= 2;
        else
            bitsNeg |= 2;
        if (input4[2] >= 0.0f)
            bitsPos |= 1;
        else
            bitsNeg |= 1;
        *out4a = *reinterpret_cast<float*>(&bitsPos);
        *out4b = *reinterpret_cast<float*>(&bitsNeg);
    }

    // Process sixth set (input5[0..2]) – note: different condition for Z component
    {
        uint bitsPos = 0;
        uint bitsNeg = 0;
        if (input5[0] >= 0.0f)
            bitsPos = 1;
        else
            bitsNeg = 1;
        if (input5[1] >= 0.0f)
            bitsPos |= 2;
        else
            bitsNeg |= 2;
        if (input5[2] < 0.0f)       // special case: negative only (excluding zero)
            bitsNeg |= 1;
        else
            bitsPos |= 1;            // non-negative (including zero)
        *out5a = *reinterpret_cast<float*>(&bitsPos);
        *out5b = *reinterpret_cast<float*>(&bitsNeg);
    }
}