// FUNC_NAME: MemoryPool::reassignNode
// Address: 0x00542e80
// This function appears to reassign a node in a memory pool or linked list structure.
// It uses a virtual function at vtable offset 0x214 to check some condition on param_3.
// Then it manipulates a node entry at this->poolBase + (param_2 * 8) and inserts it into a list starting at unaff_ESI.
// The 0x48 constant likely represents node size or header offset.

int __thiscall MemoryPool::reassignNode(int* thisPtr, int nodeIndex, int someParam) {
    int* nodePtr;          // piVar1
    char canProceed;       // cVar2
    int previousNode;      // iVar3
    int* baseAddress;      // unaff_ESI (passed implicitly via ESI)
    
    // Call virtual member: this->vtable[0x214](someParam, &someParam)
    canProceed = (**(code**)(*thisPtr + 0x214))(someParam, &someParam);
    if (canProceed) {
        // Access the node entry at index nodeIndex (each entry is 8 bytes)
        baseAddress = (int*)(*(thisPtr + 0xAE));  // +0x2B8: pointer to pool base
        nodePtr = (int*)(baseAddress + nodeIndex * 8);  // entry at index
        
        previousNode = *nodePtr;
        // Condition: existing node is null, 0x48 (free/aligned), or baseAddress is null
        if (previousNode == 0 || previousNode == 0x48 || baseAddress == 0) {
            int newValue;
            if (baseAddress == 0) {
                newValue = 0;
            } else {
                newValue = (int)baseAddress + 0x48;  // baseAddress + offset (node size)
            }
            // Update only if different
            if (*nodePtr != newValue) {
                if (*nodePtr != 0) {
                    // Free/destruct previous node
                    FUN_004daf90(nodePtr);
                }
                *nodePtr = newValue;
                if (newValue != 0) {
                    // Insert node into list: set next pointer and update previous node's prev
                    nodePtr[1] = *(int*)(newValue + 4);   // nodePtr->next = newValue->prev?
                    *(int**)(newValue + 4) = nodePtr;     // newValue->prev = nodePtr
                }
            }
            return 1;
        }
    }
    return 0;
}