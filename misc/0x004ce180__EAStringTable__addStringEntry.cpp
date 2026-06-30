// FUNC_NAME: EAStringTable::addStringEntry

void __thiscall EAStringTable::addStringEntry(int thisPtr, byte* keyString, byte* valueString)
{
    // thisPtr offsets:
    // +0x0C: pointer to allocator/factory (function pointer for object creation)
    // +0x10: pointer to last node in master linked list (or null)
    // +0x24: head of hash bucket linked list (circular, sentinel)
    // +0x2C: optional memory pool pointer
    //
    // Node layout (0x28 = 40 bytes):
    // +0x00: next pointer in bucket list
    // +0x04: unknown (used for master list linkage)
    // +0x08: stored key string pointer (used for comparison)
    // +0x0C through +0x1F: unknown, zeroed on allocation
    // +0x20: value string or other data (set after allocation)
    // +0x24: short reference count or flag
    // +0x26: short something

    StringNode* currentNode;
    StringNode* newNode;
    int* counterPtr;
    byte b1, b2;
    byte* str1, * str2;
    int cmpResult;
    bool lessThan;
    int local_2c; // unknown, used but uninitialized

    // Search for existing key in hash bucket list
    for (currentNode = *(StringNode**)(thisPtr + 0x24); 
         currentNode != *(StringNode**)(thisPtr + 0x24); 
         currentNode = (StringNode*)*currentNode)
    {
        // Sentinel check: should never be at head after first iteration
        // (circular list with sentinel)
        if (currentNode == *(StringNode**)(thisPtr + 0x24)) {
            FUN_00b97aea(); // assertion/error handler
        }

        str1 = (byte*)currentNode->storedKey; // +0x08
        str2 = keyString;
        if (str1 == nullptr) {
            str1 = &DAT_0120546e; // fallback empty string
        }

        // Word-aligned string comparison (two bytes at a time)
        do {
            b1 = *str2;
            lessThan = b1 < *str1;
            if (b1 != *str1) {
                cmpResult = (lessThan ? -1 : 1);
                goto doneCompare;
            }
            if (b1 == 0) break;
            b1 = str2[1];
            lessThan = b1 < str1[1];
            if (b1 != str1[1]) {
                cmpResult = (lessThan ? -1 : 1);
                goto doneCompare;
            }
            str1 += 2;
            str2 += 2;
        } while (b1 != 0);
        cmpResult = 0;

doneCompare:
        if (cmpResult == 0) {
            // Key already exists, return (but note: no insertion done,
            // just returns without adding? Actually returns void, but caller may have stored)
            return;
        }

        // Safety: check for sentinel before next iteration
        if (currentNode == *(StringNode**)(thisPtr + 0x24)) {
            FUN_00b97aea();
        }
    }

    // Key not found, allocate new node
    int memoryPool = *(int*)(thisPtr + 0x2C);
    newNode = (StringNode*) (*DAT_012059dc)(0, 0x28); // custom allocator
    if (newNode == nullptr) {
        if (memoryPool == 0) {
            newNode = nullptr;
            goto allocateDone;
        }
        newNode = (StringNode*)FUN_00635a80(); // fallback allocation
    }

    if (memoryPool != 0) {
        // Increase allocation counter in pool
        counterPtr = (int*)(*(int*)(memoryPool + 0x10) + 0x24);
        *counterPtr += 0x28;
    }

    // Initialize node: zero first 32 bytes (8 dwords)
    newNode->next = nullptr;
    newNode->field4 = nullptr;
    newNode->storedKey = nullptr;
    // Zero remaining dwords up to offset 0x20
    // (Assume zeroing loop covers indices 0-7)
    for (int i = 3; i < 8; i++) {
        ((uint32*)newNode)[i] = 0;
    }
    // Set shorts at +0x24 and +0x26 to 0
    *(uint16*)((uint8*)newNode + 0x24) = 0;
    *(uint16*)((uint8*)newNode + 0x26) = 0;

allocateDone:
    // If key is non-empty, compute hash/assign key to node's value area? Actually store at +0x20?
    if (keyString != nullptr && *keyString != 0) {
        uint32 hash = FUN_004dafd0(keyString); // hash function
        FUN_00408260(&newNode->valueAt20, hash); // store at +0x20
    }

    // If the valueAt20 is non-zero, increment a counter at +0x26 and do something with a reference count
    if (newNode->valueAt20 != 0) {
        *(int16*)((uint8*)newNode + 0x26) += 1;
        int refCtr = FUN_00407da0(); // get global reference counter?
        if (refCtr == 0) {
            FUN_004084d0(&newNode->valueAt20, 0x8000); // set high bit?
        } else {
            uint16 uVar4 = *(uint16*)(refCtr + 0x14);
            *(uint16*)(refCtr + 0x14) = 
                ((int16)((int)((uint)uVar4 * 2) >> 1) + 1U ^ uVar4) & 0x7FFF ^ uVar4;
        }
    }

    // Free the input strings (they were temporary? Or ownership transferred)
    FUN_004d3d90(keyString);
    if (valueString != nullptr) {
        FUN_004d3d90(valueString);
    }

    // Insert node into master list? The master list head is at this+0x24,
    // but here we insert into a separate list headed by this+0x10.
    uint32 masterListHead = *(uint32*)(thisPtr + 0x24);
    uint32* masterListLast = *(uint32**)(thisPtr + 0x10);
    if (masterListLast == nullptr) {
        // Use local variable as sentinel (stack allocated)
        // The actual sentinel is likely at this+0x10 itself, but this is a workaround
        // to avoid null pointer.
        uint32 stackSentinel[3] = {0, 0, 0};
        masterListLast = stackSentinel;
    }

    // Create a small object (0xC bytes) presumably for linking into master list
    uint32* linkObj = (uint32*)(*(code**)(*(uint32*)(thisPtr + 0xC)))(0xC, masterListLast);
    if (linkObj != nullptr) {
        *linkObj = masterListHead;
    }
    uint32* nextLink = linkObj + 1;
    if (nextLink != nullptr) {
        *nextLink = local_2c; // uninitialized, likely bug or register leftover
    }
    if (linkObj + 2 != (int*)nullptr) {
        linkObj[2] = (uint32*)(thisPtr + 0xC);
    }

    FUN_004cf240(); // process master list insertion? Possibly add to linked list
    // Actually, set newNode's field4 to the link object and update master list
    newNode->field4 = linkObj;
    *nextLink = (uint32)newNode; // insert newNode into master list

    return;
}