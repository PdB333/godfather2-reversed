// FUNC_NAME: EARSHandleManager::nextEntry
class EARSHandleManager {
public:
    // +0x10: base address of element pool (each element is 0x20 bytes)
    int* m_poolBase;

    // +0x1a: number of valid entries
    unsigned short m_entryCount;

    // +0x1c: pointer to array of unsigned short indices (which slots are in use)
    unsigned short* m_indices;

    // Output is stored in an output struct or pointer array.
    // param_1[0] = pointer to element
    // param_1[1] = index of element in pool
    // param_1[2] = next index in iteration (position in m_indices)
    int nextEntry(int* outData) {
        unsigned short count = m_entryCount;
        int currentPos = outData[2];  // Position in m_indices array
        int nextPos = currentPos + 1;

        // If we've exhausted the indices, reset output and return -1
        if ((int)count <= nextPos) {
            outData[0] = 0;
            outData[1] = -1;
            outData[2] = -1;
            return -1;
        }

        unsigned short slotIdx = m_indices[nextPos];
        outData[0] = (int)(m_poolBase + slotIdx * 0x20);  // Pointer to element
        outData[1] = slotIdx;                              // Slot index
        outData[2] = nextPos;                              // Update current position

        int futurePos = currentPos + 9;
        int result = -1;
        if (futurePos < (int)count) {
            unsigned short futureSlot = m_indices[futurePos];
            int* futureElement = m_poolBase + futureSlot * 0x20;
            // Offset 0x10 is a pointer within the element, then 0x60 is a value
            result = *(int*)(*(int*)((int)futureElement + 0x10) + 0x60);
        }
        return result;
    }
};