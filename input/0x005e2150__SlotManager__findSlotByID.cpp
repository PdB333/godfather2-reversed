// FUNC_NAME: SlotManager::findSlotByID
// Address: 0x005e2150
// Role: Searches an array of 5 slots (each 0x4a4 bytes) for a matching ID pointer stored at offset +0x48c relative to each slot base.
// The slot array starts at this+4. Returns pointer to the slot base (this+4 + index*0x4a4) if found, otherwise 0.

int __fastcall SlotManager::findSlotByID(int param_1, int param_2)
{
    // param_1 is unused? Actually ECX is 'this', but decompiler assigned param_1 (unused) to ECX.
    // EDX is the ID to search for.
    int thisPtr = (int)this; // unaff_ESI in decompiled code, representing 'this' pointer
    int iVar1;
    int *piVar2;

    if (param_2 != 0) {
        iVar1 = 0;
        piVar2 = (int *)(thisPtr + 0x490); // pointer to the first slot's ID field
        do {
            if (param_2 == *piVar2) {
                // Return pointer to the slot base (starting offset +4 from this)
                return iVar1 * 0x4a4 + 4 + thisPtr;
            }
            iVar1 = iVar1 + 1;
            piVar2 = piVar2 + 0x129; // advance to next slot's ID field (0x129*4 = 0x4a4 bytes)
        } while (iVar1 < 5);
    }
    return 0;
}