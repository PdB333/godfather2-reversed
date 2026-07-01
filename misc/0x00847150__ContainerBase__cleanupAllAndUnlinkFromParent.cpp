// FUNC_NAME: ContainerBase::cleanupAllAndUnlinkFromParent
void __thiscall ContainerBase::cleanupAllAndUnlinkFromParent()
{
    int *arrayPtr;
    int i;
    
    // Loop over each container in the chain (child-to-parent)
    while(true) {
        // First pass: call release on each non-null element in the array
        // The array is at offset 0x100, capacity/count at 0x104
        arrayPtr = *(int **)(this + 0x100);
        if (arrayPtr != arrayPtr + *(int *)(this + 0x104)) {
            do {
                if (*arrayPtr != 0) {
                    // Call release function on the object (FUN_004df600)
                    // This likely decrements reference count or destroys the object
                    FUN_004df600();
                }
                arrayPtr = arrayPtr + 1;
            } while (arrayPtr != (int *)(*(int *)(this + 0x100) + *(int *)(this + 0x104) * 4));
        }
        
        // Second pass: clear all entries (from end to start) and nullify references
        i = *(int *)(this + 0x104);
        while (i = i + -1, i >= 0) {
            int *base = *(int **)(this + 0x100);
            int obj = *(int *)(base + i * 4);
            if (obj != 0) {
                // Zero out the object's offset+8 (could be a handle or next pointer)
                *(undefined4 *)(obj + 8) = 0;
                // Clear the array entry
                *(int *)(base + i * 4) = 0;
            }
        }
        
        // Reset count and free the array buffer
        *(int *)(this + 0x104) = 0;
        FUN_009c8f10(*(int *)(this + 0x100));  // Memory deallocation
        *(int *)(this + 0x100) = 0;
        *(int *)(this + 0x108) = 0;  // Maybe capacity field
        
        // Determine parent container
        // this->parentPointer (offset 0x120) is either 0, 0x48 (sentinel), or a pointer to a parent structure
        // The current container is stored at offset 0x48 inside the parent.
        int parent = *(int *)(this + 0x120);
        if (parent == 0 || parent == 0x48) {
            break;  // No parent or root sentinel
        }
        
        // Compute parent container address (current container is at parent+0x48)
        int parentContainer;
        if (parent == 0) {
            parentContainer = 0;
        } else {
            parentContainer = parent - 0x48;
        }
        
        // If we've reached the same container (shouldn't happen normally), stop
        if (parentContainer == (int)this) {
            return;
        }
        
        // Move up to parent container and repeat
        if (parent == 0) {
            this = 0;  // Should not occur; parent was non-null before check
        } else {
            this = (ContainerBase *)(parent - 0x48);
        }
    }
}