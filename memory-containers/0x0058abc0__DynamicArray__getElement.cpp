// FUNC_NAME: DynamicArray::getElement

// Address: 0x0058abc0
// Role: Access element by index with bounds checking; auto-resize if index >= size.
// Struct layout:
//   +0x00: int* m_pData
//   +0x04: uint32 m_size

class DynamicArray {
    int* m_pData;   // +0x00
    uint32 m_size;  // +0x04

public:
    /**
     * Returns a pointer to the element at the given index.
     * If the index is out of bounds, the array is resized (via growArray)
     * to accommodate at least index+1 elements.
     */
    int* getElement(uint32 index) {
        // Save the original data pointer.
        int* pOriginalData = m_pData;

        // Bounds check: if index >= current size, grow the array.
        if (index >= m_size) {
            // Decompiler shows: param_1 = NULL; FUN_00591c00(&param_1);
            // This is interpreted as: set this to a temporary null pointer
            // and pass its address to growArray, which expects a pointer to the array.
            // In reality, the 'this' pointer is passed as reference.
            // For clarity, we call growArray(this).
            growArray(this);
        }

        // Return pointer to element: base address + index * sizeof(int)
        return pOriginalData + index;
    }

    // External resize/grow function (address 0x00591c00)
    friend void growArray(DynamicArray* pArray);
};