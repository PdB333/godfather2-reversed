// FUNC_NAME: ChaseCamera::updateTransformHistory

// 0x00898390 - Update transform history slots for camera smoothing.
// This function shifts a 3-slot transform buffer, then either sets a parent-linked transform or copies a new absolute transform.
void __thiscall ChaseCamera::updateTransformHistory(void *this, void *data) {
    int *nodePtr;
    int nodeValue;
    int *slotBase;
    int slotIndex;
    
    // Reset/initialize the source data structure (likely the camera input state)
    resetTransformData(data);
    
    // Process 3 transform history slots (each slot is 24 bytes apart, but uses 40 bytes? Overlap intentional)
    slotIndex = 3;
    slotBase = (int *)this + 0xe;  // +0x38: start of slot array (offset 0x38)
    do {
        // Shift transform data within slot: copy from indices -2,-1,0,1 to indices 4,5,6,7
        // This effectively moves the previous transform to a later position (history aging)
        slotBase[4] = slotBase[-2];
        slotBase[5] = slotBase[-1];
        slotBase[6] = slotBase[0];
        slotBase[7] = slotBase[1];
        
        // Handle linked list node at slot offset +2 (current node) and offset +8 (next pointer)
        nodePtr = slotBase + 8;  // +0x20 in slot? Actually slotBase+8 is slotBase[8]
        if (nodePtr != slotBase + 2) {
            nodeValue = slotBase[2];
            if (*nodePtr != nodeValue) {
                if (*nodePtr != 0) {
                    linkedListRemoveNode(nodePtr);
                }
                *nodePtr = nodeValue;
                if (nodeValue != 0) {
                    slotBase[9] = *(int *)(nodeValue + 4);
                    *(int **)(nodeValue + 4) = nodePtr;
                }
            }
        }
        
        slotIndex--;
        slotBase -= 6;  // Move to previous slot (24 bytes back)
    } while (slotIndex != 0);
    
    // Determine if we should use a parent-relative transform or an absolute one
    if ((*(uint *)((int)data + 0x1f54) >> 1 & 1) != 0) {
        // Use parent transform from data+0x48
        int *parent = (int *)((int)data + 0x48);
        if (*(int *)((int)this + 0x10) != (int)parent) {  // +0x10: current parent pointer field
            if (*(int *)((int)this + 0x10) != 0) {
                linkedListRemoveNode((int *)this + 4);  // Remove old parent link? Possibly separate list
            }
            *(int *)((int)this + 0x10) = (int)parent;
            if (parent != 0) {
                *(int *)((int)this + 0x14) = *(int *)((int)data + 0x4c);  // +0x14: sibling pointer
                *(int **)((int)data + 0x4c) = (int *)this + 4;  // Link into parent's list
            }
        }
        // Clear absolute transform (since parent-relative)
        *(int *)((int)this + 0x0c) = 0;  // +0x0c: probably a flag or part of transform
        *(int *)((int)this + 0x08) = 0;
        *(int *)((int)this + 0x04) = 0;
        *(int *)this = 0;
    } else {
        // Copy absolute transform from data+0x20 (4 dwords: position + orientation?)
        if (*(int *)((int)this + 0x10) != 0) {
            linkedListRemoveNode((int *)this + 4);
            *(int *)((int)this + 0x10) = 0;
        }
        *(int *)this = *(int *)((int)data + 0x20);
        *(int *)((int)this + 0x04) = *(int *)((int)data + 0x24);
        *(int *)((int)this + 0x08) = *(int *)((int)data + 0x28);
        *(int *)((int)this + 0x0c) = *(int *)((int)data + 0x2c);
    }
}