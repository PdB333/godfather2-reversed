// FUNC_NAME: StatefulDataCopy
// Function address: 0x00585400
// Role: Copies 32 bytes of data from one of two source structures to a destination structure, based on a state byte at offset 0.
// The structure layout: [byte state, 3 bytes padding, 8 dwords (32 bytes) of data]
// If the active source (pActive) has state == 2, and the new source (pNew) does not, then data is copied from active and destination state set to 2.
// If both have state != 2, destination state is set to 0 and no copy occurs.
// Otherwise (active state != 2 but new state == 2, or both == 2), data is copied from new source and destination state set to 2.

#include <cstdint>

// Assumes __fastcall with pNew as the explicit parameter (stack/EDX), pDest in EAX, pActive in ESI.
// The original decompiler signature was degraded; we reconstruct with three explicit pointers.
void __fastcall StatefulDataCopy(uint32_t* pNew, uint32_t* pDest, uint32_t* pActive)
// pNew: pointer to new source structure (byte state at offset 0, data at offset 4)
// pDest: pointer to destination structure (same layout)
// pActive: pointer to active source structure (same layout)
{
    uint32_t* srcData;
    uint32_t* dstData;

    uint8_t activeState = *(uint8_t*)pActive;
    uint8_t newState = *(uint8_t*)pNew;

    if (activeState == 2)
    {
        if (newState != 2)
        {
            *(uint8_t*)pDest = 2;
            srcData = (uint32_t*)((uint8_t*)pActive + 4); // +0x04
            goto copyData;
        }
    }
    else // activeState != 2
    {
        if (newState != 2)
        {
            *(uint8_t*)pDest = 0;
            return;
        }
    }

    // Both are 2, or active !=2 and new ==2
    srcData = (uint32_t*)((uint8_t*)pNew + 4); // +0x04
    *(uint8_t*)pDest = 2;

copyData:
    dstData = (uint32_t*)((uint8_t*)pDest + 4); // +0x04
    // Copy 8 dwords (32 bytes)
    dstData[0] = srcData[0];
    dstData[1] = srcData[1];
    dstData[2] = srcData[2];
    dstData[3] = srcData[3];
    dstData[4] = srcData[4];
    dstData[5] = srcData[5];
    dstData[6] = srcData[6];
    dstData[7] = srcData[7];
}