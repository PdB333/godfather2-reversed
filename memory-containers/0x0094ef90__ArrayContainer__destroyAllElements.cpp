// FUNC_NAME: ArrayContainer::destroyAllElements
void __fastcall ArrayContainer::destroyAllElements()
{
    // param_1 is this pointer (container object)
    int* pArrayStart = this->m_pArray; // +0x00: pointer to dynamic array of 8-byte elements
    
    if (pArrayStart != nullptr) {
        // The array has a 4-byte count stored right before the first element
        int elementCount = *(pArrayStart - 1); // pArrayStart[-1] = signed count
        
        // Iterate backwards over elements; each element is 8 bytes (2 ints)
        for (int i = elementCount - 1; i >= 0; i--) {
            int* pElement = &pArrayStart[i * 2]; // address of current 8-byte element
            // Check if first field of element is non-null (indicates active slot)
            if (*pElement != 0) {
                // Call destructor for the element
                FUN_004daf90(pElement);
            }
        }
        
        // Free the memory block that contains the count + array
        FUN_009c8f10(pArrayStart - 1);
    }
}