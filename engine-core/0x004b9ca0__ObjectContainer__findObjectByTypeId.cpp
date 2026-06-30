// FUNC_NAME: ObjectContainer::findObjectByTypeId
int __thiscall ObjectContainer::findObjectByTypeId(void* this, int targetTypeId)
{
    int* nodePtr;
    int* arrayPtr;
    int* arrayEnd;
    int* currentPtr;
    int objectPtr;
    uint flags;
    bool hasMore;

    // Initialize iterator state (likely a container iterator)
    FUN_0043b230(this);

    // Main traversal loop
    while (true) {
        // Check termination condition based on traversal mode
        if (useArray) {
            hasMore = (arrayPtr != arrayEnd);
        } else {
            hasMore = (nodePtr != nullptr);
        }
        if (!hasMore) {
            return 0;
        }

        // Determine pointer to feed into lookup function
        if (!useArray) {
            // Linked list node traversal
            // Check node type tag at offset +6 (2-byte magic 0x25e3)
            if (*(short*)((int)nodePtr + 6) == 0x25e3) {
                // Special node type: resolve pointer using relative offset
                if (*nodePtr == 0) {
                    currentPtr = &DAT_0120e700;   // Default static node
                } else {
                    currentPtr = (int*)(nodePtr[2] + *nodePtr); // nodePtr[2] is offset +8
                }
            } else {
                // Normal node: just skip header (nodePtr+2 = data start)
                currentPtr = nodePtr + 2;
            }
        } else {
            // Array element traversal
            if (*arrayPtr == 0) {
                // Global default node handling
                if ((DAT_01223d10 & 1) == 0) {
                    DAT_01223d10 |= 1;
                    DAT_01223d00 = 0;
                    DAT_01223d04 = 0;
                    DAT_01223d08 = 0;
                    DAT_01223d0c = 0;
                }
                currentPtr = &DAT_01223d00;  // Static default node array
            } else {
                // Self-relative pointer: base + *arrayPtr
                currentPtr = (int*)(*arrayPtr + (int)arrayPtr);
            }
        }

        // Look up object from current pointer
        objectPtr = FUN_00421170(currentPtr);
        if (objectPtr != 0) {
            // Compare target type ID with expected location:
            // *(int*)(*(int*)(objectPtr + 0x18) + 8)
            if (*(int*)(*(int*)(objectPtr + 0x18) + 8) == targetTypeId) {
                return objectPtr;
            }
        }

        // Advance iterator
        if (!useArray) {
            // Linked list: move to next node using relative offset stored at *nodePtr
            nodePtr = (int*)((int)nodePtr + *nodePtr);
            flags = nodePtr[1];  // Node flags at offset +4

            // Check special flag values that cause early termination
            if (flags != 0x20000000 && flags != 0x40000000 && flags != 0x80000000) {
                // Not an end marker: check if node has type tag
                if (*(short*)((int)nodePtr + 6) == 0x25e3) {
                    flags = flags & 0xffff;
                }
                if (flags != 0) {
                    // Node not usable – set nodePtr to null to stop iteration
                    nodePtr = nullptr;
                }
            } else {
                // End marker – set nodePtr to null
                nodePtr = nullptr;
            }
        } else {
            // Array: advance to next element
            arrayPtr++;
        }
    }
}