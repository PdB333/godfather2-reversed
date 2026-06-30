// FUNC_NAME: UpdateObjectDeltas
// Function address: 0x0041bf60
// Role: Updates two global objects (characters? cameras?) with new current values and computes deltas from a base value (DAT_00e2b1a4).
// If the object matches the player object (DAT_012058e8) and has a valid event handler, it calls a notification function (sub_60add0).

void __fastcall UpdateObjectDeltas(float fCurrentA /* passed in XMM1 */, float fCurrentB, float fCurrentC, float fCurrentD)
{
    // Global variables:
    // DAT_01206a3c - pointer to first object (e.g., g_pCharacter1)
    // DAT_01206a58 - pointer to second object (e.g., g_pCharacter2)
    // DAT_00e2b1a4 - base float value (e.g., some reference angle or position)
    // DAT_012058e8 - pointer to the player object (g_pPlayer)
    // DAT_0120fa60, DAT_0120f840 - static data addresses

    float fBase = DAT_00e2b1a4;  // base reference

    // First object (pointed by g_pCharacter1)
    int* pObj1 = (int*)DAT_01206a3c;
    float* pfDelta1 = (float*)(pObj1 + 0x1f0 / 4); // offset +0x1f0
    *pfDelta1 = fBase - fCurrentA;                       // store delta
    *(float*)(pObj1 + 500 / 4) = fBase - fCurrentB;      // offset 500 = 0x1f4
    *(float*)(pObj1 + 0x1f8 / 4) = fCurrentA;            // store current values
    *(float*)(pObj1 + 0x1fc / 4) = fCurrentB;

    // If this object is the player and has an event handler (pointer at +0x1e8)
    if ((DAT_012058e8 == (int)pObj1) && (*(int*)(pObj1 + 0x1e8 / 4) != 0))
    {
        // Notify with object ID (+0x14), event handler (+0x1e8), and delta pointer
        sub_60add0(*(int*)(pObj1 + 0x14 / 4), *(int*)(pObj1 + 0x1e8 / 4), pfDelta1);
        fBase = DAT_00e2b1a4; // reload base after call (might have been modified?)
    }

    // Second object (pointed by g_pCharacter2)
    int* pObj2 = (int*)DAT_01206a58;
    float* pfDelta2 = (float*)(pObj2 + 0x2a0 / 4); // offset +0x2a0
    *pfDelta2 = fBase - fCurrentC;                       // store delta
    *(float*)(pObj2 + 0x2a4 / 4) = fBase - fCurrentD;
    *(float*)(pObj2 + 0x2a8 / 4) = fCurrentC;
    *(float*)(pObj2 + 0x2ac / 4) = fCurrentD;

    // Update global pointer to point to a default object (DAT_0120fa60)
    DAT_01206a3c = &DAT_0120fa60;

    // If second object is player and has event handler (at +0x298)
    if ((DAT_012058e8 == (int)pObj2) && (*(int*)(pObj2 + 0x298 / 4) != 0))
    {
        sub_60add0(*(int*)(pObj2 + 0x14 / 4), *(int*)(pObj2 + 0x298 / 4), pfDelta2);
    }

    // Reset global pointer to another default (DAT_0120f840)
    DAT_01206a3c = &DAT_0120f840;
}