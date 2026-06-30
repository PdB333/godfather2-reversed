// FUNC_NAME: GameObject::cleanupAndRemoveFromContainers
void __thiscall GameObject::cleanupAndRemoveFromContainers(void) {
    // Check if the object has a parent (offset +0x1c)
    if (this != 0) {
        int* parent = *(int**)(this + 0x1c);
        if (parent != 0) {
            // Compare parent with a pointer from manager at +0x48
            int* manager = *(int**)(this + 0x222c);
            if (parent == *(int**)(manager + 0x48)) {
                // If parent matches, set a flag at manager+0x80 to true
                *(int*)(manager + 0x80) = 1;
            } else {
                // Otherwise call some cleanup function
                FUN_00673160(); // likely parent/state cleanup
            }
        }

        // Call another cleanup function
        FUN_00676480(); // likely resource cleanup

        // Remove from first container (list at +0xdc, node pointer at +0x160)
        int* nodeA = *(int**)(this + 0x160);
        if (nodeA != (int*)(this + 0xdc)) { // not the sentinel head
            int* newNodeManager = *(int**)(this + 0x222c);
            if (nodeA != 0) {
                // Clear entry in the array at manager+0xc using index from nodeA-8
                int index = *(int*)(nodeA - 8);
                int* arrayBase = *(int**)(newNodeManager + 0xc);
                *(int*)(arrayBase + index) = 0; // clear pointer
                // Decrement count at manager+4
                int* count = (int*)(newNodeManager + 4);
                (*count)--;
                // Free the allocation starting at nodeA-0x10
                void* allocBlock = (void*)(nodeA - 0x10);
                (*DAT_01206694)(allocBlock); // operator delete or custom free
            }
        }

        // Remove from second container (list at +0x4c, node pointer at +0xd0)
        int* nodeB = *(int**)(this + 0xd0);
        if (nodeB != (int*)(this + 0x4c)) { // not the sentinel head
            int* newNodeManager2 = *(int**)(this + 0x222c);
            if (nodeB != 0) {
                // Same removal pattern: clear array slot, decrement count, free
                int index2 = *(int*)(nodeB - 8);
                int* arrayBase2 = *(int**)(newNodeManager2 + 0xc);
                *(int*)(arrayBase2 + index2) = 0;
                int* count2 = (int*)(newNodeManager2 + 4);
                (*count2)--;
                void* allocBlock2 = (void*)(nodeB - 0x10);
                (*DAT_01206694)(allocBlock2);
            }
        }

        // Clear global flag
        DAT_012058ba = 0;
    }
}