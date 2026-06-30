// FUNC_NAME: DampingHelper::processDamping

void __fastcall DampingHelper::processDamping(uint count)
{
    // This function processes an array of elements (each 0xC0 bytes) containing 4 groups of float pairs.
    // Each group has a "current" value and a "previous" value (offset -16 from previous).
    // The operation: current = previous; previous *= decayFactor (passed in XMM1 register).
    // The base pointer (this) is passed in EAX.

    int remaining = count - 1;
    if (count > 3)
    {
        count = count >> 2;
        remaining += count * -4;
        do
        {
            // Process 4 groups at once (unrolled for speed)
            // Group 0
            *(float *)(in_EAX + 0xC) = *(float *)(in_EAX + 0x1C);
            *(float *)(in_EAX + 0x1C) = *(float *)(in_EAX + 0x1C) * in_XMM1_Da;
            // Group 1
            *(float *)(in_EAX + 0x3C) = *(float *)(in_EAX + 0x4C);
            *(float *)(in_EAX + 0x4C) = *(float *)(in_EAX + 0x4C) * in_XMM1_Da;
            // Group 2
            *(float *)(in_EAX + 0x6C) = *(float *)(in_EAX + 0x7C);
            *(float *)(in_EAX + 0x7C) = *(float *)(in_EAX + 0x7C) * in_XMM1_Da;
            // Group 3
            *(float *)(in_EAX + 0x9C) = *(float *)(in_EAX + 0xAC);
            *(float *)(in_EAX + 0xAC) = *(float *)(in_EAX + 0xAC) * in_XMM1_Da;

            in_EAX += 0xC0; // Advance to next element
            count--;
        } while (count != 0);
    }

    // Process remaining groups (0 to 3)
    if (remaining >= 0)
    {
        float *pPrev = (float *)(in_EAX + 0x1C);
        do
        {
            pPrev[-4] = *pPrev;        // current = previous
            *pPrev = *pPrev * in_XMM1_Da; // previous *= decay
            pPrev += 0xC; // Move to next group's previous (0xC * sizeof(float) = 0x30 bytes)
            remaining--;
        } while (remaining >= 0);
    }
}