// FUN_NAME: StringTable::FindOrInsertWideString

void __thiscall StringTable::FindOrInsertWideString(int thisPtr, byte* keyString, int param3)
{
    // Iterate through circular linked list at +0x24 (list head)
    // Node structure: +0x00 next, +0x04 prev, +0x08 key (wchar_t*)
    int* listHead = *(int**)*(int**)(thisPtr + 0x24);
    int* currentNode = listHead;
    int* allocator_vtable = *(int**)(thisPtr + 0x0c); // Allocator vtable

    // Search for existing key in the list
    while (currentNode != *(int**)(thisPtr + 0x24))
    {
        if (currentNode == *(int**)(thisPtr + 0x24))
        {
            // Corruption: head node in non-head position
            Assert(0);
        }

        // Retrieve the wide-character string from node at +0x08
        wchar_t* existingKey = (wchar_t*)*(int*)((int)currentNode + 8);
        if (existingKey == nullptr)
        {
            existingKey = (wchar_t*)&g_defaultString; // DAT_0120546e
        }

        // Compare keyString with existingKey (2-byte comparison, wchar_t)
        wchar_t* k1 = (wchar_t*)existingKey;
        wchar_t* k2 = (wchar_t*)keyString;
        int cmpResult;
        do
        {
            wchar_t c1 = *k1;
            wchar_t c2 = *k2;
            if (c1 != c2)
            {
                cmpResult = (c1 < c2) ? -1 : 1;
                break;
            }
            if (c1 == 0) break;
            k1++;
            k2++;
        } while (true);
        if (cmpResult == 0)
        {
            // Key found, exit function
            return;
        }

        // Move to next node
        if (currentNode == *(int**)(thisPtr + 0x24))
        {
            Assert(0);
        }
        currentNode = (int*)*currentNode;
    }

    // Key not found – allocate a new entry of size 0x28 (40 bytes)
    int* memoryTracker = *(int*)(thisPtr + 0x2c);
    int* newEntry = (int*)(*(int(__cdecl*)(int,int))DAT_012059dc)(0, 0x28); // MemoryAlloc
    if (newEntry == nullptr)
    {
        if (memoryTracker == nullptr)
        {
            newEntry = nullptr;
            goto skip_allocation;
        }
        newEntry = (int*)FallbackAlloc(); // FUN_00635a80
    }

    if (memoryTracker != nullptr)
    {
        // Update memory tracker (increment used size)
        int* memBlock = *(int**)(memoryTracker + 0x10);
        *memBlock += 0x28;
    }

    // Zero initialize the new entry
    newEntry[0] = 0;
    newEntry[1] = 0;
    newEntry[2] = 0;
    newEntry[3] = 0;
    newEntry[4] = 0;
    newEntry[5] = 0;
    newEntry[6] = 0;
    newEntry[7] = 0;
    newEntry[8] = 0;
    *((short*)(newEntry + 9)) = 0;   // offset 0x24
    *((short*)((int)newEntry + 0x26)) = 0; // offset 0x26

skip_allocation:
    // If key string is non-null and non-empty, compute hash and store it
    if (keyString != nullptr && *keyString != 0)
    {
        int hash = ComputeHash((wchar_t*)keyString); // FUN_004dafd0
        SetHashInEntry(newEntry + 8, hash); // FUN_00408260 – stores hash at entry+0x20
    }

    // If hash is non-zero, increment short at offset 0x24 and maybe randomize
    if (newEntry[8] != 0)
    {
        (*((short*)(newEntry + 9)))++; // Increment counter at +0x24
        int randomVal = GetRandom(); // FUN_00407da0
        if (randomVal == 0)
        {
            DoBitwiseOp(newEntry + 8, 0x8000); // FUN_004084d0 – mask with 0x8000
        }
        else
        {
            // XOR with random value to add entropy to token
            ushort* tokenPtr = (ushort*)(randomVal + 0x14);
            ushort oldToken = *tokenPtr;
            *tokenPtr = (oldToken & 0x7fff) | (((oldToken * 2) >> 1) + 1);
        }
    }

    // Free the input strings (they are assumed to be dynamic or temporary)
    FreeString((wchar_t*)keyString); // FUN_004d3d90
    if (param3 != 0)
    {
        FreeString((wchar_t*)param3); // FUN_004d3d90
    }

    // Allocate and initialize a new node for the main list (size 0xC = 12 bytes)
    int* parentList = (int*)*(int*)(thisPtr + 0x10); // +0x10 -> parent list or allocator context
    int* nodeAllocatorContext;
    if (parentList == nullptr)
    {
        // Use local fallback triple (stack storage)
        int localTriple[3] = {0, 0, 0};
        nodeAllocatorContext = localTriple;
    }
    else
    {
        nodeAllocatorContext = parentList;
    }

    // Call vtable function at this+0xc: it takes size=0xC and a context pointer
    int* newNode = (int*)(allocator_vtable[0])(0xC, nodeAllocatorContext); // vtable function for allocation
    if (newNode != nullptr)
    {
        newNode[0] = *(int*)(thisPtr + 0x24); // prev pointer? Actually stores list head
    }
    newNode[1] = *(int*)(thisPtr + 0x24); // next? Actually stores list head as well? (uStack_2c is uninitialized, likely this holds the head)
    newNode[2] = thisPtr + 0x0c; // vtable pointer or allocator

    // Insert newNode into the circular list
    // Assume list head is at this+0x24, newNode->next = head, newNode->prev = head->prev
    // But the code is confusing; likely it's a proper double-linked list insertion.
    // Based on decompilation: puStack_20[1] = puVar9 (newNode); and *puVar2 = puVar9 where puVar2 = newNode+1
    // This sets the list head's next to newNode.
    *(int**)(thisPtr + 0x28) = newNode; // Insert into list? (likely overwriting head->next)
    *((int*)newNode[1]) = (int)newNode; // Link back
    // (The above is approximate; actual EA engine list insertion would be more robust)

    // Call to finalize or lock (FUN_004cf240)
    FinalizeInsertion(); // FUN_004cf240
}