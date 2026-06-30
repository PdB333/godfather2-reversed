// FUNC_NAME: ConditionEvaluator::evaluate
// Function address: 0x00446bf0
// Evaluates a condition tree/aggregator, checks flags and iterates children, then runs callbacks.
// param_1 (this): ConditionEvaluator instance
// param_2: Context object (e.g., GameEntity* or EventData*) with flags at +0x1c and +0x1d
// param_3: bPerformCheck (if true, check flags; if false, skip some checks)
// param_4: pIsSatisfied (output bool: whether condition is satisfied at this level)
// param_5: pChildSatisfied (output byte: bit0=child satisfied? bit1=only child? etc.)
// Returns: bool (true if condition passes overall; false fails)

char ConditionEvaluator::evaluate(int contextObj, char bPerformCheck, char* pIsSatisfied, byte* pChildSatisfied)
{
    byte bFlags;
    char cResult;
    ConditionNode* ppNode;
    ConditionNode* pNode;
    int* pChild;
    uint uIndex;
    bool bDone;
    char cOverall;
    char local_bIsHash;
    int local_bitmapBase;
    ConditionNode* local_currentNode;
    uint local_currentIndex;
    uint local_count;
    ConditionNode* local_nextNode;
    short local_tempShort;
    uint local_tempUint;
    ConditionNode* local_storage;
    
    cOverall = true;
    // Check if the context object has the "initialized" flag (bit0 at +0x1c)
    if ((*(byte*)(contextObj + 0x1c) & 1) == 0) {
        // Not initialized: reset traversal
        FUN_0043aff0(contextObj, 0xffd2e5b1); // likely "ConditionTree::resetIterator"
        if (pIsSatisfied != NULL) {
            *pIsSatisfied = false;
        }
        ppNode = local_storage;
        pChild = (int*)local_currentNode;
        uIndex = local_currentIndex;
        if (pChildSatisfied != NULL) {
            *pChildSatisfied = 1; // assume satisfied by default
        }
        // Traverse children using either hash table (local_bIsHash != 0) or list
        while (true) {
            pNode = (ConditionNode*)pChild;
            if (local_bIsHash == 0) {
                bDone = (ppNode == NULL); // list mode: check if current node is null
            } else {
                bDone = (uIndex == local_count); // hash mode: check if index >= count
            }
            if (bDone) goto after_traversal;
            
            // Determine the next child node pointer
            if (local_bIsHash == 0) {
                // List mode: children are in a linked list, ppNode is the current node pointer
                if (*(short*)((int)&ppNode + 6) == 0x25e3) { // check node type tag at offset +6
                    pChild = (int*)(uint)*(ushort*)(&ppNode->next); // tag 0x25e3: next offset stored as ushort
                } else {
                    pChild = (int*)ppNode->next; // else next is a direct pointer
                }
            } else {
                // Hash mode: children accessed via bitmap + entry array
                if (*(short*)(&local_storage + 6) == 0x25e3) {
                    pChild = (int*)(uint)*(ushort*)((int)&local_storage + 4); // hash bucket index
                } else {
                    pChild = (int*)local_storage->next;
                }
            }
            if (pChild == NULL) break;
            
            // Advance to next child
            pChild = (int*)pNode;
            if (local_bIsHash == 0) {
                // List mode: advance pointer
                if ((int)uIndex < 0) {
                    FUN_0043b140(); // possibly "ConditionTree::advanceIterator"
                    // After call, ppNode is updated by the function via local_8
                    ppNode = local_storage;
                    pChild = (int*)local_currentNode;
                    uIndex = local_currentIndex;
                } else if ((int)uIndex < (int)(local_count - 1)) {
                    local_currentIndex = uIndex + 1;
                    // Move to next node in list (pointer arithmetic)
                    ppNode = (ConditionNode*)((int)ppNode + (int)ppNode);
                    uIndex = local_currentIndex;
                } else {
                    // Reached end: set to sentinel value (probably end marker)
                    ppNode = (ConditionNode*)0x01163cf8;
                }
            } else {
                // Hash mode: advance index and check bitmap
                local_currentIndex = uIndex + 1;
                uIndex = local_currentIndex;
                if (local_currentIndex != local_count) {
                    local_tempShort = (short)local_currentIndex;
                    // Check if this index is present in the bitmap (bit array at local_bitmapBase)
                    if ((*(byte*)((local_currentIndex >> 3) + local_bitmapBase) & (1 << ((byte)local_currentIndex & 7))) == 0) {
                        // Slot not occupied: store next pointer + node
                        local_currentNode = (ConditionNode*)((int)pNode + 4);
                        local_tempUint = *(int*)pNode;
                        pChild = (int*)local_currentNode;
                        local_storage = (ConditionNode*)pNode;
                    } else {
                        // Slot occupied: mark as invalid
                        local_storage = NULL;
                        local_tempUint = 0;
                    }
                }
            }
        }
        // After loop, set output flags
        if (pIsSatisfied != NULL) {
            *pIsSatisfied = true; // traversal succeeded, condition is satisfied at this level
        }
        if (local_bIsHash != 0) {
            ppNode = &local_storage;
        }
        pChild = (int*)ppNode[2]; // Get the "flags" field of the last node? Or maybe the child's type flags at +0x08?
        // Check if we should suppress result based on flags and perform check flag
        if (((bPerformCheck != 0) && (((uint)pChild & 1) == 0)) ||
            ((*(uint*)((int)this + 0x24) & (uint)pChild) != 0)) {
            cOverall = false;
        }
        if ((pChildSatisfied != NULL) && (((uint)pChild & 4) != 0)) {
            *pChildSatisfied = 0;
        }
    } else {
        // Initialized context: check alternative flags
        if ((*(byte*)(contextObj + 0x1c) & 2) == 0) {
            if (pIsSatisfied != NULL) {
                *pIsSatisfied = false;
            }
            if (pChildSatisfied != NULL) {
                *pChildSatisfied = 1;
            }
            goto after_traversal;
        }
        if (pIsSatisfied != NULL) {
            *pIsSatisfied = true;
        }
        bFlags = *(byte*)(contextObj + 0x1d); // different flag byte at +0x1d
        if (((bPerformCheck != 0) && ((bFlags & 1) == 0)) ||
            ((*(byte*)((int)this + 0x24) & bFlags) != 0)) {
            cOverall = false;
        }
        if (pChildSatisfied != NULL) {
            *pChildSatisfied = ~(bFlags >> 2) & 1; // invert bit2
        }
    }
    if (cOverall == false) {
        return false;
    }
after_traversal:
    // If there are callbacks registered, invoke each with (1, contextObj)
    if ((*(int*)((int)this + 0x20) != 0) && (uIndex = 0, *(int*)((int)this + 0x20) != 0)) {
        pChild = (int*)((int)this + 0x18); // pointer to callback array
        do {
            cResult = (*(char (__thiscall**)(int, int))(*pChild))(1, contextObj);
            if (cResult == 0) {
                return false;
            }
            uIndex = uIndex + 1;
            pChild = pChild + 1;
        } while (uIndex < *(uint*)((int)this + 0x20));
    }
    return cOverall;
}