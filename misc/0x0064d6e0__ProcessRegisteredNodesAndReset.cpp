// FUNC_NAME: ProcessRegisteredNodesAndReset

void ProcessRegisteredNodesAndReset(void)
{
    // Global pointer to the head of a linked list of registered nodes.
    // DAT_01205a28 is presumably a list of nodes to process/reset.
    int* head;
    int* nodePtr;
    uint flags;
    int nodeCount;
    int arrayIndex;
    int* nodeArray;          // Dynamic array to collect all node pointers.
    uint arrayCapacity;      // Current capacity of nodeArray.
    int* currentChild;
    
    head = (int*)DAT_01205a28;
    nodeArray = (int*)0x0;
    arrayCapacity = 0;
    nodeCount = 0;
    
    // First pass: collect all node pointers into a dynamic array.
    if (head != (int*)0x0) {
        arrayIndex = 1; // Index for next collection? Actually local_10 is used as a capacity tracker.
        // The original code uses local_10 as capacity, but it's incremented per node.
        // Rewritten for clarity.
        // We'll reimplement the original allocation logic.
        // local_10 starts at 1, but the condition is if (uVar5 < local_10) which means capacity < current count? Hmm.
        // Actually, the logic: it reallocates when arrayCapacity < (nodeCount+1). The initial capacity is 1.
        // It allocates in increments of 16.
        // Simpler: we can just use a list first and then allocate once. But to be faithful to decompiled code, we'll replicate.
        // However, for readability we can simplify. The original code is tricky. Let's rewrite with clear intent.
        
        nodeCount = 0;
        arrayCapacity = 0;
        nodeArray = (int*)0x0;
        
        nodePtr = head;
        // We'll simulate the original reallocation: capacity grows by 16 when needed.
        // For simplicity, we'll just collect all nodes first into a temporary list, then allocate.
        // But since the original code does it inline, we can do:
        // We'll keep the original logic, but comment it.
        // Let's implement a straightforward collection.
    }
    
    // Original logic for first loop: (simplified to clear behavior)
    // We'll rewrite it with proper variable names.
    // Actually, the decompiled code has a do-while that builds the array and also increments an index.
    // Let's just implement a version that matches the semantics but is readable.
    
    // I'll reimplement the function exactly as decompiled but with better names.
    
    // First loop: collect all nodes into nodeArray
    {
        int capacity = 1;
        int* currentArray = (int*)0x0;
        int collected = 0;
        int* runner = head;
        
        if (head != 0) {
            int count = 0;
            int local_14 = head;
            int local_10 = 1;  // capacity
            int* array = 0;
            int idx = 0;
            
            do {
                if ((uint)idx < (uint)local_10) {
                    // Need more space: allocate new array aligned to 16.
                    local_10 = (local_10 - (local_10 & 0xf)) + 0x10;
                    int* newArray = (int*)malloc(local_10 * 4);
                    if (count != 0) {
                        // Copy old elements from old array to new, considering offset.
                        // The original pointer arithmetic is complex; we simplify:
                        // Actually, it copies from old array to new array using relative addresses.
                        // For correctness, just allocate and copy.
                        memcpy(newArray, array, count * 4);
                    }
                    free(array);
                    array = newArray;
                }
                // Store node pointer
                if (array + count != 0) {
                    array[count] = local_14;
                }
                local_14 = *(int*)(local_14 + 0x10); // next node
                count++;
                local_10 = count; // capacity is set to count? Actually increment.
            } while (local_14 != 0);
            
            nodeArray = array;
            nodeCount = count;
        }
    }
    
    // Second loop: process each node in the list (using head pointer again)
    // The loop reads from DAT_01205a28 again (which may be modified during processing).
    while (head = (int*)DAT_01205a28, head != 0) {
        flags = *(uint*)(head + 0x14);
        DAT_01205a28 = *(int*)(head + 0x10); // Remove node from global list (head = next)
        *(undefined4*)(head + 0x10) = 0;
        *(undefined4*)(head + 0xc) = 0;
        *(undefined4*)(head + 0x14) = 0;
        
        if (flags != 0) {
            // Iterate over child list (linked list starting at head+0x1c, next at +0xc)
            int* child = *(int**)(head + 0x1c);
            while (child != 0) {
                uint childFlags = *(uint*)(child + 4);
                if (childFlags == 0) {
                    // Child not yet registered
                    // Get parent from child+0x14
                    int* parent = *(int**)(child + 0x14);
                    // Set child's flags to the parent's flags
                    *(uint*)(child + 4) = flags;
                    
                    // If child's slot index (+0x2c) does not match parent's current count (+0x200)
                    if (*(int*)(child + 0x2c) != *(int*)(parent + 0x200)) {
                        // Swap child with the element at parent's current count slot
                        int* slotPtr = *(int**)(*(int*)(parent + 0x1fc) + *(int*)(parent + 0x200) * 4);
                        // slotPtr->field_0x2c = child->field_0x2c
                        *(int*)(slotPtr + 0x2c) = *(int*)(child + 0x2c);
                        // Move the content from parent's slot to child's old slot
                        *(undefined4*)(*(int*)(parent + 0x1fc) + *(int*)(child + 0x2c) * 4) =
                            *(undefined4*)(*(int*)(parent + 0x1fc) + *(int*)(parent + 0x200) * 4);
                        // Place child at the current count slot
                        *(int*)(*(int*)(parent + 0x1fc) + *(int*)(parent + 0x200) * 4) = child;
                        // Update child's slot index to the current count
                        *(int*)(child + 0x2c) = *(int*)(parent + 0x200);
                    }
                    // Increment parent's count
                    *(int*)(parent + 0x200) = *(int*)(parent + 0x200) + 1;
                }
                else {
                    // Child already has flags, OR them with the new flags
                    *(uint*)(child + 4) = childFlags | flags;
                }
                // Move to next child
                child = *(int**)(child + 0xc);
            }
        }
    }
    
    // Clear global head
    DAT_01205a28 = 0;
    
    // Free the collected node array
    free(nodeArray);
    
    return;
}