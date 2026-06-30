// FUNC_NAME: AnimationClip::advance
int __thiscall AnimationClip::advance(int thisPtr, float deltaTime)
{
    int animData; // pointer to animation data structure
    float currentTime; // current time in the clip
    float temp1, temp2, temp3; // temporary interpolation values
    float resultValue; // computed result value
    float xValue, yValue; // computed X and Y values
    float invDuration1, invDuration2; // inverse durations

    // Update current time
    currentTime = *(float *)(thisPtr + 0x14) + deltaTime;
    animData = *(int *)(thisPtr + 0x10); // pointer to animation data (e.g., AnimData)
    *(float *)(thisPtr + 0x14) = currentTime;

    // Check if current time is within the clip duration
    if (currentTime < *(float *)(animData + 0x6c)) // duration
    {
        // Compute interpolation result
        temp1 = *(float *)(animData + 0x94); // some threshold or base value
        temp2 = currentTime * *(float *)(animData + 0x88) + *(float *)(animData + 0x84); // linear interpolation
        temp3 = currentTime * *(float *)(animData + 0x90) + *(float *)(animData + 0x8c); // linear interpolation
        if (temp2 < temp3)
        {
            temp3 = temp2;
        }
        if (temp1 <= temp3)
        {
            resultValue = temp3;
            if (*(float *)(animData + 0x98) < temp3) // another threshold
            {
                resultValue = *(float *)(animData + 0x98);
            }
        }
        else
        {
            resultValue = temp1;
        }
        *(float *)(thisPtr + 0x18) = resultValue; // store computed value

        // Compute X and Y values (possibly position or scale)
        xValue = *(float *)(animData + 0x54) * currentTime;
        yValue = *(float *)(animData + 0x58) * currentTime;
        *(float *)(thisPtr + 0x28) = xValue;
        *(float *)(thisPtr + 0x2c) = yValue;

        // Check flag at offset +0x44 bit 0x2000 (e.g., looping flag)
        if ((*(unsigned short *)(animData + 0x44) & 0x2000) == 0)
        {
            // Apply fractional part and multiplier
            *(float *)(thisPtr + 0x28) =
                (float)(int)((xValue - (float)(int)xValue) * *(float *)(animData + 0x4c)) *
                *(float *)(animData + 0xb0);
            *(float *)(thisPtr + 0x2c) =
                (float)(int)((yValue - (float)(int)yValue) * *(float *)(animData + 0x50)) *
                *(float *)(animData + 0xb4);
        }

        // Compute inverse durations (clamped to 1.0)
        temp1 = *(float *)(animData + 100) * currentTime + *(float *)(animData + 0x5c); // 100 = 0x64
        temp2 = *(float *)(animData + 0x68) * currentTime + *(float *)(animData + 0x60);
        if ((double)temp1 < 0.0) // DAT_00e446c8 is 0.0
        {
            temp1 = 1.0f; // DAT_00e2e210 is 1.0
        }
        if ((double)temp2 < 0.0)
        {
            temp2 = 1.0f;
        }
        invDuration1 = 1.0f / temp1; // DAT_00e2b1a4 is 1.0
        invDuration2 = 1.0f / temp2;
        *(float *)(thisPtr + 0x30) = invDuration1;
        *(float *)(thisPtr + 0x34) = invDuration2;

        // Return success: preserve high 24 bits of animData pointer, set low byte to 1
        return (animData & 0xFFFFFF00) | 1;
    }
    else
    {
        // Return failure: preserve high 24 bits, low byte zero
        return (animData & 0xFFFFFF00);
    }
}