// FUNC_NAME: CreditManager::addCreditTransaction
float __thiscall CreditManager::addCreditTransaction(int this, int creditType, int transactionId, float amount, int description)
{
    // Node structure from a pool/list at this+0x1380 (free list head) and this+0x1384 (active list head?)
    // Offsets within node:
    // [0x00] - uniqueId (counter)
    // [0x04] - description (param_5)
    // [0x05] - amount (param_4)
    // [0x06] - unused (0)
    // [0x07] - timestamp (global tick)
    // [0x08] - creditType (1-4)
    // [0x09] - previousBalance (based on creditType)
    // [0x0A] - nextActive? (used for list manipulation)

    int *freeListHead = *(int **)(this + 0x1380); // Free list head
    int *pEntry = freeListHead;                   // Allocate an entry from free list

    // Remove entry from free list: freeListHead = pEntry[0x0A] (next in free list)
    *(int *)(this + 0x1380) = pEntry[10];
    // Insert into active list: pEntry[0x0A] = current active list head; active list head = pEntry
    pEntry[10] = *(int *)(this + 0x1384);
    *(int **)(this + 0x1384) = pEntry;

    int oldBalance = 0;
    // creditType ranges 1-4, fetch from array at offsets 0x74 (+4 per type)
    switch (creditType)
    {
    case 1:
        oldBalance = *(int *)(this + 0x74);
        break;
    case 2:
        oldBalance = *(int *)(this + 0x78);
        break;
    case 3:
        oldBalance = *(int *)(this + 0x7c);
        break;
    case 4:
        oldBalance = *(int *)(this + 0x80);
        break;
    }

    // Assign a unique ID from a counter at this+0x1394
    pEntry[0] = *(int *)(this + 0x1394);
    *(int *)(this + 0x1394) += 1;

    pEntry[9] = oldBalance;          // Previous balance
    pEntry[8] = creditType;          // Credit type
    pEntry[4] = description;         // Description (string pointer)
    pEntry[5] = *(int *)&amount;     // Amount (stored as int but is float)
    pEntry[6] = 0;                   // Unused
    pEntry[7] = g_globalTimestamp;   // Global timestamp (from DAT_00d5780c)

    // Update "current" transaction fields in this object (maybe for quick access)
    *(int *)(this + 100) = creditType;       // +0x64? Actually offset is 0x64? Decompiled says "param_1 + 100" = decimal 100 => hex 0x64
    *(int *)(this + 0x68) = pEntry[0];       // Unique ID
    *(float *)(this + 0x60) = amount;        // Amount
    *(int *)(this + 0x5c) = description;     // Description

    // Log the transaction (FUN_005a04a0)
    logCreditTransaction("AddCredit", 0, &DAT_00d87730, 1, transactionId);

    // Return the net change: amount - oldBalance (as float)
    return amount - (float)oldBalance;
}