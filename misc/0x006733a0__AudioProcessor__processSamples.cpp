// FUNC_NAME: AudioProcessor::ProcessSamples
// Address: 0x006733a0
// Role: Processes an array of 16-bit input samples into 32-bit output samples
//       with three modes: scale+shift, scale+divide, or random noise.
//       The processing parameters are obtained from a structure pointed by EAX (this).
//       EDI contains the number of samples to process (count).

void AudioProcessor::ProcessSamples(short* pInput, int* pOutput, int count)
{
    // Structure layout (offsets from this pointer):
    // +0x00: short scaleFactor   (sVar2)
    // +0x02: short shiftAmount   (used in mode 0)
    // +0x04: int   additiveValue  (iVar6, used in mode 0 and 1)
    // +0x10: short mode          (0, 1, or 2)
    // +0x08: int   divisor        (iVar4, used in mode 1)
    // Note: Offsets are based on the decompiled pointer arithmetic.

    short* pParams = this; // in_EAX

    short scaleFactor = pParams[0];               // *in_EAX
    short mode       = pParams[8];               // in_EAX[8]
    int   additive   = *(int*)(pParams + 4);      // int at offset +0x08 (byte offset 8)
    int   divisor    = *(int*)(pParams + 2);      // int at offset +0x04 (byte offset 4)

    if (mode == 0)
    {
        short shiftAmount = pParams[1];            // in_EAX[1]
        for (int i = 0; i < count; i++)
        {
            int sample = (int)pInput[i] * (int)scaleFactor;
            sample = (sample + additive) >> (shiftAmount & 0x1f);
            pOutput[i] = sample;
        }
    }
    else if (mode == 1)
    {
        for (int i = 0; i < count; i++)
        {
            int sample = (int)pInput[i] * (int)scaleFactor;
            if (sample < 0)
            {
                // Negative rounding (away from zero)
                sample = -((additive - sample) / divisor);
            }
            else
            {
                sample = (sample + additive) / divisor;
            }
            pOutput[i] = sample;
        }
    }
    else if (mode == 2)
    {
        // Random noise generation
        for (int i = 0; i < count; i++)
        {
            pOutput[i] = FUN_00676010(); // RNG call
        }
    }
}