// FUNC_NAME: EntityManager::removeByID
// Function at 0x0097da80
// Removes an element from a dynamic array (each element 0x10 bytes) by matching an int key at offset +0xC within the element.
// The array base pointer is at this+0xC0, element count at this+0xC4.
// Calls cleanup function on the element before removal.
// If the element is not the last, the last element is copied into its place.

void __thiscall EntityManager::removeByID(int thisPtr, int key) {
    uint index = 0;
    
    // Check if the array is non-empty
    if (*(uint *)(thisPtr + 0xC4) != 0) {
        // Get pointer to the first element's key field (offset +0xC)
        int *keyPtr = (int *)(*(int *)(thisPtr + 0xC0) + 0xC);
        
        // Linear search for the element with matching key
        while (*keyPtr != key) {
            index++;
            keyPtr = keyPtr + 4; // advances by 0x10 bytes (element size)
            if (*(uint *)(thisPtr + 0xC4) <= index) {
                return; // key not found
            }
        }
        
        // Found at 'index'; call cleanup function on the element
        if ((int)index >= 0) {
            FUN_0097c1e0(*(int *)(thisPtr + 0xC0) + index * 0x10);
            
            // If it's not the last element, overwrite with the last element
            if (index != *(int *)(thisPtr + 0xC4) - 1) {
                int arrayBase = *(int *)(thisPtr + 0xC0);
                int lastElementOffset = *(int *)(thisPtr + 0xC4) * 0x10 - 0x10; // (count-1)*0x10
                undefined8 *dest = (undefined8 *)(arrayBase + index * 0x10);
                undefined8 *src = (undefined8 *)(arrayBase + lastElementOffset);
                *dest = *src;
                dest[1] = src[1];
            }
            
            // Decrement element count
            *(int *)(thisPtr + 0xC4) = *(int *)(thisPtr + 0xC4) - 1;
        }
    }
    return;
}