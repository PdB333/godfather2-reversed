// FUNC_NAME: EARSArray::destroy
// Function at 0x00722190: Destructor for a compact array container.
// The container holds a pointer to a dynamically allocated array at offset +0x0C.
// Each element occupies 0x24 bytes. The allocation has a count stored just before the array data (at pointer[-1]).
// Iterates backwards over elements, calling a destructor for each whose first field (pointer) is non-null,
// then frees the allocation header.

void __fastcall EARSArray::destroy(int this)
{
    // +0x0C: pointer to the start of the array data
    int *arrayData = *(int **)(this + 0xC);
    
    if (arrayData != nullptr) {
        // The count is stored in the 4 bytes preceding the array data
        int count = *(int *)(arrayData - 1);
        
        // Start just past the last element (count * elementSize / 4 = count * 9)
        int *currentPos = arrayData + count * 9;
        
        // Iterate backwards over each element
        while (count-- > 0) {
            // Move to the previous element (0x24 bytes back)
            currentPos -= 9;
            
            // If the first field (a pointer) is non-null, destroy the element
            if (*currentPos != 0) {
                // Destructor for the element at currentPos
                // Called as FUN_004daf90 in the original binary
                destructElement(currentPos);
            }
        }
        
        // Free the allocation block (the header at arrayData - 1)
        // Called as FUN_009c8f10 in the original binary
        freeAllocation(arrayData - 1);
    }
}