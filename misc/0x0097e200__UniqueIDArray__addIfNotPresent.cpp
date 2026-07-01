// FUNC_NAME: UniqueIDArray::addIfNotPresent
// Address: 0x0097e200
// Role: Adds an element identified by an ID to a dynamically-sized array if it is not already present.
// The array stores 16-byte structures; the first 4 bytes are the ID used for uniqueness check.
// On resize, capacity is doubled (or set to 1 if current is 0).

class UniqueIDArray {
public:
    // +0xcc: pointer to array elements (16 bytes each)
    char* m_data;        // offset 0xcc
    // +0xd0: number of used elements
    int m_size;          // offset 0xd0
    // +0xd4: allocated capacity
    int m_capacity;      // offset 0xd4

    // Internal: resize the array to newCapacity (implemented by callee at 0x0097bdf0)
    void resizeArray(int newCapacity);  // FUN_0097bdf0

    // Internal: initialize an element at given offset with the provided ID (implemented by callee at 0x0097c2a0)
    void initializeElement(int id, char* elementPtr);  // FUN_0097c2a0

    // Add id if not already in the array. Returns without action if found.
    void addIfNotPresent(int id) {
        unsigned int i = 0;
        if (m_size != 0) {
            int* currentID = (int*)(m_data + 12);  // offset 0xc within each element? Actually piVar3 = array + 0xc, but later iterated by 4 ints? Wait, let's check.
            // Correction: The code does piVar3 = (int*)(*(int*)(param_1+0xcc) + 0xc); That's base + 12 bytes.
            // Then it does *piVar3 == param_2, comparing the int at that offset. So the ID is at offset 12 within each 16-byte element.
            // Then increments piVar3 by 4 (4 bytes) each loop, which would move to next element? That's only if each element is 4 bytes, but it's 16.
            // There's a mismatch. Actually the code does "piVar3 = piVar3 + 4" – this is pointer arithmetic, so it advances by 4*sizeof(int)=16 bytes.
            // Because piVar3 is int*, adding 4 moves by 4 ints (16 bytes). That matches element size.
            // So piVar3 points to the ID field (offset 12) of each element. So element structure: first 12 bytes are something else, then ID at offset 12.
            // So we'll interpret m_data as array of structs where the ID is at offset 12.
            int* idPtr = (int*)(m_data + 12);
            do {
                if (*idPtr == id) {
                    if (i >= 0) { // always true; just return if found
                        return;
                    }
                    break;
                }
                i++;
                idPtr += 4; // move to next element's ID (16 bytes)
            } while (i < (unsigned int)m_size);
        }

        // Not found; need to add
        if (m_size == m_capacity) {
            int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            resizeArray(newCapacity);
        }

        int newIndex = m_size;
        m_size++;
        char* elementPtr = m_data + newIndex * 16;
        initializeElement(id, elementPtr);
    }
};