// FUNC_NAME: getObjectGUID
// Function at 0x0045da60: Retrieves a 128-bit GUID from an ID, first via hash table lookup, then fallback.
// param_1: pointer to 4-int output GUID (outGUID)
// param_2: identifier (some token/string hash or resource ID)
void getObjectGUID(int* outGUID, int resourceID)
{
    // Constants from the binary
    const int HASH_KEY = 0xae986323;            // Key used in first hash lookup
    const short GUID_TYPE_MAGIC = 0x25e3;       // Magic value indicating valid GUID type at offset +6
    const int FALLBACK_SEED = 0x38860031;       // Seed for fallback lookup

    // Clear output GUID (128-bit / 4 ints)
    outGUID[0] = 0;
    outGUID[1] = 0;
    outGUID[2] = 0;
    outGUID[3] = 0;

    // First lookup attempt: possibly hash table or custom container
    // The following two calls likely operate on the stack frame, setting local variables.
    int unusedResult1 = FUN_0043aff0(resourceID, HASH_KEY); // +0x?? (stack info)
    int unusedResult2 = FUN_0043af00(2);                      // Set key length?

    // Variables set by the above calls (names based on usage):
    bool bIsInline;           // local_68: flag indicating if data is stored inline or via pointer
    int* pEntry;              // local_c: pointer to a data structure (entry)
    int length1;              // local_5c: length or count from entry
    int length2;              // local_58: additional length/count
    int buffer[18];           // local_54: stack buffer used when data is not inline

    // Note: The decompiler shows these are used uninitialized, but the preceding calls (FUN_0043aff0, FUN_0043af00)
    // are expected to have set them via some stack pointer manipulation (possibly through global/register).
    // For reconstruction, we assume they are correctly initialized by those calls.

    // Determine if the entry is valid based on the inline flag
    bool entryValid;
    if (!bIsInline) {
        entryValid = (*pEntry == 0); // If pointer is null? Actually check *pEntry == 0 ?
        // The original: bVar3 = *local_c == 0; So entryValid = (*pEntry == 0) means invalid.
        // But the logic: if (!bVar3) { ... } so we invert: entryValid = !bVar3 => *local_c != 0.
        // So we write:
        entryValid = (*pEntry != 0);
    }
    else {
        entryValid = (length1 == length2); // Inline case: compare two lengths
    }

    if (!entryValid)
    {
        // If entry is not valid, we need to correct the pointer
        if (bIsInline) {
            pEntry = buffer; // Use inline buffer as the data source
        }

        // Check magic value at offset +6 of the entry structure (short)
        if (*(short*)((int)pEntry + 6) == GUID_TYPE_MAGIC)
        {
            // Entry is a direct GUID: pEntry points to a structure with the GUID at offset indicated by *pEntry
            // if *pEntry == 0 then use a global default GUID (DAT_0120e700)
            int* pGuid;
            if (*pEntry == 0) {
                pGuid = (int*)0x0120e700; // Hardcoded address - replace with actual global if known
            }
            else {
                pGuid = (int*)(pEntry[2] + *pEntry); // Dereference: pGuid = (int*)(*(int*)(pEntry+2) + *pEntry)
            }
            // Now pGuid points to a 128-bit GUID (4 ints)
            // Check if the GUID is non-zero (all four parts)
            if ( (pGuid[0] != 0) || (pGuid[1] != 0) || (pGuid[2] != 0) || (pGuid[3] != 0) )
            {
                // Validate GUID via some function
                int isValid = FUN_004211e0(pGuid); // Returns non-zero if valid
                if (isValid != 0)
                {
                    // Copy the GUID to output
                    outGUID[0] = pGuid[0];
                    outGUID[1] = pGuid[1];
                    outGUID[2] = pGuid[2];
                    outGUID[3] = pGuid[3];
                }
            }
        }
        else
        {
            // Entry is a pointer to a remote GUID (pEntry+2)
            int* pRemote = pEntry + 2; // pRemote points to a structure with GUID at offset 0
            // Check if the remote GUID is non-zero
            if ( (pRemote[0] != 0) || (pRemote[1] != 0) || (pRemote[2] != 0) || (pRemote[3] != 0) )
            {
                int isValid = FUN_004211e0(pRemote);
                if (isValid != 0)
                {
                    outGUID[0] = pRemote[0];
                    outGUID[1] = pRemote[1];
                    outGUID[2] = pRemote[2];
                    outGUID[3] = pRemote[3];
                }
            }
        }
    }

    // If output GUID is still all zeros, try a fallback lookup
    if ( (outGUID[0] == 0) && (outGUID[1] == 0) && (outGUID[2] == 0) && (outGUID[3] == 0) )
    {
        int* pFallback = (int*)FUN_004b9ca0(resourceID, FALLBACK_SEED); // Returns pointer to some object
        if (pFallback != 0)
        {
            // GUID is stored at offsets +0x1c to +0x28 (four ints)
            // +0x1c: first int
            // +0x20: second int
            // +0x24: third int
            // +0x28: fourth int
            outGUID[0] = *(int*)((int)pFallback + 0x1c);
            outGUID[1] = *(int*)((int)pFallback + 0x20);
            outGUID[2] = *(int*)((int)pFallback + 0x24);
            outGUID[3] = *(int*)((int)pFallback + 0x28);
        }
    }

    return;
}