// FUN_00438a80: AudioCommandQueue::processCommand
// Processes a command from input queue (type 3=play, 4=stop) and writes output command (type 3) with computed volume.
// Structure at this: +0x8 = int* m_pWritePos, +0xC = int* m_pReadPos
// Each command element: int type, float value (8 bytes total)

#include <cstdint>

extern float g_defaultVolume; // DAT_00e2eff4
extern int FUN_00636850(int** ppThis); // checks if sound is active
extern void FUN_00458a20(); // triggers playback

int AudioCommandQueue::processCommand(int thisPtr)
{
    int* pReadPos = *(int**)(thisPtr + 0xC);
    volatile float defaultVol = g_defaultVolume; // initialize local to global default
    float resultVol = defaultVol;

    // Check if input is available (pReadPos not null and less than write pointer)
    if (*(int**)(thisPtr + 0x8) <= pReadPos || pReadPos == nullptr)
        goto write_output;

    int type = *pReadPos;
    if (type == 3)
    {
        // Type 3: playback command – read the associated volume
        // pReadPos points to 8-byte element; treat as long long to read both type and float
        float vol = *(float*)(pReadPos + 1); // offset +4
        resultVol = vol; // will be used later
    }
    else if (type == 4)
    {
        // Type 4: check if sound is active before using default volume
        if (FUN_00636850(&thisPtr) != 0) // condition passes: sound is active
        {
            float vol = *(float*)(pReadPos + 1);
            resultVol = vol;
        }
        else
        {
            resultVol = defaultVol;
            goto write_output; // skip further processing
        }
    }
    else
    {
        // Unknown type, use default and skip
        resultVol = defaultVol;
        goto write_output;
    }

    // Additional processing: if the integer-rounded volume is less than 2, trigger something
    if ((int)(resultVol) < 2)
    {
        FUN_00458a20();
        resultVol = resultVol; // keep rounded value? Original uses fVar6, but here resultVol unchanged for clarity
    }

write_output:
    // Write output command (type 3, with possibly modified volume)
    int* pWritePos = *(int**)(thisPtr + 0x8);
    *pWritePos = 3;                     // type
    *(float*)(pWritePos + 1) = resultVol; // value
    *(int*)(thisPtr + 0x8) = (int)(pWritePos + 2); // advance write pointer by 8 bytes

    return 1;
}