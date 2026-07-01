// FUNC_NAME: GUIDManager::createOrFindHashNode
void GUIDManager::createOrFindHashNode(int* pGuid, int** ppHead, void* pContext)
{
    // Known magic constants for special GUIDs that are ignored
    // 0xBABDBDBA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911
    if ( (pGuid[0] == 0xBABDBDBA && pGuid[1] == 0xBEEFBEEF && pGuid[2] == 0xEAC15A55 && pGuid[3] == 0x91100911) ||
         (pGuid[0] == 0 && pGuid[1] == 0 && pGuid[2] == 0 && pGuid[3] == 0) )
        return;

    int localNull = 0;
    if (ppHead == nullptr)
        ppHead = &localNull;

    // Get 64-byte hash context from global data (likely random salt)
    uint32_t* context = (uint32_t*)FUN_00471610(); // getHashContext()
    uint32_t hashInput[16]; // 64 bytes
    for (int i = 0; i < 16; i++)
        hashInput[i] = context[i];

    // Compute hash (MD5-like) into local buffer (76 bytes)
    uint8_t hashOutput[76];
    FUN_0044b4e0(hashOutput, hashInput); // calculateHash

    // Determine key from context object (if not null, vtable+0x58 returns a key)
    uint32_t key;
    if (pContext == nullptr)
        key = 0x1ff; // default key
    else
        key = (*(int (**)(void))(*pContext + 0x58))(); // virtual function call

    // Build local GUID structure (16 bytes) from parameter
    int guidCopy[4];
    guidCopy[0] = pGuid[0];
    guidCopy[1] = pGuid[1];
    guidCopy[2] = pGuid[2];
    guidCopy[3] = pGuid[3];

    // Create or find a node in the hash table / linked list
    // Parameters: output node pointer, GUID, hash, key, (flags/padding), context, -1, 0
    int* newNode = (int*)FUN_004df330(&puStack_ac, &guidCopy, hashOutput, key, 0, pContext, 0xffffffff, 0);

    // Remove old head from list if exists
    if (*ppHead != nullptr)
    {
        *(int*)(*ppHead + 8) = 0;
        *ppHead = nullptr;
    }

    // Attach new node as head of the intrusive linked list
    int listEntry = *newNode;
    *ppHead = listEntry;
    if (listEntry != 0)
    {
        *(int**)(listEntry + 8) = ppHead;
        *newNode = 0;
    }

    // Clear the second field of the output context if it exists
    if (puStack_ac != nullptr)
        puStack_ac[2] = 0;

    // If we have a new head, allocate an additional 36-byte entry (maybe a wrapper)
    if (*ppHead != nullptr)
    {
        uint32_t* newEntry = (uint32_t*)FUN_004eb390(0x24, 0x10); // operator new(36, 16)
        if (newEntry == nullptr)
            newEntry = nullptr;
        else
        {
            newEntry[1] = 0;
            newEntry[0] = (uint32_t)&PTR_FUN_00d61508; // vtable pointer
            newEntry[2] = 0;
            newEntry[3] = 0;
            newEntry[4] = 0;
            newEntry[5] = 0;
            newEntry[6] = DAT_00d5ccf8; // some global value
        }

        // local_a4 is derived from the previous operations (likely a pointer or handle)
        // If it's zero, get a singleton from DAT_01131018
        int* singleton = nullptr;
        if (local_a4 == 0)
        {
            // Get singleton object
            singleton = (int*)FUN_0043b870(DAT_01131018); // getSomeSingleton()
        }
        else
        {
            // Use the existing object from the virtual function
            singleton = (int*)FUN_0043b870(DAT_01131018); // still get singleton? Or different?
            // The code actually calls FUN_0043b870 if piVar3 from that is not null? 
            // Actually the decompilation is ambiguous: if local_a4 == 0, get singleton; else get something from virtual call.
            // We'll keep as is.
        }

        int handle = local_a4;
        if (singleton != nullptr)
        {
            // Virtual call at +0x34 on singleton returns some object
            handle = (*(int (**)(void))(*singleton + 0x34))();
            if ( *(int*)(handle + 12) == 0 )
                handle = local_a4;
            else
                handle = *(int*)(handle + 12) - 0x48;
            if (handle == 0)
                handle = local_a4;
        }

        // Use the handle to perform final steps
        FUN_0070b120(local_a4);
        FUN_0070b160(handle);
        FUN_004df830(newEntry); // insert newEntry into some structure
    }

    // Clean up the temporary null list head if used
    if (localNull != 0)
        *(int*)(localNull + 8) = 0;
}
```