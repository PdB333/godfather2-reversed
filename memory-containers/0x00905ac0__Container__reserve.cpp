// FUNC_NAME: Container::reserve
// Address: 0x00905ac0
// Reserves capacity for at least newCapacity elements (0x1C bytes each).
void Container::reserve(uint newCapacity) {
    // Only grow if new capacity is larger than current
    if (m_capacity >= newCapacity) return;

    // Allocate new buffer (operator new, not malloc)
    int* newData = (int*)operator new(newCapacity * 0x1C);

    if (m_data != nullptr) {
        // Move existing elements to the new buffer
        for (uint i = 0; i < m_count; ++i) {
            // Pointer to old element (each element is 7 ints = 0x1C bytes)
            int* oldElem = &m_data[i * 7];
            // Pointer to new element (at offset 0x14 from start? Actually code initializes puVar4 to newData+0x14,
            // but we compute directly)
            int* newElem = &newData[i * 7];

            // Call copy/move helper on the old element (prepares data for transfer?)
            FUN_004d3b50(oldElem);

            // Copy three fields from old to new:
            //   oldElem[4] -> newElem[4]   (offset +0x10)
            //   oldElem[5] (truncated to char) -> newElem[5] (offset +0x14)
            //   oldElem[6] -> newElem[6]   (offset +0x18)
            newElem[4] = oldElem[4];
            *(char*)(newElem + 5) = (char)oldElem[5];
            newElem[6] = oldElem[6];

            // If the old element's first field (a pointer) is non‑null, call a cleanup function.
            // The function pointer is at oldElem[3] (offset +0x0C).
            if (oldElem[0] != 0) {
                ((void (__thiscall*)(int*))oldElem[3])((int*)oldElem[0]);
            }
        }

        // Free the old buffer
        FUN_009c8f10(m_data);
    }

    // Update pointer and capacity (count remains unchanged)
    m_data = newData;
    m_capacity = newCapacity;
}