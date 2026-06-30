// FUNC_NAME: ObjectListDeserializer::deserializeList

int* __thiscall ObjectListDeserializer::deserializeList(int thisPtr, int* bufferDescriptor)
{
    int* itemBase;       // base address for items (pointer arithmetic)
    int listHead = 0;    // head of the linked list to return
    int* currentNode;    // newly allocated node
    uint index;          // loop counter

    int* containerPtr = bufferDescriptor[5]; // +0x14 in bufferDescriptor: pointer to container header
    int offset;          // used as offset within container

    if (*(short*)(containerPtr + 2) == 5) { // container type tag
        // Process first array (element size 0xa0)
        if (*(int*)(containerPtr + 4) != 0) {
            *(int*)(containerPtr + 4) = *(int*)(containerPtr + 4) + (int)containerPtr; // make absolute
        }
        if (*(int*)(containerPtr + 8) != 0) {
            *(int*)(containerPtr + 8) = *(int*)(containerPtr + 8) + (int)containerPtr; // make absolute
        }

        // Process first array (entries of size 0xa0)
        index = 0;
        if (*(short*)(containerPtr + 0xc) != 0) {
            do {
                itemBase = (int*)(*(int*)(containerPtr + 4) + offset);
                // Try to find existing object using four-part key
                int obj = createObjectFromFourPartKey(*itemBase, *(itemBase+1), *(itemBase+2), *(itemBase+3));
                if (obj == 0) {
                    // Object not found, create new one (first array constructor)
                    obj = constructFirstArrayType(itemBase);
                } else {
                    // Object exists, increment reference count
                    *(int*)(obj + 0x14) += 1;
                }

                // Allocate a linked list node (8 bytes)
                currentNode = (int*)allocateMemory(8);
                if (currentNode != 0) {
                    *currentNode = obj;
                    currentNode[1] = listHead; // link to previous head
                    listHead = (int)currentNode;
                }

                index++;
                offset += 0xa0; // advance to next element
            } while (index < *(unsigned short*)(containerPtr + 0xc));
        }

        // Process second array (entries of size 0x130)
        offset = 0;
        index = 0;
        if (*(short*)(containerPtr + 0xe) != 0) {
            do {
                itemBase = (int*)(*(int*)(containerPtr + 8) + offset);
                // Same key-based lookup
                int obj = createObjectFromFourPartKey(*itemBase, *(itemBase+1), *(itemBase+2), *(itemBase+3));
                if (obj == 0) {
                    // Object not found, create with second array constructor (note: uses thisPtr-4)
                    obj = constructSecondArrayType(thisPtr - 4);
                } else {
                    *(int*)(obj + 0x14) += 1;
                }

                currentNode = (int*)allocateMemory(8);
                if (currentNode != 0) {
                    *currentNode = obj;
                    currentNode[1] = listHead;
                    listHead = (int)currentNode;
                }

                index++;
                offset += 0x130;
            } while (index < *(unsigned short*)(containerPtr + 0xe));
        }
    }

    return (int*)listHead;
}

// Note: Called functions are stubs for readability.
// FUN_004508e0 → createObjectFromFourPartKey
// FUN_0044ee30 → constructFirstArrayType
// FUN_0044ef00 → constructSecondArrayType (uses thisPtr-4? possibly a different constructor)
// FUN_009c8e50 → allocateMemory (size in bytes)