// FUNC_NAME: UniqueList::addIfNotExists (or LinkedList::insertUnique)
// Function address: 0x004fc270
// Role: Inserts a new node into a doubly-linked list (managed by the object at `list`)
// while ensuring no duplicate entry exists, using a fast lookup array (`lookupArray`).
// Returns 1 if inserted, 0 if duplicate or failure.

typedef char byte;

// Thread-local storage base pointer (likely EARS per-thread memory manager)
extern int __tls_base; // accessed via FS offset 0x2c

// Allocation function: size stored in *outSize (actual allocated size)
extern bool nodeAllocator(int* outSize);

// Function that returns the number of items to process,
// takes max capacity and some other param (possibly element size or flags)
extern int getProcessCount(int maxCapacity, int extraParam);

// Reconstructed function
byte UniqueList_AddIfNotExists(int* list, int* lookupArray, int extraParamInEAX)
{
    int listSize;
    int nodeIndex;
    int iVar1;
    int* piVar3;
    int nodePtr;
    int iVar4;
    int iVar5;
    int* piVar6;
    int iVar7;
    int iVar8;
    int* listElemPtr;
    int tlsBase;
    int currentCount;

    // Get number of items to iterate from list's external count
    listSize = getProcessCount(lookupArray[1], extraParamInEAX);
    *(byte *)lookupArray = 0; // default return: not inserted

    if (listSize == 0) {
        return 0;
    }

    // Iterate over the list of IDs stored at list+0x1c
    listElemPtr = (int *)(list + 0x7); // list+0x1c as int-pointer (since offset 0x1c = 28 bytes = 7 ints)
    // Actually list is int*, so list+0x1c is list + 7 (since int is 4 bytes)
    // Correct: list + 0x7 for offset 0x1c

    for (; listSize > 0; listSize--) {
        // Check if this ID already exists in the lookup array
        iVar7 = 0;
        if (lookupArray[0x16] > 0) {
            piVar3 = lookupArray;
            do {
                piVar3 += 2; // skip to next entry pair
                // Access global array via TLS to get the unique key for this ID
                int key = *(int *)(*(int *)(**(int **)(__tls_base + 0x2c) + 8) + 0x24 + *listElemPtr);
                if (key == *(int *)(*(int *)(**(int **)(__tls_base + 0x2c) + 8) + 0x24 + *piVar3)) {
                    goto LABEL_DUPLICATE;
                }
                iVar7++;
            } while (iVar7 < lookupArray[0x16]);
        }

        // Not a duplicate; proceed with insertion
        if (lookupArray[0x16] < lookupArray[1]) {
            int objPtr = *listElemPtr; // dereference the ID to get object pointer
            // Allocate a new node from TLS pool
            nodeAllocator(&nodeIndex);
            if (nodeIndex != 0) {
                tlsBase = **(int **)(__tls_base + 0x2c);
                nodePtr = *(int *)(tlsBase + 8) + nodeIndex; // compute node address in pool

                // Call virtual functions on the object to get data to store in node
                int* vtable = *(int**)objPtr;
                iVar4 = (*(int (**)(void))(vtable[1]))(); // vtable[1]? Usually vtable[0] is something else, vtable[1] might be a method to get data1
                *(int *)(nodePtr + 0x10) = iVar4;
                if (iVar4 != 0) {
                    iVar5 = (*(int (**)(void))(vtable[2]))(); // vtable[2] for data2
                    *(int *)(nodePtr + 0x1c) = iVar5;
                }
                *(int **)(nodePtr + 0x24) = (int*)objPtr; // store pointer to original object

                // Initialize node's next/prev links (currently null)
                int* nodeLinks = (int *)(*(int *)(tlsBase + 8) + 8 + nodeIndex);
                *nodeLinks = 0;
                *(nodeLinks+1) = 0;

                // Insert node at tail of the linked list (list+0x14 = head, list+0x18 = tail)
                int* nodeData = (int *)(*(int *)(tlsBase + 8) + nodeIndex);
                *nodeData = *(int *)(list + 0x5); // list+0x14 -> head? Actually offset 0x14 = 20 bytes = 5 ints
                *(nodeData+1) = *(int *)(list + 0x6); // list+0x18 -> tail? offset 0x18 = 24 bytes = 6 ints

                // Update head/tail if list was empty
                if (*(int *)(list + 0x5) != 0) {
                    int* prevTail = (int *)(*(int *)(list + 0x5) + 8 + *(int *)(tlsBase + 8));
                    *prevTail = nodeIndex;
                    *(prevTail+1) = iStack_8; // store some value (likely the tail's next pointer)
                }

                // Update list head and tail
                *(int *)(list + 0x5) = nodeIndex;
                *(int *)(list + 0x6) = iStack_8; // iStack_8 is likely the tail's next pointer

                // Increment a counter in the node (maybe reference count or usage)
                int* nodeCount = (int *)(*(int *)(tlsBase + 8) + 0x30 + nodeIndex);
                *nodeCount = *nodeCount + 1;

                // Add the new node's indices to the lookup array
                int currentCount = lookupArray[0x16];
                if (currentCount < 10) { // limit to 10 entries? Possibly a small cache
                    lookupArray[0x16] = currentCount + 1;
                    lookupArray[currentCount * 2 + 2] = nodeIndex;
                    lookupArray[currentCount * 2 + 3] = iStack_8;
                }

                *(byte *)lookupArray = 1; // mark success
            }
        }

LABEL_DUPLICATE:
        listElemPtr++; // move to next element in the list
        // (listSize decremented in loop condition)
    }

    return *(byte *)lookupArray;
}