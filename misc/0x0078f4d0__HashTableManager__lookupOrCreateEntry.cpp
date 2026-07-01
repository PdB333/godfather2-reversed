// FUNC_NAME: HashTableManager::lookupOrCreateEntry
void __thiscall HashTableManager::lookupOrCreateEntry(int* inOutIndex, int param3)
{
    int iVar1;
    int* piVar2;
    char cVar3;
    int* piVar4;
    char localBuffer[44]; // +0x40
    long long data8; // +0x14
    int data4; // +0x0c

    piVar2 = inOutIndex;
    // Offset to hash table: +0xB4 from this. Each entry is 16 bytes (4 ints)
    int* entryPtr = (int*)((int)inOutIndex * 0x10 + 0xB4 + (int)this);
    iVar1 = *entryPtr;

    // Check if entry is empty or marked as deleted (sentinel values)
    // Sentinel values: 0xBADABDBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
    if ((iVar1 != -0x45245246) || (entryPtr[1] != -0x41104111) ||
        (entryPtr[2] != -0x153ea5ab) || (entryPtr[3] != -0x6eeff6ef))
    {
        if ((iVar1 != 0) || (entryPtr[1] != 0) ||
            (entryPtr[2] != 0) || (entryPtr[3] != 0))
        {
            // Entry is occupied – query object manager for this key
            piVar4 = (int*)FUN_00446100(entryPtr, 0);  // some lookup by key
            if (piVar4 != (int*)0x0)
            {
                cVar3 = (*(code**)(*piVar4 + 0x10))(0x8a859764, &inOutIndex);
                if ((cVar3 != '\0') && (inOutIndex != (int*)0x0))
                {
                    // Create a new entry from the query result
                    (*(code**)(*inOutIndex + 4))(localBuffer);
                    // Copy first 12 bytes of local buffer into entry
                    *(long long*)inOutIndex = data8;
                    inOutIndex[2] = data4;
                    return;
                }
            }
        }
    }
    // Entry is empty or not found – fallback
    FUN_0078fba0(piVar2, param3);
    return;
}