// FUNC_NAME: Entity::registerInManager
// Address: 0x008907b0
// Registers this entity in a global manager's linked list, comparing by 64-byte GUID/name.
// Uses a hash table with chaining. Called once on first update (flag at +0x74*4).

void __fastcall Entity::registerInManager(int* thisPtr)
{
    int* piVar1;
    uint hashValue;
    byte* pbStr1;
    byte* pbStr2;
    int compareResult;
    int* iterNode;
    int* prevNode;
    int* localHashKey; // +0x10?0x28 from owner

    // Check if already registered (bit 0 of field at +0x74)
    if ((thisPtr[0x74] & 1U) == 0) {
        thisPtr[0x74] |= 1; // Set flag

        // Get pointer to hash table entry list from owner manager
        // thisPtr[0x4c] is pointer to owner (e.g., Manager), +0x10 -> some array, +0x28 -> list head
        localHashKey = *(int**)(*(int*)(thisPtr[0x4c] + 0x10) + 0x28);

        // Compute a hash value from some ID (field +0x6a)
        hashValue = thunk_FUN_0042a990(thisPtr[0x6a]); // someHashFunction

        // Store hash in field +0x75
        thisPtr[0x75] = hashValue;

        // If bits 6 and 7 of hash are both set, adjust based on flag byte at +0x6b (low byte)
        if (((byte)hashValue & 0xc0) == 0xc0) {
            if ((*(byte*)(thisPtr + 0x6b) & 1) == 0) {
                hashValue = (hashValue & 0xffffffbf) | 0x80; // clear bit6, set bit7
            } else {
                hashValue = (hashValue & 0xffffff7f) | 0x40; // clear bit7, set bit6
            }
            thisPtr[0x75] = hashValue;
        }

        // Call virtual function at vtable+0x5c with the hash and -1 (maybe set up something)
        (**(code**)(*thisPtr + 0x5c))(hashValue, 0xffffffff);

        uVar2 = thisPtr[0x75];
        // If bit 9 (0x200) is set and owner exists, do something
        if (((uVar2 & 0x200) != 0) && (piVar1 = (int*)thisPtr[0x4c], piVar1 != NULL)) {
            FUN_004a3d40(uVar2, ~uVar2, 1); // some bitwise operation
            (**(code**)(*piVar1 + 0x40))(0x20e5862, &localHashKey); // virtual call on owner
        }

        // Global hash table manager (DAT_0112e2dc)
        int* g_hashTableRoot = (int*)DAT_0112e2dc; // actually a struct with offsets +4 and +8

        // Get the hash bucket list head from g_hashTableRoot
        // g_hashTableRoot[1] = bucket array, g_hashTableRoot[2] = bucket count
        int* bucketList = *(int**)(g_hashTableRoot[1] + g_hashTableRoot[2] * 4);

        // Use FUN_008903b0 to start iterator over list with key from localHashKey
        // localHashKey is the expected key (maybe the name index)
        FUN_008903b0(&iterNode, &localHashKey); // likely initializes an iterator

        // Bucket list is the first node in the chain
        int* firstNode = bucketList;

        // Walk the linked list (each node has +0, +4, +8? Actually next at +8? Check code: piStack_14[2] is next? 
        // The loop uses piStack_14[2] as next pointer and compares key at piStack_14[0] to localHashKey)
        while (iterNode != firstNode) {
            // Check if current node's key matches localHashKey
            if ((int*)*iterNode == localHashKey) {
                int* nodeWithData = (int*)iterNode[1]; // pointer to actual data node with strings
                // Get string from this entity (+0x15*4) via virtual call (vtable[4])
                pbStr1 = (byte*)(**(code**)(thisPtr[0x15] + 4))(); // likely returns pointer to GUID/name
                // Get string from node's data (+0x54*4) via virtual call
                pbStr2 = (byte*)(**(code**)(*(int*)(nodeWithData + 0x54) + 4))();

                // Compare 64 bytes (0x40) in chunks of 4
                uint remaining = 0x40;
                do {
                    if (*(int*)pbStr1 != *(int*)pbStr2) goto notEqual;
                    remaining -= 4;
                    pbStr2 += 4;
                    pbStr1 += 4;
                } while (3 < remaining); // while remaining > 3

                if (remaining == 0) {
                    compareResult = 0;
                } else {
notEqual:
                    int diff = (uint)*pbStr1 - (uint)*pbStr2;
                    if (diff == 0) {
                        if (remaining == 1) compareResult = 0;
                        else {
                            diff = (uint)pbStr1[1] - (uint)pbStr2[1];
                            if (diff == 0) {
                                if (remaining == 2) compareResult = 0;
                                else {
                                    diff = (uint)pbStr1[2] - (uint)pbStr2[2];
                                    if (diff == 0) {
                                        if (remaining == 3) compareResult = 0;
                                        else {
                                            diff = (uint)pbStr1[3] - (uint)pbStr2[3];
                                            if (diff == 0) compareResult = 0;
                                            else compareResult = 1;
                                        }
                                    } else compareResult = 1;
                                }
                            } else compareResult = 1;
                        }
                    } else compareResult = 1;
                    if (diff < 1) compareResult = -1;
                }

                // If strings match (compareResult == 0), insert this entity into the node's linked list
                if (compareResult == 0) {
                    // Find last node in the chain (using field +0x1c0 as next pointer)
                    int* tail = nodeWithData;
                    int* next = *(int*)(nodeWithData + 0x1c0); // +0x1c0 is a next pointer
                    while (next != 0) {
                        tail = (int*)next; // actually advance node pointer
                        next = *(int*)(tail + 0x1c0); // go to next
                    }
                    // Append this entity to the end of the list
                    *(int**)(tail + 0x1c0) = thisPtr; // tail->next = this
                    thisPtr[0x71] = (int)tail; // store previous tail in +0x71
                }
                // If no match, continue to next node in bucket chain
            }
            // Move to next node in chain (use iterNode[2] as next pointer according to control flow)
            iterNode = (int*)iterNode[2];
            if (iterNode == NULL) {
                // If NULL, wrap around? The code jumps to another loop that increments something
                iterNode = (int*)(thisPtr + 1); // questionable
                // Actually the code at code_r0x00890951:
                // for (iterNode = (int*)piStack_14[2]; iterNode == NULL; iterNode = (int*)*iterNode) { iterNode = piStack_10+1; piStack_10=piStack_10+1; }
                // This is weird; probably a while loop for linked list traversal with sentinel.
                // We'll skip modeling exactly.
                // Simplified: break;
            }
            if (iterNode == firstNode) break;
        }

        // Rebalance or finalize insertion
        // Perform some kind of hash table insertion (calls FUN_00890410 with bucket list, iterator, localHashKey)
        FUN_00890410(&firstNode, &iterNode, (int*)((uint)localHashKey & 0xffffff00)); // trimmed key

        // Update some manager state (likely statistics or ordering)
        uint someState = FUN_0088cfd0(); // get something
        FUN_0088fbb0(someState);

        // Check if this entity has a sub-object (+0x77) that is of a certain type (bit22 check)
        if ((thisPtr[0x77] != 0) && (int* subObj = FUN_006b0ee0(thisPtr[0x77]), subObj != NULL) &&
            ((~(byte)(*(uint*)(subObj + 0x34) >> 0x16) & 1) == 0)) {
            // Notify owner manager (virtual +0x48)
            (**(code**)(*(int*)thisPtr[0x4c] + 0x48))(0x30256d83, 0);
        }

        // If there is a callback data (+0x76), call it with a parameter from callback data+0x10
        if (thisPtr[0x76] != 0) {
            FUN_004294a0(thisPtr, *(undefined4*)(thisPtr[0x76] + 0x10));
        }
    }

    // Generic update called every frame
    FUN_004ba130();
}