// FUNC_NAME: Animated::crossfadeAnimations

// Address: 0x00601a00
// Role: Crossfades between two animation slots identified by indices.
// Accesses an array of AnimSlot structs at this+0x70 (each entry 0xC bytes: id, unknown, data).
// Checks that both slots are active and have different IDs, then performs blend.

// Forward declarations of internal functions (addresses based on decompiled references)
bool setActiveAnim(int animId, int animData);      // 0x005f5c20
int evaluateBlend(int animData, char* blendBuffer); // 0x005f5f20, blendBuffer is 12 bytes
void finalizeBlend();                               // 0x005f5bb0

int __thiscall Animated::crossfadeAnimations(int thisPtr, int* pSourceSlotIdx, int* pTargetSlotIdx)
{
    // Each AnimSlot struct is 0xC (12) bytes
    // Offsets: +0x00: id (int), +0x04: unknown, +0x08: data (int)
    int* sourceSlot = (int*)(thisPtr + 0x70 + *pSourceSlotIdx * 0xC);
    int srcId = *sourceSlot;
    int srcData = sourceSlot[2];   // +0x08

    int result = 0;
    if (srcId != 0)
    {
        int* targetSlot = (int*)(thisPtr + 0x70 + *pTargetSlotIdx * 0xC);
        int tgtId = *targetSlot;
        if (tgtId != 0)
        {
            int tgtData = targetSlot[2];
            if (tgtData != 0 && tgtId != srcId)
            {
                // Start the target animation
                setActiveAnim(tgtId, tgtData);

                char blendBuffer[12]; // used by evaluateBlend
                result = evaluateBlend(srcData, blendBuffer);

                finalizeBlend();
            }
        }
    }
    return result;
}